/*
 * DefaultUndoRedoManagerTest.h
 *
 *  Created on: 04.11.2016
 *      Author: Gerd
 */

#ifndef INCLUDE_DEFAULTUNDOREDOMANAGERTEST_H_
#define INCLUDE_DEFAULTUNDOREDOMANAGERTEST_H_

#include <memory>

#include <include/UndoRedoManager.h>
#include "UndoRedoManagerTest.h"

class DefaultUndoRedoManagerTest : public UndoRedoManagerTest {
public:
	virtual std::unique_ptr<UndoRedoManager> createManager() const override {
		return std::unique_ptr<UndoRedoManager>(new UndoRedoManagerImpl);
	}
	static cute::suite make_suite();
};
inline
cute::suite DefaultUndoRedoManagerTest::make_suite(){
	cute::suite s { };
	UndoRedoManagerTests(DefaultUndoRedoManagerTest)
	return s;
}



#endif /* INCLUDE_DEFAULTUNDOREDOMANAGERTEST_H_ */
