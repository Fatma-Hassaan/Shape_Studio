#include "Graph.h"
#include "../GUI/GUI.h"
#include"../controller.h"
#include "..\operations\operation.h"

Graph::Graph()
{
	shapeCount = 0;
	selectedShape = nullptr;
	copShape = nullptr;
}



//==================================================================================//
//						shapes Management Functions								//
//==================================================================================//

//Add a shape to the list of shapes
void Graph::Addshape(shape* pShp)
{
	//Add a new shape to the shapes list
	if(shapeCount<maxShapeCount)
		shapesList[shapeCount++] = pShp;
}
////////////////////////////////////////////////////////////////////////////////////
//Draw all shapes on the user interface
void Graph::Draw(GUI* pUI) const
{
	pUI->ClearDrawArea();
	for (int i = 0; i < shapeCount; ++i)
    {
        if (shapesList[i]->ShpImage)
            pUI->DrawImage(shapesList[i]->P1, shapesList[i]->P2, shapesList[i]->ShpImage);
        else
            shapesList[i]->Draw(pUI);
    }
}


shape* Graph::Getshape(int x, int y) const
{
	//If a shape is found return a pointer to it.
	//if this point (x,y) does not belong to any shape return NULL
    for (int i = 0; i < shapeCount; ++i) {
	if (shapesList[i]->isPointInside(x, y)) {
		return shapesList[i];
	}
        }

	///Add your code here to search for a shape given a point x,y	

	return nullptr;
}
shape* Graph::GetSelected()
{
	return selectedShape;
}
shape* Graph::getCopied() {
	return copiedShape;
}

void Graph::setCopied(shape* copied) {
	copiedShape = copied;
}

void Graph::setselected(shape* s)
{
	if (!selectedShape)
		selectedShape = s;
}


/*void Graph::unselectAllShapes() {
	for (int i = 0; i < shapeCount; i++) {
		shapesList[i]->setSelected(false);
	}
}

void Graph::selectShape(int x, int y) {
	for (int i = 0; i < shapeCount; i++) {
		if (shapesList[i]->isPointInside(x, y)) {
			unselectAllShapes();
			shapesList[i]->setSelected(true);
			return;
		}
	}
	unselectAllShapes();
}*/

void Graph::Writeshapes(ofstream& OutFile)
{
	OutFile << colorData(DrawColor) << " " << colorData(FillColor) << endl;
	OutFile << shapeCount;	
	for (int i = 0; i < shapeCount; i++)
		shapesList[i]->save(OutFile);	//Calling the Save function for each figure
}

void Graph::writeshapes(ofstream& OutFile, ShapeType SavedType)
{
	int TypeCount = 0;
	for (int i = 0; i < shapeCount; i++)
		if (shapesList[i]->getType() == SavedType)
			TypeCount++;

	OutFile << colorData(DrawColor) << " " << colorData(FillColor) << endl;		
	OutFile << TypeCount;	//Writing the number of figures of SavedType
	for (int i = 0; i < shapeCount; i++)
		if (shapesList[i]->getType() == SavedType)
			shapesList[i]->save(OutFile);	
}

bool Graph::empty()
{
	for (int i = 0; i < shapeCount; i++)
		if (shapesList[i])
			return false;
	return true;
}

void Graph::sendToBack(Shape* shape)
{
	int currentIndex;
	shape* currentshape;

	for (int i = 0; i < shapeCount; i++)
	{

		if (shapesList[i] == shape)
		{
			currentIndex = i;
			currentshape = shapesList[i];
			break;
		}
	}

	for (int i = currentIndex; i > 0; i--)
	{
		shapesList[i] = shapesList[i - 1];
	}

	shapesList[0] = currentshape;
}
shape** Graph::getshapesList() const
{
    shape** newshapelist = new shape*[shapesListSize];
    for (size_t i = 0; i < shapesListSize; ++i)
    {
        newshapelist[i] = shapesList[i];
    }
    return newshapelist;
}
shape** Graph::selectedshapes(size& selectedCount) const
{
    // First, count the number of selected shapes
    selectedCount = 0;
    for (size i = 0; i < shapesListSize; ++i)
    {
        if (shapesList[i]->IsSelected())
        {
            ++selectedCount;
        }
    }

    // Allocate memory for the selected shapes
    shape** selectedshapes = new shape*[selectedCount];
    size j = 0;

    // Fill the array with the selected shapes
    for (size i = 0; i < shapesListSize; ++i)
    {
        if (shapesList[i]->IsSelected())
        {
            selectedshapes[j++] = shapesList[i];
        }
    }

    return selectedshapes;
}

/*void Graph::SetClipboard(shape* pShp)
{
    if (clipboardShape != nullptr)
    {
        delete clipboardShape;
    }
    clipboardShape = pShp;
}

// Get clipboard shape
shape* Graph::GetClipboard() const
{
    return clipboardShape;
}

// Remove shape from the list
void Graph::RemoveShape(shape* pShp)
{
    for (int i = 0; i < shapeCount; ++i)
    {
        if (shapesList[i] == pShp)
        {
            delete shapesList[i];
            for (int j = i; j < shapeCount - 1; ++j)
            {
                shapesList[j] = shapesList[j + 1];
            }
            shapeCount--;
            return;
        }
    }
}*/
Graph::~Graph()
{
}
