#include "Rect.h"

Rect::Rect(Point P1, Point P2, GfxInfo shapeGfxInfo):shape(shapeGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
}

Rect::~Rect()
{}

void Rect::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawRect(Corner1, Corner2, ShpGfxInfo);
}
bool Rect::isPointInside(int x, int y) const {
    return (x >= Corner1.x && x <= Corner2.x && y >= Corner1.y && y <= Corner2.y);
}

void Rect::setSelected(bool selected) {
    ShpGfxInfo.isSelected = selected;
    if (selected) {
        ShpGfxInfo.DrawClr = SELECTED_BORDER_COLOR; // Change border color to indicate selection
    }
    else {
        ShpGfxInfo.DrawClr = ORIGINAL_BORDER_COLOR;  // Revert to original border color
    }
}
