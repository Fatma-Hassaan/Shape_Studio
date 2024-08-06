#pragma once
#include "operation.h"
class Save :public operation
{
	operationType Confirm;	//An ActionType variable to act as a confirmation for the action
	void savetoFile(string) const;
public:
	Save(controller*);
	void readoperationParameters() override;
	void Execute() override;
	void quickSave() const;	//Saves without confirmation or asking for a name for the file
	void saveForUndo(bool = false) const;
};
