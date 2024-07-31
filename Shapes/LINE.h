#pragma once
#include "Shapes/Shape.h"

class LINE : public shape
{
private:
	Point Corner1;
	Point Corner2;
public:
	LINE(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~LINE();
	virtual void Draw(GUI* pUI) const;
        virtual bool isPointInside(int x, int y) const override;
	virtual void setSelected(bool selected) override;
};

