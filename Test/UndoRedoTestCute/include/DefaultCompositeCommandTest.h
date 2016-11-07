/*
 * DefaultCompositeCommandTest.h
 *
 *  Created on: 04.11.2016
 *      Author: Gerd
 */

#ifndef INCLUDE_DEFAULTCOMPOSITECOMMANDTEST_H_
#define INCLUDE_DEFAULTCOMPOSITECOMMANDTEST_H_

#include <include/UndoRedoStackImpl.h>
#include <include/CompositeCommandImpl.h>
#include "CompositeCommandTest.h"


class DefaultCompositeCommandTest : public CompositeCommandTest {
public:

	virtual std::unique_ptr<UndoRedoStack> createURStack() const override {
		return
			std::unique_ptr<UndoRedoStack>(new UndoRedoStackImpl());
	}

	virtual std::unique_ptr<CompositeCommand> createSUT() const override {
		return
			std::unique_ptr<CompositeCommand>(
					new CompositeCommandImpl( (UndoRedoStackImpl()) )
			);
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
