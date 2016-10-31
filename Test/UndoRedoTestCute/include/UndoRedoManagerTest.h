/*
 * UndoRedoManagerTest.h
 *
 *  Created on: 30.10.2016
 *      Author: Gerd
 */

#ifndef SRC_UNDOREDOMANAGERTEST_H_
#define SRC_UNDOREDOMANAGERTEST_H_

#include "UndoRedoTest.h"

class UndoRedoManagerTest : public UndoRedoTest
{

public:
	void IsModifiedSimple();
	void IsModifiedAndIsRedoableWithNewCommand();
	void ResetModified();

	void IsModifiedtwithExceptionDoIt();
	void IsModifiedtwithExceptionUndo();
	void IsModifiedtwithExceptionRedo();

	void DoItExceptionNeutral();
	void UndoExceptionNeutral();
	void RedoExceptionNeutral();

	static cute::suite make_suite();
};


#endif /* SRC_UNDOREDOMANAGERTEST_H_ */
