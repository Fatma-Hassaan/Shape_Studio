#pragma once
#ifndef EXIT_H
#define EXIT_H
#include "operation.h"

//Exit Action class
class Exit : public operation
{
private:
	int shapeCount;
public:
	Exit(controller* pControl);
	void readoperationParameters() override;

	//Exit the program
	void Execute() override;

};

#endif
