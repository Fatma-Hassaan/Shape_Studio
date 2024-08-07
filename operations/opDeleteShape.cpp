#include "opDeleteShape.h"
#include "..\controller.h"

opDeleteShape::opDeleteShape(controller* pCont) : operation(pCont) {}

void opDeleteShape::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGraph = pControl->getGraph();
    
    int x, y;
    pUI->PrintMessage("Select a shape to delete");
    pUI->GetPointClicked(x, y);
    
    shape* pShp = pGraph->Getshape(x, y);
    if (pShp != nullptr)
    {
        pGraph->RemoveShape(pShp);
        pUI->PrintMessage("Shape deleted");
    }
    else
    {
        pUI->PrintMessage("No shape selected");
    }
}
