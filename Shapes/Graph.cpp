#include "Graph.h"
#include "../GUI/GUI.h"

Graph::Graph()
{
	shapeCount = 0;
	selectedShape = nullptr;
}

Graph::~Graph()
{
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
	for (int i=0;i<shapeCount; i++)
		shapesList[i]->Draw(pUI);
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
void Graph::unselectAllShapes() {
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
}
