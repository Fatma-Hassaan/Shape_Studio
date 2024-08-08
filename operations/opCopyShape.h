#pragma once
#include "operation.h"

class opCopyShape : public operation
{
public:
    opCopyShape(controller* pCont);
    ~opCopy();
    virtual void Execute();
};
