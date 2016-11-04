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

	void IsUndoable();
	void IsRedoable();

//	static cute::suite make_suite();
};
#define UndoRedoStackTests(DerivedTest)									\
		s.push_back(CUTE_SMEMFUN(DerivedTest, DoIt));					\
		s.push_back(CUTE_SMEMFUN(DerivedTest, DoItWithException));		\
		s.push_back(CUTE_SMEMFUN(DerivedTest, DoItExceptionNeutral));	\
		s.push_back(CUTE_SMEMFUN(DerivedTest, Undo));					\
		s.push_back(CUTE_SMEMFUN(DerivedTest, UndoWithException));		\
		s.push_back(CUTE_SMEMFUN(DerivedTest, UndoExceptionNeutral));	\
		s.push_back(CUTE_SMEMFUN(DerivedTest, RedoWithException));		\
		s.push_back(CUTE_SMEMFUN(DerivedTest, RedoExceptionNeutral));	\
		s.push_back(CUTE_SMEMFUN(DerivedTest, IsUndoable));				\
		s.push_back(CUTE_SMEMFUN(DerivedTest, IsRedoable));

#endif /* UNDOREDOSTACKTEST_H_ */
