/*
 * DefaultUndoRedoManagerTest.h
 *
 *  Created on: 04.11.2016
 *      Author: Gerd
 */

#ifndef INCLUDE_DEFAULTUNDOREDOMANAGERTEST_H_
#define INCLUDE_DEFAULTUNDOREDOMANAGERTEST_H_

#include <memory>

//#include <include/UndoRedoManager.h>
#include <include/UndoRedoManagerImpl.h>
#include "UndoRedoManagerTest.h"

class DefaultUndoRedoManagerTest :
		public UndoRedoManagerTest<UndoRedoFramework::ByInheritance::UndoRedoManager> {
public:
	using base_type = UndoRedoManagerTest<UndoRedoFramework::ByInheritance::UndoRedoManager>;
	using base_type::SUT;
	using UndoRedoManagerImpl = UndoRedoFramework::ByInheritance::UndoRedoManagerImpl;


	virtual std::unique_ptr<SUT> createSUT() const override {
		return std::unique_ptr<SUT>(
				new UndoRedoManagerImpl
		);
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
