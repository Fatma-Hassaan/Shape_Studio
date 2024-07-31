#include "opChangeDcolor.h"
#include "controller.h"
#include "GUI\GUI.h"

opChangeDcolor::opChangeDcolor(controller* pCont) :operation(pCont)
{}
opChangeDcolor::~opChangeDcolor()
{}
//Execute the operation
void opChangeDcolor::Execute() {



	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();
	color temp = pUI->GetColor();
	pUI->SetCrntDrawColor(temp);
}
