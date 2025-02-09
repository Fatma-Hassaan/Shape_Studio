#pragma once



#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"
#include <iostream>
#include <Windows.h>
#include <commdlg.h>
#include <string>
using namespace std;

struct Point	//To be used for shapes points
{
	int x, y;
};

struct GfxInfo	//Graphical info common for all shapes (you may add more members)
{
	color DrawClr;	//Draw color of the shape
	color FillClr;	//Fill color of the shape
	bool isFilled;	//shape Filled or not
	int BorderWdth;	//Width of shape borders
	bool isSelected;	//true if the shape is selected.
};




class GUI
{
	enum GUI_MODE	
	{
		MODE_DRAW,	
		MODE_PLAY	
	};


	enum MenuIcon //The icons of the menu (you should add more icons)
	{
		//Note: Icons are ordered here as they appear in menu
		//If you want to change the menu icons order, change the order here
		ICON_GAME,
		ICON_RECT,		//Recangle icon in menu
		ICON_TRI,		//Triangle icon in menu
		ICON_CIR,
		ICON_SQE,
		ICON_OVAL,
		ICON_RPOL,
		ICON_IRPOL,
		ICON_LINE,
		//TODO: Add more icons names here
		ICON_FILL_CLR,
		ICON_DRAW_CLR,
		ICON_UNDO,
		ICON_REDO,
                ICON_COPY,	    //Copy  icon in menu
		//ICON_CUT,	    //Cut  icon in menu
		ICON_PASTE,	    //Paste  icon in menu
                ICON_DELETE,
		ICON_EXIT,		//Exit icon
                ICON_STICK_IMAGE,
		DRAW_ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum

	};

	enum DrawMenuOperation {

		ITM_LOAD,
		ITM_SAVE,
		ITM_COPY,
		ITM_PASTE,
		ITM_DELETE,
		ITM_ROTATE,
		ITM_MOVE,
		ITM_SEND_TO_BACK,
		ITM_BRING_TO_FRONT,
		ITM_RESIZE,


		DRAW_OPERATION_COUNT, //no. of operation items

	};

	GUI_MODE InterfaceMode;
	int	width, height,	//Window width and height
		wx, wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuIconWidth,		//Width of each icon in toolbar menu
	    MenuOperationWidth;


	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed



	window* pWind;

public:

	GUI();

	// Input Functions  ---------------------------
	void GetPointClicked(int& x, int& y) const;//Get coordinate where user clicks
	string GetSrting() const;	 //Returns a string entered by the user
	operationType GetUseroperation() const; //Read the user click and map to an operation
	


	// Output Functions  ---------------------------
	window* CreateWind(int, int, int, int) const; //creates the application window
	void CreateDrawToolBar();	//creates Draw mode toolbar & menu
	void CreateDrawOperationToolBar() ; 
	void deleteDrawOperationToolBar() const; 
	void CreateStatusBar() const;	//create the status bar
        color GetColor() const;
        void SetCrntDrawColor(color x);
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area

	// -- shapes Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo) const;  //Draw a rectangle
	void DrawTRI(Point P1, Point P2, Point P3, GfxInfo TRIGfxInfo) const;
	void DrawLINE(Point P1, Point P2, GfxInfo LINEGfxInfo) const;
        void DrawSquare(Point P1, Point P2, GfxInfo GfxInfo) const;
        void DrawCircle(Point P1, Point P2, GfxInfo GfxInfo) const;

	///Make similar functions for drawing all other shapes.

	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width
        void changeFillColor(color); //Change Current Filling Color
        void changeDrawColor(color); //Change Current Drawing Color
        COLORREF currentColor;
        void DrawUndoRedoIcons(UndoRedo::MODES, bool) const;
        void drawOnToolbar(string, int) const;
        void drawOnoperationbar(string, int) const;

        
        void DrawImage(Point P1, Point P2, image* img) const; // Method to draw the image
        image* LoadImage(const string& filename) const; // Method to load an image
        
	~GUI();
};

