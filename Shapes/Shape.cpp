#include "shape.h"

shape::shape(GfxInfo shapeGfxInfo)
{ 
	ShpGfxInfo = shapeGfxInfo;
	
}
shape::~shape()
{
    if (ShpImage)
        delete ShpImage; // Free the image memory if it exists
}
void shape::SetSelected(bool s)
{	ShpGfxInfo.isSelected = s; }

bool shape::IsSelected() const
{	return ShpGfxInfo.isSelected; }

void shape::ChngDrawClr(color Dclr)
{	ShpGfxInfo.DrawClr = Dclr; }

void shape::ChngFillClr(color Fclr)
{	
	ShpGfxInfo.isFilled = true;
	ShpGfxInfo.FillClr = Fclr; 
}

/*void shape::setType(ShapeType T)
{
	shpType = T;
}
*/
/*ShapeType shape::getType() const
{
	return shpType;
}*/

