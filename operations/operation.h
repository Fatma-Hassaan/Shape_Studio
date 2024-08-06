#pragma once
#include "..\DefS.h"
#include "..\GUI\GUI.h"

class controller; //forward class declaration
//Base class for all possible operations
class operation
{
protected:
	controller *pControl;	//operations needs control to do their job

public:

	operation(controller *pCont) { pControl = pCont; }	//constructor
	virtual ~operation(){}
        virtual void readActionParameters() = 0;

	//Execute operation (code depends on operation type)
	virtual void Execute() =0;

	//To undo this operation (code depends on operation type)
	//virtual void Undo()=0;

	//To redo this operation (code depends on operation type)
	//virtual void Redo()=0;

};

/////////////////////////////////	SHAPES OPERATIONS	/////////////////////////////////
class opAddRect : public operation
{
public:
	opAddRect(controller* pCont);
	virtual ~opAddRect();

	//Add rectangle to the controller
	virtual void Execute();

};

class opAddSquare : public operation
{
public:
	opAddSquare(controller* pCont);
	virtual ~opAddSquare();

	//Add Square to the controller
	virtual void Execute();

};

class opAddTriangle : public operation
{
public:
	opAddTriangle(controller* pCont);
	virtual ~opAddTriangle();

	//Add Triangle to the controller
	virtual void Execute();

};

class opAddCircle : public operation
{
public:
	opAddCircle(controller* pCont);
	virtual ~opAddCircle();

	//Add Circle to the controller
	virtual void Execute();

};

class opAddLine : public operation
{
public:
	opAddLine(controller* pCont);
	virtual ~opAddLine();

	//Add Line to the controller
	virtual void Execute();

};
