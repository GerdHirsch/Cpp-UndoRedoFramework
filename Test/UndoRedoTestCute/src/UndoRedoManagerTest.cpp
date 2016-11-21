/*
 * UndoRedoManagerTest.cpp
 *
 *  Created on: 30.10.2016
 *      Author: Gerd
 */

#include "../include/UndoRedoManagerTest.h"

#include <iostream>
//
//void UndoRedoManagerTest::IsModifiedSimple(){
//	UndoRedoManager& urMngr(getSUT());
//
//	ASSERT_EQUALM("new Manager must be unmodified!", false, urMngr.isModified());
//
//	urMngr.doIt(plus);
//	urMngr.doIt(plus);
//	ASSERT_EQUALM("Manager with two Commands must be modified!",
//					true, urMngr.isModified());
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
//}
//void UndoRedoManagerTest::IsModifiedAndIsRedoableWithNewCommand(){
//	UndoRedoManager& urMngr(getSUT());
//
//	urMngr.doIt(plus);
//	urMngr.doIt(plus); // modified Count == 2
//	ASSERT_EQUAL(true, urMngr.isModified());
//
//	// modified Count == 0 undoStack.size == 1
//	urMngr.resetModified();
//	ASSERT_EQUAL(false, urMngr.isModified());
//
//	urMngr.undo(); // -1
//	ASSERT_EQUAL(true, urMngr.isModified());
//	urMngr.redo(); // 0
//	ASSERT_EQUAL(false, urMngr.isModified());
//	urMngr.undo(); // -1
//	ASSERT_EQUAL(true, urMngr.isModified());
//
//	// NewCommand danach kommen wir nicht mehr
//	// in den unmodified State
//	urMngr.doIt(plus); // modified Count == 3 undoStack.size == 2
//	ASSERT_EQUAL(true, urMngr.isModified());
//	//nach neuem Command darf kein redo mehr möglich sein
//	ASSERT_EQUAL(false, urMngr.isRedoable());
//
//	while(urMngr.isUndoable()){
//		urMngr.undo();
//		ASSERT_EQUAL(true, urMngr.isModified());
//	}
//}
//void UndoRedoManagerTest::ResetModified(){
//	UndoRedoManager& urMngr(getSUT());
//
//	urMngr.doIt(plus);
//	urMngr.resetModified();
//	ASSERT_EQUAL(false, urMngr.isModified());
//}
//void UndoRedoManagerTest::IsModifiedwithExceptionDoIt(){
//	UndoRedoManager& urMngr(getSUT());
//
//	ASSERT_EQUAL(false, urMngr.isModified());
//	ASSERT_EQUAL(false, urMngr.isUndoable());
//	ASSERT_EQUAL(false, urMngr.isRedoable());
//
//	Plus::throwException() = true;
//
//	try{
//		urMngr.doIt(plus);
//	}catch (std::exception& e){
//			std::cout << "catch: " << e.what() << std::endl;
//	}
//	ASSERT_EQUAL(false, urMngr.isModified());
//	ASSERT_EQUAL(false, urMngr.isUndoable());
//	ASSERT_EQUAL(false, urMngr.isRedoable());
//}
//void UndoRedoManagerTest::IsModifiedtwithExceptionUndo(){
//	UndoRedoManager& urMngr(getSUT());
//
//	ASSERT_EQUAL(false, urMngr.isModified());
//	ASSERT_EQUAL(false, urMngr.isUndoable());
//	ASSERT_EQUAL(false, urMngr.isRedoable());
//
//	urMngr.doIt(plus);
//	ASSERT_EQUAL(true, urMngr.isModified());
//	ASSERT_EQUAL(true, urMngr.isUndoable());
//	ASSERT_EQUAL(false, urMngr.isRedoable());
//
//	Plus::throwException() = true;
//
//	try{
//		urMngr.undo();
//	}catch (std::exception& e){
////			System.out.println("catch: " + e.getMessage());
//	}
//	ASSERT_EQUAL(true, urMngr.isModified());
//	ASSERT_EQUAL(true, urMngr.isUndoable());
//	ASSERT_EQUAL(false, urMngr.isRedoable());
//}
//void UndoRedoManagerTest::IsModifiedtwithExceptionRedo(){
//	UndoRedoManager& urMngr(getSUT());
//
//	ASSERT_EQUAL(false, urMngr.isModified());
//	ASSERT_EQUAL(false, urMngr.isUndoable());
//	ASSERT_EQUAL(false, urMngr.isRedoable());
//
//	urMngr.doIt(plus);
//	urMngr.doIt(plus);
//	urMngr.undo();
//	ASSERT_EQUAL(true, urMngr.isModified());
//	ASSERT_EQUAL(true, urMngr.isUndoable());
//	ASSERT_EQUAL(true, urMngr.isRedoable());
//
//	urMngr.resetModified();
//	ASSERT_EQUAL(false, urMngr.isModified());
//
//	Plus::throwException() = true;
//
//	try{
//		urMngr.undo();
//	}catch (std::exception& e){
////			System.out.println("catch: " + e.getMessage());
//	}
//	ASSERT_EQUAL(false, urMngr.isModified());
//	ASSERT_EQUAL(true, urMngr.isUndoable());
//	ASSERT_EQUAL(true, urMngr.isRedoable());
//
//	try{
//		urMngr.redo();
//	}catch (std::exception& e){
////			System.out.println("catch: " + e.getMessage());
//	}
//	ASSERT_EQUAL(false, urMngr.isModified());
//	ASSERT_EQUAL(true, urMngr.isUndoable());
//	ASSERT_EQUAL(true, urMngr.isRedoable());
//}
//
//void UndoRedoManagerTest::DoItExceptionNeutral(){
//	UndoRedoManager& urMngr(getSUT());
//
//	Plus::throwException() = true;
//	ASSERT_THROWSM("Command throws but Manager not!",
//			urMngr.doIt(plus), std::logic_error);
//}
//void UndoRedoManagerTest::UndoExceptionNeutral(){
//	UndoRedoManager& urMngr(getSUT());
//
//	urMngr.doIt(plus);
//	Plus::throwException() = true;
//	ASSERT_THROWSM("Command throws but Manager not!",
//			urMngr.undo(), std::logic_error);
//}
//void UndoRedoManagerTest::RedoExceptionNeutral(){
//	UndoRedoManager& urMngr(getSUT());
//
//	urMngr.doIt(plus);
//	urMngr.undo();
//	Plus::throwException() = true;
//	ASSERT_THROWSM("Command throws but Manager not!",
//			urMngr.redo(), std::logic_error);
//}
//
//cute::suite UndoRedoManagerTest::make_suite(){
//	cute::suite s { };
//	s.push_back(CUTE_SMEMFUN(UndoRedoManagerTest, IsModifiedSimple));
//	s.push_back(CUTE_SMEMFUN(UndoRedoManagerTest, IsModifiedAndIsRedoableWithNewCommand));
//	s.push_back(CUTE_SMEMFUN(UndoRedoManagerTest, ResetModified));
//	s.push_back(CUTE_SMEMFUN(UndoRedoManagerTest, IsModifiedwithExceptionDoIt));
//	s.push_back(CUTE_SMEMFUN(UndoRedoManagerTest, IsModifiedtwithExceptionUndo));
//	s.push_back(CUTE_SMEMFUN(UndoRedoManagerTest, IsModifiedtwithExceptionRedo));
//	s.push_back(CUTE_SMEMFUN(UndoRedoManagerTest, DoItExceptionNeutral));
//	s.push_back(CUTE_SMEMFUN(UndoRedoManagerTest, RedoExceptionNeutral));
//	s.push_back(CUTE_SMEMFUN(UndoRedoManagerTest, UndoExceptionNeutral));
//	return s;
//}
