/*
 * test.cpp
 *
 *  Created on: 15.01.2018
 *      Author: Gerd
 */

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"


#include "../include/UndoRedoStackCustomizedByDelegationTest.h"

#include <iostream>
using namespace std;


void runAllTests(int argc, char const *argv[]){
	cout << "runAllTests()" << endl;

	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);

	cute::makeRunner(lis,argc,argv)(CustomizedUndoRedoStackByDelegationTest::make_suite(), "Customized UndoRedoStack ByDelegation");

}

int main(int argc, char const *argv[]){
	cout << "UndoRedoCustomizedTest" << endl;
	 runAllTests(argc,argv);
}
