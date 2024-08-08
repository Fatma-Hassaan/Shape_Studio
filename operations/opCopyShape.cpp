#include "opCopyShape.h"
#include "..\controller.h"
#include"GUI/GUI.h"
#include"Shapes/Shape.h"
opCopyShape::opCopyShape(controller* pCont) : operation(pCont) {}

void opCopyShape::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGraph = pControl->getGraph();
    
   	shape* cop = pGraph->GetSelected();
	if (cop) {
		pGraph->setCopied(cop);
		pUI->PrintMessage("shape is Copied");
		
	}
	else {
		pUI->PrintMessage("Please Select A shape First");
	}

}
}
