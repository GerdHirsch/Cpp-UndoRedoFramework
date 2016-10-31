#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "../include/UndoRedoStackTest.h"
#include "../include/UndoRedoManagerTest.h"
#include "../include/CompositeCommandTest.h"

#include <iostream>
using namespace std;


void runAllTests(int argc, char const *argv[]){
	cute::suite s;

	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(UndoRedoStackTest::make_suite(), "UndoRedoStack");
	cute::makeRunner(lis,argc,argv)(UndoRedoManagerTest::make_suite(), "UndoRedoManager");
<<<<<<< HEAD
	cute::makeRunner(lis,argc,argv)(CompositeCommandTest::make_suite(), "UndoRedoManager");
=======
>>>>>>> branch 'add-tests' of https://github.com/GerdHirsch/Cpp-UndoRedoFramework.git
}

int main(int argc, char const *argv[]){
	cout << "main()" << endl;

//	Calculator calculator;
//	UndoRedoManagerImpl urMngr;
//	urMngr.doIt(Plus(calculator, 3));
//
//	cout << calculator.getResult() << endl;
    runAllTests(argc,argv);
    return 0;
}
/*
 *
class TestClass{
	typedef void(TestClass::*TestMethod)();
	TestMethod testMethod;
public:
	TestClass() : testMethod(&TestClass::test1){}
	TestClass(TestMethod testMethod) : testMethod(testMethod){}

	void operator()(){
		(this->*testMethod)();
	}
	void test1(){
		ASSERTM("start writing tests with Classes", false);
	}
	void test2(){
		ASSERTM("start writing tests with Classes", false);
	}
};

void thisIsATest() {
	ASSERTM("start writing tests", false);
}
 */


