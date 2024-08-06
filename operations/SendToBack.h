#pragma once
#include "operation.h"
#include "..\controller.h"
#include "..\shapes\Graph.h"

class SendToBack : public operation
{
	shape* currentshape;
public:

	SendToBack(controller* pCont);
	void readoperationParameters() override;
	void Execute() override;
};
