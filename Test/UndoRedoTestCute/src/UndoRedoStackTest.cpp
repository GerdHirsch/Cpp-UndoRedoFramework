/*
 * UndoRedoStackTest.cpp
 *
 *  Created on: 30.10.2016
 *      Author: Gerd
 */

#include "../include/UndoRedoStackTest.h"

void UndoRedoStackTest::IsUndoable(){
	UndoRedoManager& urMngr(getManager());

	urMngr.doIt(plus);
	ASSERT_EQUAL(true, urMngr.isUndoable());
}
void UndoRedoStackTest::IsRedoable(){
	UndoRedoManager& urMngr(getManager());

	urMngr.doIt(plus);
	urMngr.undo();
	ASSERT_EQUAL(true, urMngr.isRedoable());
}

void UndoRedoStackTest::DoIt(){
	UndoRedoManager& urMngr(getManager());

	Plus::throwException() = false;

	urMngr.doIt(Plus(calculator, plusValue));

	int expected = plusValue;
	int result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}
void UndoRedoStackTest::Undo(){
	UndoRedoManager& urMngr(getManager());

	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();

	int result = calculator.getResult();
	int expected { 0 };

	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(true, urMngr.isRedoable());
}
void UndoRedoStackTest::Redo(){
	UndoRedoManager& urMngr(getManager());

	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();

	urMngr.redo();

	int expected = plusValue;
	int result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}
void UndoRedoStackTest::DoItWithException(){
	UndoRedoManager& urMngr(getManager());

	Plus::throwException() = true;
	int result = calculator.getResult();
	int expected = 0;
	ASSERT_EQUAL(expected, result);

	try{
		urMngr.doIt(plus);
	}catch(...){}

	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}

void UndoRedoStackTest::UndoWithException(){
	UndoRedoManager& urMngr(getManager());

	urMngr.doIt(plus);

	int expected = plusValue;
	int result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	Plus::throwException() = true;

	try{
		urMngr.undo();
	}catch(...){
//		cout << "catch UndoWithException" << endl;
	}

	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}

void UndoRedoStackTest::RedoWithException(){
	UndoRedoManager& urMngr(getManager());

	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();
	Plus::throwException() = true;
	try{
		urMngr.redo();
	}catch(...){
//		cout << "catch RedoWithException" << endl;
	}

	int result = calculator.getResult();
	int expected { 0 };
	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(true, urMngr.isRedoable());
}

void UndoRedoStackTest::DoItExceptionNeutral(){
	UndoRedoManager& urMngr(getManager());

	Plus::throwException() = true;

	ASSERT_THROWS(urMngr.doIt(plus), std::logic_error);
}
//==========
void UndoRedoStackTest::UndoExceptionNeutral(){
	UndoRedoManager& urMngr(getManager());

	Plus::throwException() = false;
	urMngr.doIt(plus);
	Plus::throwException() = true;

	ASSERT_THROWS(urMngr.undo(), std::logic_error);
}
//==========
void UndoRedoStackTest::RedoExceptionNeutral(){
	UndoRedoManager& urMngr(getManager());

	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();
	Plus::throwException() = true;

	ASSERT_THROWS(urMngr.redo(), std::logic_error);
}


//cute::suite UndoRedoStackTest::make_suite(){
//	cute::suite s { };
//	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, DoIt));
//	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, DoItWithException));
//	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, DoItExceptionNeutral));
//	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, Undo));
//	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, UndoWithException));
//	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, UndoExceptionNeutral));
//	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, Redo));
//	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, RedoWithException));
//	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, RedoExceptionNeutral));
//	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, IsRedoable));
//	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, IsUndoable));
//	return s;
//}
