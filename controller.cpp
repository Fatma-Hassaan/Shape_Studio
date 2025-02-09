#include "controller.h"
#include "operations\opAddRect.h"


//Constructor
controller::controller()
{
	pGraph = new Graph;
	pGUI = new GUI;	//Create GUI object
}

//==================================================================================//
//								operations-Related Functions							//
//==================================================================================//
operationType controller::GetUseroperation() const
{
	//Ask the input to get the operation from the user.
	return pGUI->GetUseroperation();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an operation and executes it
operation* controller::createOperation(operationType OpType)
{
	operation* pOp = nullptr;
	
	//According to operation Type, create the corresponding operation object
	switch (OpType)
	{
		case DRAW_RECT:
			pOp = new opAddRect(this);
			break;
		case DRAW_TRI:
	               pOp = new opAddTri(this);
	               break;

		case DRAW_LINE:
			///create AddLineoperation here
			pOp = new opAddLine(this);
			break;
		case UNDO:
	               pOp = new UndoRedo(this, UndoRedo::MODE_UNDO);
	               break;

                case REDO:
	               pOp = new UndoRedo(this, UndoRedo::MODE_REDO);
	               break;

                case SEND_TO_BACK:
	               pOp = new SendToBack(this);
	               break;

                case SAVE:
	              pOp = new Save(this);
	              break;

                case LOAD:
	             pOp = new Load(this);
	             break;
		case ADD_IMAGE:
                pOp = new opAddImage(this);
                 break;
		case COPY_SHAPE:
            pOp = new opCopyShape(this);
            break;
                case PASTE_SHAPE:
            pOp = new opPasteShape(this);
            break;
                 case DELETE_SHAPE:
            pOp = new opDeleteShape(this);
            break;

		case EXIT:
			///create Exitoperation here
			
			break;
		
		case STATUS:	//a click on the status bar ==> no operation
			break;
	}

	return pOp;
	
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all shapes on the user interface
void controller::UpdateInterface() const
{	
	pGraph->Draw(pGUI);
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the UI
GUI *controller::GetUI() const
{	return pGUI; }
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the Graph
Graph* controller::getGraph() const
{
	return pGraph;
}

void controller::setSelectedShape(shape* sp)
{
	selectedShape = sp;
}

shape* controller::getSelectedShape() const
{
	return selectedShape;
}

void controller::exit()
{
	delete pGUI; delete pGraph;
	pGUI = nullptr; pGraph = nullptr;
}



//Destructor
controller::~controller()
{
	delete pGUI;
	delete pGraph;
	
}



//==================================================================================//
//							Run function											//
//==================================================================================//
void controller::Run()
{
	operationType OpType;
	do
	{
		//1. Ask the GUI to read the required operation from the user
		OpType = GetUseroperation();

		//2. Create an operation coresspondingly
		operation* pOpr = createOperation(OpType);
		 
		//3. Execute the created operation
		if (pOpr)
		{
			pOpr->Execute();//Execute
			delete pOpr;	//operation is not needed any more ==> delete it
			pOpr = nullptr;
		}

		//Update the interface
		UpdateInterface();

	} while (OpType != EXIT);

}
