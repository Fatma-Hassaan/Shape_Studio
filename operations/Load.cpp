#include "Load.h"
#include "..\controller.h"
#include "..\GUI\GUI.cpp"
#include "..\GUI\GUI.h"


Load::Load(controller* pCont) :operation(pCont)
{}

void Load::readoperationParameters()
{
	GUI* pGUI = pControl->GetUI();
	pGUI->PrintMessage("Load Figures, click on the icon again to confirm.");
	confirm = pGUI->GetUseroperation();
	pGUI->ClearStatusBar();
}

void Load::Execute()
{
	GUI* pGUI = pControl->GetUI();
 
	readActionParameters(); 
	if (confirm != LOAD)
	{
		pGUI->PrintMessage("Cancelled!");
		return;
	}

	// Reading and setting the name of the source file:
	pGUI->PrintMessage("Enter the name of the file  OR  Press [ENTER] to load from shapeList.txt");
	string FileName = pGUI->GetSrting();
	FileName = !FileName.empty() ? FileName : "shapeList.txt";

	loadFromFile(FileName);

	pGUI->PrintMessage("Loaded Successfully!");
}

void Load::readshapes(ifstream& InFile) const
{
	while (!InFile.eof())
	{
		shape* Newshp;
		string SavedType;	//The Figure's type
		InFile >> SavedType;	//Reading the type
		ShapeType SHP_TYPE = readType(SavedType);	//Setting the type
		if (SHP_TYPE == EMPTY_TYPE) break;
		setshpType(Newshp, SHP_TYPE);	//Creating a dummy object of that type
		Newshp->load(InFile);	//Calling its Load function
		pControl->Addshape(Newshp);	//Adding it to the list
	}
}

void Load::quickLoad() const
{
	loadFromFile("SaveGame.txt");
	GUI* pGUI = pControl->GetUI();
}

void Load::loadFromFile(string filename) const
{
	GUI* pGUI = pControl->GetUI();
	//pControl->clearFigures();
	ifstream InFile;
	InFile.open(filename);

	// Reading the draw and fill colors and changing their icons:
	Color DrawColor = readColor(InFile);
	Color FillColor = readColor(InFile);
	
	pGUI->ChangeDrawColor(DrawColor);
	pGUI->ChangeFillColor(FillColor, FillColor != NoFill());

	// Reading shape Information from the file:
	int NoOfshapes;
	InFile >> NoOfshapes;

	readshapes(InFile);

	// Finishing up:
	InFile.close();
}