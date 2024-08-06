#include "UndoRedo.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "Load.h"
#include <string>

UndoRedo::UndoRedo(controller* pCont, int mode) :operation(pCont)
{
	this->mode = mode;
}

void UndoRedo::readoperationParameters(){}

void UndoRedo::Execute()
{
	GUI* pGUI = pControl->GetUI();
	Load load(pControl);

	string filename;
	if (mode == MODE_UNDO) {

		if (undoList.empty()) {
			pGUI->PrintMessage("No more available UNDOs");
			return;
		}

		filename = *(undoList.end() - 1);
		undoList.pop_back();
		redoList.emplace_back(currentFileName);

		updateFileNamesAccordingTo(filename);

	}
	else {

		if (redoList.empty()) {
			pGUI->PrintMessage("No more available REDOs");
			return;
		}

		filename = *(redoList.end() - 1);
		redoList.pop_back();
		undoList.emplace_back(currentFileName);

		updateFileNamesAccordingTo(filename);
	}

	load.loadFromFile(filename);

	pGUI->PrintMessage("Undo, Click anywhere");

	pGUI->DrawUndoRedoIcons(MODE_UNDO, !undoList.empty());
	pGUI->DrawUndoRedoIcons(MODE_REDO, !redoList.empty());
}

void UndoRedo::updateFileNamesAccordingTo(string filename) const
{
	currentFileName = filename;

	// update value of historyCount according to currentFileName
	sscanf_s(currentFileName.c_str(), "save\\history%d.sav", &historyCount);
	nextFileName = "save\\history" + to_string(++historyCount) + ".sav";
}

void UndoRedo::eraseRedoList()
{
	redoList.clear();
}

void UndoRedo::incrementUndoList()
{
	undoList.emplace_back(currentFileName);
	currentFileName = nextFileName;
	nextFileName = "save\\history" + to_string(++historyCount) + ".sav";
}

bool UndoRedo::isUndoAvailable()
{
	return !undoList.empty();
}

bool UndoRedo::isRedoAvailable()
{
	return !redoList.empty();
}

string UndoRedo::getNextFileName()
{
	return nextFileName;
}

string UndoRedo::getCurrentFileName()
{
	return currentFileName;
}

int UndoRedo::historyCount = 1;
string UndoRedo::currentFileName = "save\\history0.sav";
string UndoRedo::nextFileName = "save\\history1.sav";
vector<string> UndoRedo::undoList;
vector<string> UndoRedo::redoList;