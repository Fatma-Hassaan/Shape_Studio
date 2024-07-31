#include "operations/operation.h"
#include "GUI/GUI.h"
#include "Shapes/Graph.h"
#include "controller.h"

opSelect::opSelect(controller* pCont) : operation(pCont) {}

void opSelect::Execute() {
    GUI* pGUI = pControl->GetUI();
    Graph* pGraph = pControl->getGraph();

    // Get mouse click coordinates
    int x, y;
    pGUI->GetPointClicked(x, y);

    shape* pShape = pGraph->Getshape(x, y);

    if (pShape) {
        pShape->setSelected(true); // Mark the shape as selected
        pGUI->PrintMessage("Shape selected.");
    }
    else {
        pGUI->PrintMessage("No shape at this point.");
    }
}