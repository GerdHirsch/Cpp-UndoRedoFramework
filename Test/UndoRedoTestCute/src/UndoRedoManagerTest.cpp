/*
 * UndoRedoManagerTest.cpp
 *
 *  Created on: 30.10.2016
 *      Author: Gerd
 */

#include "../include/UndoRedoManagerTest.h"

void UndoRedoManagerTest::IsModifiedSimple(){
//	ASSERT_EQUAL(false, urMngr.isModified());
//
//	urMngr.doIt(plus);
//	urMngr.doIt(plus);
//	ASSERT_EQUAL(true, urMngr.isModified());
//	urMngr.undo();
//	ASSERT_EQUAL(true, urMngr.isModified());
//
//	urMngr.resetModified();
//	ASSERT_EQUAL(false, urMngr.isModified());
//
//	urMngr.redo();
//	ASSERT_EQUAL(true, urMngr.isModified());
//	urMngr.undo();
//	ASSERT_EQUAL(false, urMngr.isModified());
//	urMngr.undo();
//	ASSERT_EQUAL(true, urMngr.isModified());
//	urMngr.redo();
//	ASSERT_EQUAL(false, urMngr.isModified());
//	urMngr.redo();
//	ASSERT_EQUAL(true, urMngr.isModified());
}
void UndoRedoManagerTest::IsModifiedAndIsRedoableWithNewCommand(){

}

cute::suite make_suite(){
	cute::suite s;
	s.push_back(CUTE_SMEMFUN(UndoRedoManagerTest, IsModifiedSimple));
	return s;
}
