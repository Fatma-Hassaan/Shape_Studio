#include "SendToBack.h"
#include "..\controller.h"
#include "..\GUI\GUI.cpp"
#include "..\GUI\GUI.h"


SendToBack::SendToBack(controller* pCont) :operation(pCont)
{}

void SendToBack::readoperationParameters()
{
	currentshape = pControl->getSelectedShape();
}
void SendToBack::Execute()
{

	readoperationParameters();

	GUI* pGUI = pControl->GetUI();

	pGUI->CreateDrawOperationToolBar();
	pGUI->drawOnoperationbar("images\\MenuItems\\Menu_send_to_back.jpg", ITM_SEND_TO_BACK);

	if (currentFigure == nullptr)
		pGUI->PrintMessage("Please Select a shape first");
	else
		pCont->sendToBack(currentshape);

	Save save(pCont);
	save.saveForUndo();
}