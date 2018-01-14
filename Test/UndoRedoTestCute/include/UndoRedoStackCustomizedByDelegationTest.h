/*
 * DefaultUndoRedoStackTest.h
 *
 *  Created on: 04.11.2016
 *      Author: Gerd
 */

#ifndef CUSTOMIZED_UNDOREDOSTACKDELEGATIONTEST_H_
#define CUSTOMIZED_UNDOREDOSTACKDELEGATIONTEST_H_

#include <memory>

#include <UndoRedoCustomized/UndoRedoStackImpl.h>
#include "UndoRedoStackTest.h"


class CustomizedUndoRedoStackByDelegationTest : public UndoRedoStackTest<UndoRedoFramework::UndoRedoStack> {
public:
	using this_type = CustomizedUndoRedoStackByDelegationTest;
	using base_type = UndoRedoStackTest<UndoRedoFramework::UndoRedoStack>;
	using base_type::SUT;
	using UndoRedoStackImpl = UndoRedoCustomized::UndoRedoStackImpl;

	virtual std::unique_ptr<SUT> createSUT() const override {
		return std::unique_ptr<SUT>( new UndoRedoStackImpl );
	}
	static cute::suite make_suite(){
		return base_type::make_suite<this_type>();
	}

};

#endif /* CUSTOMIZED_UNDOREDOSTACKDELEGATIONTEST_H_ */
