/*
 * UndoRedoStackTest.h
 *
 *  Created on: 30.10.2016
 *      Author: Gerd
 */

#ifndef UNDOREDOSTACKTEST_H_
#define UNDOREDOSTACKTEST_H_

#include "UndoRedoTest.h"

class UndoRedoStackTest : public UndoRedoTest {

public:
	void DoIt();
	void DoItWithException();
	void DoItExceptionNeutral();

	void Undo();
	void UndoWithException();
	void UndoExceptionNeutral();
	void Redo();
	void RedoWithException();
	void RedoExceptionNeutral();

	static cute::suite make_suite();
};

#endif /* UNDOREDOSTACKTEST_H_ */
