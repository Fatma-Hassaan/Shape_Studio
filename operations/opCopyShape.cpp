#include "opCopyShape.h"
#include "..\controller.h"

opCopyShape::opCopyShape(controller* pCont) : operation(pCont) {}

void opCopyShape::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGraph = pControl->getGraph();
    
    int x, y;
    pUI->PrintMessage("Select a shape to copy");
    pUI->GetPointClicked(x, y);
    
    shape* pShp = pGraph->Getshape(x, y);
    if (pShp != nullptr)
    {
        pGraph->SetClipboard(pShp->Clone());
        pUI->PrintMessage("Shape copied");
    }
    else
    {
        pUI->PrintMessage("No shape selected");
    }
}
