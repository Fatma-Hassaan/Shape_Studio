#pragma once
#include "operation.h"

class opPasteShape : public operation
{
public:
    opPasteShape(controller* pCont);
    virtual void Execute();
};
