#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "../include/UndoRedoStackByInheritanceTest.h"
#include "../include/UndoRedoStackByDelegationTest.h"
#include "../include/UndoRedoManagerByInheritanceTest.h"
#include "../include/UndoRedoManagerByDelegationTest.h"
#include "../include/DefaultCompositeCommandTest.h"

#include <iostream>

using namespace std;


void runAllTests(int argc, char const *argv[]){
	cout << "runAllTests()" << endl;

	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);

	cute::makeRunner(lis,argc,argv)(UndoRedoStackByInheritanceTest::make_suite(), "UndoRedoStack ByInheritance");
	cute::makeRunner(lis,argc,argv)(UndoRedoStackByDelegationTest::make_suite(), "UndoRedoStack ByDelegation");
	cute::makeRunner(lis,argc,argv)(UndoRedoManagerByInheritanceTest::make_suite(), "UndoRedoManager ByInheritance");
	cute::makeRunner(lis,argc,argv)(UndoRedoManagerByDelegationTest::make_suite(), "UndoRedoManager ByDelegation");
	cute::makeRunner(lis,argc,argv)(DefaultCompositeCommandTest::make_suite(), "CompositeCommand");
}

int main(int argc, char const *argv[]){
	cout << "UndoRedoDefaultTest" << endl;

    runAllTests(argc,argv);
    return 0;
}
