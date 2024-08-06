#include "Save.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include <string>




Save::Save(controller* pCont) :operation(pCont)
{}

void Save::readoperationParameters()
{
	GUI* pGUI = pControl->GetUI();
	pGUI->PrintMessage("Save Figures, click on the icon again to confirm.");
	Confirm = pGUI->GetUseroperation();
	pGUI->ClearStatusBar();
}

void Save::Execute()
{
	GUI* pGUI = pControl->GetUI();

	// Confirming the action:
	if (Confirm != SAVE)
	{
		pGUI->PrintMessage("Cancelled!");
		return;
	}

	// Reading and setting the name of the destination file:
	pGUI->PrintMessage("Enter the name of the file including the extension  OR  Press [ENTER] to save to shapeList.txt");
	string FileName = pGUI->GetSrting();
	FileName = !FileName.empty() ? FileName : "shapeList.txt";

	savetoFile(FileName);

	pControl->GetUI()->PrintMessage("Saved Successfully to " + FileName + "!");
}

void Save::savetoFile(string filename) const
{
	// Saving to the file:
	ofstream OutFile;
	OutFile.open(filename);
	pControl->Writeshapes(OutFile);

	// Finishing up:
	OutFile.close();
}

void Save::quickSave() const
{
	savetoFile("SaveGame.txt");
}

void Save::saveForUndo(bool firstTime) const
{
	GUI* pGUI = pControl->GetUI();
	string filename;

	// firstTime is used to save the program state when it first opens to initialize "history0.sav" file

	if (firstTime)
	{
		filename = UndoRedo::getCurrentFileName();
	}
	else
	{
		filename = UndoRedo::getNextFileName();
		UndoRedo::incrementUndoList();
	}

	// if we made some UNDOs and made a new action previous REDOs will be removed
	UndoRedo::eraseRedoList();
	pGUI->DrawUndoRedoIcons(UndoRedo::MODE_REDO, false);

	pGUI->DrawUndoRedoIcons(UndoRedo::MODE_UNDO, UndoRedo::isUndoAvailable());

	savetoFile(filename);
}