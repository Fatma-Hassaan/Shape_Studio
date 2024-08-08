#include "opAddImage.h"
#include "..\controller.h"
#include"Shapes/Shape.h"
#include"GUI/GUI.h"

opAddImage::opAddImage(controller* pCont) : operation(pCont)
{}

opAddImage::~opAddImage()
{}

void opAddImage::Execute()
{
    // Get a pointer to the graph
    Graph* pGraph = pControl->getGraph();

    // Get a pointer to the UI
    GUI* pGUI = pControl->GetUI();
    pGraph->drawstickimage(pUI);
}
