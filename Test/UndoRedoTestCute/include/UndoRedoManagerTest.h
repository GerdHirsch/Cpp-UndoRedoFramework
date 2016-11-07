/*
 * UndoRedoManagerTest.h
 *
 *  Created on: 30.10.2016
 *      Author: Gerd
 */

#ifndef SRC_UNDOREDOMANAGERTEST_H_
#define SRC_UNDOREDOMANAGERTEST_H_

#include "UndoRedoStackTest.h"

class UndoRedoManagerTest : public UndoRedoStackTest<UndoRedoManager>
{

public:
	void IsModifiedSimple();
	void IsModifiedAndIsRedoableWithNewCommand();
	void ResetModified();

	void IsModifiedwithExceptionDoIt();
	void IsModifiedtwithExceptionUndo();
	void IsModifiedtwithExceptionRedo();

	void DoItExceptionNeutral();
	void UndoExceptionNeutral();
	void RedoExceptionNeutral();

//	static cute::suite make_suite();
};

#define UndoRedoManagerTests(DerivedTest)\
	UndoRedoStackTests(DerivedTest)	\
	s.push_back(CUTE_SMEMFUN(DerivedTest, IsModifiedSimple));				\
	s.push_back(CUTE_SMEMFUN(DerivedTest, IsModifiedAndIsRedoableWithNewCommand));\
	s.push_back(CUTE_SMEMFUN(DerivedTest, ResetModified));					\
	s.push_back(CUTE_SMEMFUN(DerivedTest, IsModifiedwithExceptionDoIt));	\
	s.push_back(CUTE_SMEMFUN(DerivedTest, IsModifiedtwithExceptionUndo));	\
	s.push_back(CUTE_SMEMFUN(DerivedTest, IsModifiedtwithExceptionRedo));	\
	s.push_back(CUTE_SMEMFUN(DerivedTest, DoItExceptionNeutral));			\
	s.push_back(CUTE_SMEMFUN(DerivedTest, UndoExceptionNeutral));			\
	s.push_back(CUTE_SMEMFUN(DerivedTest, RedoExceptionNeutral));

#endif /* SRC_UNDOREDOMANAGERTEST_H_ */
