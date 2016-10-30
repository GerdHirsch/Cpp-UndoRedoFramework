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

	typedef void(UndoRedoStackTest::*TestMethod)();
	TestMethod testMethod;
public:
	UndoRedoStackTest(TestMethod testMethod) : testMethod(testMethod){}

	void operator()(){
		(this->*testMethod)();
	}

	void testDoIt();
	void testDoItWithException();
	void testDoItExceptionNeutral();

	void testUndo();
	void testUndoWithException();
	void testUndoExceptionNeutral();
	void testRedo();
	void testRedoWithException();
	void testRedoExceptionNeutral();
};

#endif /* UNDOREDOSTACKTEST_H_ */
