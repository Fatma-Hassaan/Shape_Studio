#include "LINE.h"

LINE::LINE(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
}

LINE::~LINE()
{}

void LINE::Draw(GUI* pUI) const
{	
	pUI->DrawLINE(Corner1, Corner2, ShpGfxInfo);
}