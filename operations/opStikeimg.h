#pragma once
#include "..\operations\operation.h"
#include "..\Shapes\Graph.h"
#include "..\GUI\GUI.h"

class opAddImage : public operation
{
public:
    opAddImage(controller* pCont);
    virtual ~opAddImage();
    virtual void Execute();
};
