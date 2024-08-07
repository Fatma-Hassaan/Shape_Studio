#include "opPasteShape.h"
#include "..\controller.h"

opPasteShape::opPasteShape(controller* pCont) : operation(pCont) {}

void opPasteShape::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGraph = pControl->getGraph();
    
    shape* clipboardShape = pGraph->GetClipboard();
    if (clipboardShape != nullptr)
    {
        shape* newShape = clipboardShape->Clone();
        
        int x, y;
        pUI->PrintMessage("Click to place the copied shape");
        pUI->GetPointClicked(x, y);
        
        newShape->Move(x, y);
        pGraph->Addshape(newShape);
        
        pUI->PrintMessage("Shape pasted");
    }
    else
    {
        pUI->PrintMessage("Clipboard is empty");
    }
}
