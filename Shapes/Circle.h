#pragma once

#include "Shapes/shape.h"

class Circle : public shape
{
private:
	Point Corner1;
	Point Corner2;
public:
	Circle(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Circle();
	virtual void Draw(GUI* pUI) const;
	virtual bool isPointInside(int x, int y) const override;
	virtual void setSelected(bool selected) override;
};

