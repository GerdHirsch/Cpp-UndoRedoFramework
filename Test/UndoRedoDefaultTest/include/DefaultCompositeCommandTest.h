/*
 * DefaultCompositeCommandTest.h
 *
 *  Created on: 04.11.2016
 *      Author: Gerd
 */

#ifndef INCLUDE_DEFAULTCOMPOSITECOMMANDTEST_H_
#define INCLUDE_DEFAULTCOMPOSITECOMMANDTEST_H_

#include <UndoRedoFramework/ByInheritance/UndoRedoStackImpl.h>
#include <UndoRedoFramework/CompositeCommandImpl.h>
#include <UndoRedoTest/CompositeCommandTest.h>


class DefaultCompositeCommandTest : public CompositeCommandTest {
public:
	using this_type = DefaultCompositeCommandTest;
	using base_type = CompositeCommandTest;
	using base_type::SUT;
	using CompositeCommandImpl = UndoRedoFramework::CompositeCommandImpl;
	using UndoRedoStackImpl = UndoRedoFramework::ByInheritance::UndoRedoManagerImpl;
//	using UndoRedoStackImpl = UndoRedoFramework::ByInheritance::UndoRedoStackImpl;

	virtual std::unique_ptr<SUT> createSUT() const override {
		return
			std::unique_ptr<SUT>(
					new CompositeCommandImpl( (createURStack()) )
			);
		}


	virtual std::unique_ptr<UndoRedoStack> createURStack() const override {
		return
			std::unique_ptr<UndoRedoStack>(new UndoRedoStackImpl());
	}
	static cute::suite make_suite(){
		return base_type::make_suite<this_type>();
	}
};

#endif /* INCLUDE_DEFAULTCOMPOSITECOMMANDTEST_H_ */
