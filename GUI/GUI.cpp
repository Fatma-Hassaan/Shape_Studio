#include "GUI.h"

GUI::GUI()
{
	InterfaceMode = MODE_DRAW;
	width = 1300;
	height = 700;
	wx = 5;
	wy = 5;


	StatusBarHeight = 50;
	ToolBarHeight = 50;
	MenuIconWidth = 80;
	ColorIconWidth=30;

	DrawColor = DARKGREEN;	//default Drawing color
	FillColor = YELLOW;	//default Filling color
	MsgColor = BLUE;		//Messages color
	BkGrndColor = WHITE;	//Background color
	HighlightColor = MAGENTA;	//This color should NOT be used to draw shapes. use it for highlight only
	StatusBarColor = LIGHTSEAGREEN;
	PenWidth = 3;	//default width of the shapes frames


	//Create the output window
	pWind = CreateWind(width, height, wx, wy);
	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - PAINT ^ ^ PLAY - - - - - - - - - -");

	CreateDrawToolBar();
	CreateStatusBar();
}




//======================================================================================//
//								Input Functions										//
//======================================================================================//
void GUI::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string GUI::GetSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if( Label.size() > 0)	
				Label.resize(Label.size() - 1);
			else
				Key = '\0';		
		else
			Label += Key;
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired operation
operationType GUI::GetUseroperation() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (InterfaceMode == MODE_DRAW)
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < ToolBarHeight)
		{
			if (x > width - 5 * MenuOperationWidth && x < width - 4 * MenuOperationWidth)
				return UNDO;
			if (x > width - 4 * MenuOperationWidth && x < width - 3 * MenuOperationWidth)
				return REDO;
			//Check whick Menu icon was clicked
			//==> This assumes that menu icons are lined up horizontally <==

			int ClickedIconOrder = (x / MenuIconWidth);
			//Divide x coord of the point clicked by the menu icon width (int division)
			//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

			if (x < (ICON_FILL_CLR)*MenuIconWidth + 50 && x >(ICON_FILL_CLR) * MenuIconWidth)
				return CHNG_FILL_CLR;
			if (x < (ICON_DRAW_CLR)*MenuIconWidth && x >(ICON_DRAW_CLR) * MenuIconWidth - 50)
				return CHNG_DRAW_CLR;


			switch (ClickedIconOrder)
			{
			case ICON_GAME:      return TO_PLAY;
			case ICON_RECT:      return DRAW_RECT;
			case ICON_TRI:       return DRAW_TRI;
			case ICON_CIR:       return DRAW_CIRC;
			case ICON_LINE:	     return DRAW_LINE;
			case ICON_SQE:       return DRAW_SQE;
			case ICON_OVAL:      return DRAW_OVAL;
			case ICON_RPOL:      return DRAW_RPOL;
			case ICON_IRPOL:     return DRAW_IRPOL;
			case ICON_DRAW_CLR: return CHNG_DRAW_CLR;
	                 case ICON_EXIT: return EXIT;

			default: return EMPTY;
			}

		}
		else if (x >= 0 && x < MenuOperationWidth)
		{
			int ClickedItemOrder = (y / MenuOperationWidth) - 1;

			switch (ClickedItemOrder)
			{
			case ITM_LOAD:               return LOAD;
			case ITM_SAVE:               return SAVE;
			case ITM_COPY:               return COPY;
			case ITM_PASTE:              return PASTE;
			case ITM_DELETE:             return DEL;
			case ITM_SEND_TO_BACK:       return SEND_BACK;
			case ITM_BRING_TO_FRONT:     return BRNG_FRNT;
			case ITM_RESIZE:             return RESIZE;
			case ITM_ROTATE:             return ROTATE;
			case ITM_MOVE:               return MOVE;


			default: return EMPTY;
			}

		}

		//[2] User clicks on the drawing area
		if (y >= ToolBarHeight && y < height - StatusBarHeight && x >= MenuOperationWidth)
		{
			return DRAWING_AREA;
		}
		//[3] User clicks on the status bar
		return STATUS;
	}

	else	
	{
		if (y >= 0 && y < ToolBarHeight)
		{
			if (x < MenuIconWidth - 20)
				return TO_DRAW;
			else if (x < (10 * MenuOperationWidth + 80) && x>10 * MenuOperationWidth)
				return PLAY_COLOR;
			else if (x < (12 * MenuOperationWidth + 80) && x>12 * MenuOperationWidth)
				return PLAY_SHAPE;
		}
	}
}

////////////////////////////////////////////////////



//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(BkGrndColor);
	pW->SetPen(BkGrndColor, 1);
	pW->DrawRectangle(0, ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar()
{

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu icon
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuIcon
	string MenuIconImages[DRAW_ICON_COUNT];
	MenuIconImages[ICON_RECT] = "images\\MenuIcons\\Menu_Rect.jpg";
	MenuIconImages[ICON_TRI] = "images\\MenuIcons\\Menu_Tri.jpg";
	MenuIconImages[ICON_CIR] = "images\\MenuIcons\\Menu_Cir.jpg";
	MenuIconImages[ICON_SQE] = "images\\MenuIcons\\Menu_Sqe.jpg";
	MenuIconImages[ICON_OVAL] = "images\\MenuIcons\\Menu_Oval.jpg";
	MenuIconImages[ICON_RPOL] = "images\\MenuIcons\\Menu_Rpol.jpg";
	MenuIconImages[ICON_IRPOL] = "images\\MenuIcons\\Menu_IRpol.jpg";
	MenuIconImages[ICON_LINE] = "images\\MenuIcons\\Menu_Line.jpg";
	MenuIconImages[ICON_DRAW_CLR] = "images\\MenuIcons\\color.jpg";
	MenuIconImages[ICON_EXIT] = "images\\MenuIcons\\Menu_Exit.jpg";

	//TODO: Prepare images for each menu icon and add it to the list

	//Draw menu icon one image at a time
	for (int i = 0; i < DRAW_ICON_COUNT; i++)
		pWind->DrawImage(MenuIconImages[i], i * MenuIconWidth, 0, MenuIconWidth, ToolBarHeight);

	//draw Exit icon
	pWind->DrawImage(MenuIconImages[ICON_EXIT], width - MenuIconWidth, 0, MenuIconWidth, ToolBarHeight - 3);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);

}
void GUI::ClearDrawArea() const
{
	pWind->SetPen(BkGrndColor, 1);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(MsgColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, height - (int)(0.75 * StatusBarHeight), msg);
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreateDrawOperationToolBar()
{

	string MenuOperationImages[DRAW_OPERATION_COUNT];
	MenuOperationImages[ITM_LOAD] = "images\\MenuItems\\Menu_Load.jpg";
	MenuOperationImages[ITM_SAVE] = "images\\MenuItems\\Menu_Save.jpg";
	MenuOperationImages[ITM_COPY] = "images\\MenuItems\\Menu_Copy.jpg";
	MenuOperationImages[ITM_PASTE] = "images\\MenuItems\\Menu_Paste.jpg";
	MenuOperationImages[ITM_DELETE] = "images\\MenuItems\\Menu_Delete.jpg";
	MenuOperationImages[ITM_ROTATE] = "images\\MenuItems\\Menu_Rotate.jpg";
	MenuOperationImages[ITM_MOVE] = "images\\MenuItems\\Menu_Move.jpg";
	MenuOperationImages[ITM_SEND_TO_BACK] = "images\\MenuItems\\Menu_send_to_back.jpg";
	MenuOperationImages[ITM_BRING_TO_FRONT] = "images\\MenuItems\\Menu_bring_to_front.jpg";
	MenuOperationImages[ITM_RESIZE] = "images\\MenuItems\\Menu_Resize.jpg";


	for (int i = 0; i < DRAW_OPERATION_COUNT; i++)
		pWind->DrawImage(MenuOperationImages[i], 0, (i + 1) * ToolBarHeight, MenuOperationWidth - 3, ToolBarHeight);

	//Draw a line next to Operation Menu
	pWind->SetPen(RED, 3);
	pWind->DrawLine(MenuOperationWidth - 1.5, ToolBarHeight, MenuOperationWidth - 1.5, height - StatusBarHeight);
}

void GUI::deleteDrawOperationToolBar() const
{
	pWind->SetPen(BkGrndColor, 1);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(0, ToolBarHeight, MenuOperationWidth, height - StatusBarHeight);
}

void GUI::ClearDrawArea() const
{
	pWind->SetPen(BkGrndColor, 1);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(MsgColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, height - (int)(0.75 * StatusBarHeight), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const	//get current drwawing color
{
	return DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{
	return FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int GUI::getCrntPenWidth() const		//get current pen width
{
	return PenWidth;
}

//======================================================================================//
//								shapes Drawing Functions								//
//======================================================================================//

void GUI::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo) const
{
	color DrawingClr;
	if (RectGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

}
void GUI::DrawTRI(Point P1, Point P2,Point P3, GfxInfo TRIGfxInfo) const
{
	color DrawingClr;
	if (TRIGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = TRIGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, TRIGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (TRIGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TRIGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);

}

void GUI::DrawLINE(Point P1, Point P2, GfxInfo LINEGfxInfo) const
{
	color DrawingClr;
	if (LINEGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = LINEGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, LINEGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (LINEGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(LINEGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);

}
void GUI::DrawSquare(Point P1, Point P2, GfxInfo GfxInfo) const
{
	long x1, y1, sideL;
	x1 = (P2.x - P1.x) * (P2.x - P1.x);
	y1 = (P2.y - P1.y) * (P2.y - P1.y);
	sideL = sqrt(x1 + y1);
	Point P2S;
	P2S = { (P1.x + sideL),(P1.y + sideL) };
	color DrawingClr;
	if (GfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = GfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, GfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (GfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(GfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawRectangle(P1.x, P1.y, P2S.x, P2S.y, style);

}
void GUI::DrawCircle(Point P1, Point P2, GfxInfo GfxInfo) const
{
	long x1, y1, RAD;
	x1 = (P2.x - P1.x) * (P2.x - P1.x);
	y1 = (P2.y - P1.y) * (P2.y - P1.y);
	RAD = sqrt(x1 + y1);

	color DrawingClr;
	if (GfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = GfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, GfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (GfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(GfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawCircle(P1.x, P1.y, RAD, style);
}
color GUI::GetCurrentDColor() const {
	window* x = CreateWind(400, 400, width / 4, height / 4);
	string image = "images//MenuIcons//color.jpg";
	x->DrawImage(image, 0, 0, 400, 400);

	Point temp;
	x->WaitMouseClick(temp.x, temp.y);
	color y = x->GetColor(temp.x, temp.y);
	delete x;
	return y;

}
void GUI::SetCrntDrawColor(color x) {

	DrawColor = x;
}

//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

