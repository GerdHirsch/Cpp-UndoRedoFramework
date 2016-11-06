/*
 * DefaultCompositeCommandTest.h
 *
 *  Created on: 04.11.2016
 *      Author: Gerd
 */

#ifndef INCLUDE_DEFAULTCOMPOSITECOMMANDTEST_H_
#define INCLUDE_DEFAULTCOMPOSITECOMMANDTEST_H_

#include <include/UndoRedoManager.h>
#include <include/CompositeCommand.h>
#include "CompositeCommandTest.h"


class DefaultCompositeCommandTest : public CompositeCommandTest {
public:
	virtual std::unique_ptr<UndoRedoManager> createManager() const override {
		return std::unique_ptr<UndoRedoManager>(new UndoRedoManagerImpl);
	}
	virtual std::unique_ptr<CompositeCommand> createCommand() const override {
		return std::unique_ptr<CompositeCommand>(new CompositeCommand(UndoRedoManagerImpl()));
	}
	static cute::suite make_suite();
};
inline
cute::suite DefaultCompositeCommandTest::make_suite(){
	cute::suite s { };
	CompositeCommandTests(DefaultCompositeCommandTest)
	return s;
}



#endif /* INCLUDE_DEFAULTCOMPOSITECOMMANDTEST_H_ */
