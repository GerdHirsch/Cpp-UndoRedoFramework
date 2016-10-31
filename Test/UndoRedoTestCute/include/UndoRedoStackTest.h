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
//	UndoRedoStackTest(TestMethod testMethod) :
//		UndoRedoTest(testMethod){}
	UndoRedoStackTest(TestMethod testMethod) :
		testMethod(testMethod){}

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

#define TEST_CLASS(Name, Base)				\
struct Name : Base{							\
	Name() : Base(&Base::test##Name){}		\
};											\

//struct DoIt : UndoRedoStackTest{
//	using UndoRedoStackTest::UndoRedoStackTest;
//};

TEST_CLASS(DoIt, UndoRedoStackTest)
TEST_CLASS(DoItWithException, UndoRedoStackTest)
TEST_CLASS(DoItExceptionNeutral, UndoRedoStackTest)

TEST_CLASS(Undo, UndoRedoStackTest)
TEST_CLASS(UndoWithException, UndoRedoStackTest)
TEST_CLASS(UndoExceptionNeutral, UndoRedoStackTest)

TEST_CLASS(Redo, UndoRedoStackTest)
TEST_CLASS(RedoWithException, UndoRedoStackTest)
TEST_CLASS(RedoExceptionNeutral, UndoRedoStackTest)


#endif /* UNDOREDOSTACKTEST_H_ */
