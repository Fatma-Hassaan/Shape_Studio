#include "TRI.h"
#include "operations/operation.h"
#include "controller.h"
#include "GUI\GUI.h"

opAddTriangle::opAddTriangle(controller* pCont) :operation(pCont)
{}
opAddTriangle::~opAddTriangle()
{}

//Execute the operation
void opAddTriangle::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("New Triangleangle: Click at first corner");
	//Read 1st corner and store in point P1
	pUI->GetPointClicked(P1.x, P1.y);

	string msg = "First corner is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";
	msg += " ... Click at second corner";
	pUI->PrintMessage(msg);
	//Read 2nd corner and store in point P2
	pUI->GetPointClicked(P2.x, P2.y);
	pUI->ClearStatusBar();

	//Preapre all Triangle parameters
	GfxInfo TriangleGfxInfo;

	//get drawing, filling colors and pen width from the interface
	TriangleGfxInfo.DrawClr = pUI->getCrntDrawColor();
	TriangleGfxInfo.FillClr = pUI->getCrntFillColor();
	TriangleGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	//TriangleGfxInfo.isFilled = false;	//default is not filled
	TriangleGfxInfo.isSelected = false;	//defualt is not selected


	//Create a Triangleangle with the above parameters
	TRI* R = new TRI(P1, P2, TriangleGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the Triangleangle to the list of shapes
	pGr->Addshape(R);

}
