/*
 * UndoRedoStackTest.cpp
 *
 *  Created on: 30.10.2016
 *      Author: Gerd
 */

#include "../include/UndoRedoStackTest.h"


#include <iostream>
#include <exception>
using namespace std;

//void _UndoRedoStackTest::DoIt(){
//	char const* message = "DemoTest";
//	ASSERT_EQUAL_MESSAGE(message, 0, -1);
//}



void UndoRedoStackTest::DoIt(){
	Plus::throwException() = false;
	int result = calculator.getResult();
	int expected = 0;
	ASSERT_EQUAL(expected, result);
	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());

	urMngr.doIt(Plus(calculator, 3));

	expected = plusValue;
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}
void UndoRedoStackTest::DoItWithException(){
	cout << "UndoRedoStackTest::DoItWithException()" << endl;

	Plus::throwException() = true;
	int result = calculator.getResult();
	int expected = 0;
	ASSERT_EQUAL(expected, result);

	try{
		urMngr.doIt(plus);
	}catch(std::exception& e){}

	ASSERT_EQUAL(expected, result);
	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}

void UndoRedoStackTest::DoItExceptionNeutral(){
	Plus::throwException() = true;

	ASSERT_THROWS(urMngr.doIt(plus), std::logic_error);
}
//==========
void UndoRedoStackTest::Undo(){
	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();

	int result = calculator.getResult();
	int expected = 0;

	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}
void UndoRedoStackTest::UndoWithException(){
	urMngr.doIt(plus);
	Plus::throwException() = true;
	try{
		urMngr.undo();
	}catch(std::exception& e){
		cout << "catch UndoWithException" << endl;
	}

	int result = calculator.getResult();
	int expected = plusValue;

	ASSERT_EQUAL(expected, result);
	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}

void UndoRedoStackTest::UndoExceptionNeutral(){
	Plus::throwException() = false;
	urMngr.doIt(plus);
	Plus::throwException() = true;

	ASSERT_THROWS(urMngr.undo(), std::logic_error);
}
//==========
void UndoRedoStackTest::Redo(){
	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();

	int result = calculator.getResult();
	int expected = plusValue;

	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(true, urMngr.isRedoable());

	ASSERT_EQUAL(expected, result);

	urMngr.redo();

	result = calculator.getResult();
	expected = 0;

	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}
void UndoRedoStackTest::RedoWithException(){
	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();
	Plus::throwException() = true;
	try{
		urMngr.redo();
	}catch(std::exception& e){
		cout << "catch UndoWithException" << endl;
	}

	int result = calculator.getResult();
	int expected = 0;

	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(true, urMngr.isRedoable());
}

void UndoRedoStackTest::RedoExceptionNeutral(){
	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();
	Plus::throwException() = true;

	ASSERT_THROWS(urMngr.redo(), std::logic_error);
}

