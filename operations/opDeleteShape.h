#pragma once
#include "operation.h"

class opDeleteShape : public operation
{
public:
    opDeleteShape(controller* pCont);
    virtual void Execute();
};
