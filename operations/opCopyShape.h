#pragma once
#include "operation.h"

class opCopyShape : public operation
{
public:
    opCopyShape(controller* pCont);
    virtual void Execute();
};
