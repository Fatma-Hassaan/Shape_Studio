#include "opAddImage.h"
#include "..\controller.h"

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

    // Prompt user to select a shape
    pGUI->PrintMessage("Select a shape to attach an image");
    int x, y;
    pGUI->GetPointClicked(x, y);

    shape* pShape = pGraph->Getshape(x, y);
    if (!pShape)
    {
        pGUI->PrintMessage("No shape selected. Operation aborted.");
        return;
    }

    // Prompt user to enter image file path
    pGUI->PrintMessage("Enter the path of the image file:");
    string imagePath = pGUI->GetSrting();

    // Load the image
    image* img = pGUI->LoadImage(imagePath);
    if (!img)
    {
        pGUI->PrintMessage("Failed to load image. Operation aborted.");
        return;
    }

    // Set the image to the shape
    pShape->SetImage(img);

    pGUI->PrintMessage("Image added to shape.");
}
