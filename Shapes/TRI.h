#pragma once

#include "Shapes/Shape.h"

class TRI : public shape
{
private:
	Point Corner1;	
	Point Corner2;
	Point Corner3;
public:
TRI(Point, Point, Point, GfxInfo shapeGfxInfo );
virtual ~TRI();
virtual void Draw(GUI* pUI) const;
virtual bool isPointInside(int x, int y) const override;
virtual void setSelected(bool selected) override;
};


