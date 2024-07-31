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
bool TRI::isPointInside(int x, int y) const {
    return (x >= Corner1.x && x <= Corner2.x && y >= Corner1.y && y <= Corner2.y);
}

void TRI::setSelected(bool selected) {
    ShpGfxInfo.isSelected = selected;
    if (selected) {
        ShpGfxInfo.DrawClr = SELECTED_BORDER_COLOR; // Change border color to indicate selection
    }
    else {
        ShpGfxInfo.DrawClr = ORIGINAL_BORDER_COLOR;  // Revert to original border color
    }
}
