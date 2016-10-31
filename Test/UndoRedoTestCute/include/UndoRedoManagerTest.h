/*
 * UndoRedoManagerTest.h
 *
 *  Created on: 30.10.2016
 *      Author: Gerd
 */

#ifndef SRC_UNDOREDOMANAGERTEST_H_
#define SRC_UNDOREDOMANAGERTEST_H_

#include "UndoRedoTest.h"

class UndoRedoManagerTest //: public UndoRedoTest<UndoRedoManagerTest>
{

public:
//	using UndoRedoTest<UndoRedoManagerTest>::UndoRedoTest;

	void IsModifiedSimple();
	void IsModifiedAndIsRedoableWithNewCommand();
};

//TEST_CLASS(IsModifiedSimple, UndoRedoManagerTest)
//TEST_CLASS(IsModifiedAndIsRedoableWithNewCommand, UndoRedoManagerTest)

#endif /* SRC_UNDOREDOMANAGERTEST_H_ */
