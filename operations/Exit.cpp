#include "Exit.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


Exit::Exit(controller* pControl) : operation(pCont)
{}

void Exit::readoperationParameters()
{

	GUI* pGUI = pControl->GetUI();
	pGUI->PrintMessage("Exit");
	pGUI->ClearStatusBar();
}

void Exit::Execute()
{
	readoperationParameters();
	pControl->exit();
}