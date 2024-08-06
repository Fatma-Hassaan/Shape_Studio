#pragma once
#include "operation.h"



class Load :public operation
{
	operationType confirm;
public:
	Load(controller*);
	void readoperationParameters() override;
	void Execute() override;
	void readshapes(ifstream&) const;	
	void quickLoad() const;	
	void loadFromFile(string) const;
};