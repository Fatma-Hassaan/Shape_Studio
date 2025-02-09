#pragma once
#include "Shape.h"
#include <fstream>

using namespace std;

//forward decl
class GUI;	

//A class that is responsible on everything related to shapes
class Graph
{
	enum { maxShapeCount = 1000 };
private:
	shape* shapesList[maxShapeCount]; //a container to hold all shapes							   
	int shapeCount;			// Actual number of shapes stored in the list
	shape* selectedShape;	//pointer to the currently selected shape
public:										
	Graph();
	~Graph();
	void Addshape(shape* pFig); //Adds a new shape to the shapesList
	void Draw(GUI* pUI) const;			//Draw the graph (draw all shapes)
	shape* Getshape(int x, int y) const; //Search for a shape given a point inside the shape
       /* void unselectAllShapes();
        void selectShape(int x, int y);*/
        void sendToBack(Shape*);
        void Writeshapes(ofstream&);
        void writeshapes(ofstream&, ShapeType);
        bool empty();
        void setCopied(shape*);
        shape* getCopied();
        shape* GetSelected();
	void setselected(shape* s);
       // shape* GetClipboard() const;
        //void RemoveShape(shape* pShp);
	void Save(ofstream& outfile);	//Save all shapes to a file
	void load(ifstream& inputfile);	//Load all shapes from a file
};
