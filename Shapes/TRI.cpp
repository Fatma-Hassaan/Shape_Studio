#include "TRI.h"

TRI::TRI(Point P1, Point P2,Point P3, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
}

TRI::~TRI()
{}

void TRI::Draw(GUI* pUI) const
{
	pUI->DrawTRI(Corner1, Corner2,Corner3, ShpGfxInfo);
}