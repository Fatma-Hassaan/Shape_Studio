#pragma once
#include "operation.h"
#include <vector>

class UndoRedo :public operation
{
	static int historyCount;
	int mode;
	static vector<string> undoList;
	static vector<string> redoList;
	static  string currentFileName, nextFileName;

	void updateFileNamesAccordingTo(string) const;
public:
	enum MODES { MODE_UNDO, MODE_REDO };
	UndoRedo(controller*, int);
	void readoperationParameters() override;
	void Execute() override;
	static void eraseRedoList();
	static void incrementUndoList();
	static bool isUndoAvailable();
	static bool isRedoAvailable();
	static string getNextFileName();
	static string getCurrentFileName();
};