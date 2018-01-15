/*
 * UndoRedoManagerTest.h
 *
 *  Created on: 30.10.2016
 *      Author: Gerd
 */

#ifndef SRC_UNDOREDOMANAGERTEST_H_
#define SRC_UNDOREDOMANAGERTEST_H_

#include "UndoRedoStackTest.h"

template<class SUTType>
class UndoRedoManagerTest : public UndoRedoStackTest<SUTType>
{

public:
	using this_type = UndoRedoManagerTest;
	using base_type = UndoRedoStackTest<SUTType>;
	using base_type::make_suite;

	using typename base_type::SUT;

	using UndoRedoTest<SUT>::getSUT;
	using UndoRedoTest<SUT>::plus;
	using UndoRedoTest<SUT>::plusValue;
	using UndoRedoTest<SUT>::minus;
	using UndoRedoTest<SUT>::minusValue;
	using UndoRedoTest<SUT>::calculator;

	void IsModifiedSimple();
	void IsModifiedAndIsNotRedoableWithNewCommand();
	void ResetModified();
	void IsNotModifiedAfterDoItAndUndo();

	void IsModifiedwithExceptionDoIt();
	void IsModifiedtwithExceptionUndo();
	void IsModifiedtwithExceptionRedo();

	template<class DerivedTest>
	static cute::suite make_suite(){
		cute::suite s( base_type::template make_suite<DerivedTest>() );

		s.push_back(CUTE_SMEMFUN(DerivedTest, IsModifiedSimple));
		s.push_back(CUTE_SMEMFUN(DerivedTest, IsModifiedAndIsNotRedoableWithNewCommand));
		s.push_back(CUTE_SMEMFUN(DerivedTest, ResetModified));
		s.push_back(CUTE_SMEMFUN(DerivedTest, IsNotModifiedAfterDoItAndUndo));
		s.push_back(CUTE_SMEMFUN(DerivedTest, IsModifiedwithExceptionDoIt));
		s.push_back(CUTE_SMEMFUN(DerivedTest, IsModifiedtwithExceptionUndo));
		s.push_back(CUTE_SMEMFUN(DerivedTest, IsModifiedtwithExceptionRedo));

		return s;
	}
};

template<class SUTType>
inline
void UndoRedoManagerTest<SUTType>::IsNotModifiedAfterDoItAndUndo() {
	auto& urMngr(getSUT());
	urMngr.resetModified();

	urMngr.doIt(plus);
	urMngr.undo();
	ASSERT_EQUAL(false, urMngr.isModified());
}

template<class SUTType>
inline
void UndoRedoManagerTest<SUTType>::IsModifiedSimple(){
	auto& urMngr(this->getSUT());

	ASSERT_EQUALM("new Manager must be unmodified!", false, urMngr.isModified());

	urMngr.doIt(plus);
	urMngr.doIt(plus);
	ASSERT_EQUALM("Manager with two Commands must be modified!",
					true, urMngr.isModified());
	urMngr.undo();
	ASSERT_EQUAL(true, urMngr.isModified());

	urMngr.resetModified();
	ASSERT_EQUAL(false, urMngr.isModified());

	urMngr.redo();
	ASSERT_EQUAL(true, urMngr.isModified());
	urMngr.undo();
	ASSERT_EQUAL(false, urMngr.isModified());
	urMngr.undo();
	ASSERT_EQUAL(true, urMngr.isModified());
	urMngr.redo();
	ASSERT_EQUAL(false, urMngr.isModified());
	urMngr.redo();
	ASSERT_EQUAL(true, urMngr.isModified());
}
template<class SUTType>
inline
void UndoRedoManagerTest<SUTType>::IsModifiedAndIsNotRedoableWithNewCommand(){
	auto& urMngr(getSUT());

	urMngr.doIt(plus);
	urMngr.doIt(plus);
	ASSERT_EQUAL(true, urMngr.isModified());

	urMngr.resetModified();
	ASSERT_EQUAL(false, urMngr.isModified());

	urMngr.undo();
	ASSERT_EQUAL(true, urMngr.isModified());
	urMngr.redo();
	ASSERT_EQUAL(false, urMngr.isModified());
	urMngr.undo();
	ASSERT_EQUAL(true, urMngr.isModified());

	// NewCommand danach kommen wir nicht mehr
	// in den unmodified State
	urMngr.doIt(plus);
	ASSERT_EQUAL(true, urMngr.isModified());
	//nach neuem Command darf kein redo mehr möglich sein
	ASSERT_EQUAL(false, urMngr.isRedoable());

	while(urMngr.isUndoable()){
		urMngr.undo();
		ASSERT_EQUAL(true, urMngr.isModified());
	}
}
template<class SUTType>
inline
void UndoRedoManagerTest<SUTType>::ResetModified(){
	auto& urMngr(getSUT());

	urMngr.doIt(plus);
	urMngr.resetModified();
	ASSERT_EQUAL(false, urMngr.isModified());
}
template<class SUTType>
inline
void UndoRedoManagerTest<SUTType>::IsModifiedwithExceptionDoIt(){
	auto& urMngr(getSUT());

	ASSERT_EQUAL(false, urMngr.isModified());
	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());

	Plus::throwException() = true;

	ASSERT_THROWSM("Command throws but SUT not!",
			urMngr.doIt(plus), std::logic_error);

	ASSERT_EQUAL(false, urMngr.isModified());
	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}
template<class SUTType>
inline
void UndoRedoManagerTest<SUTType>::IsModifiedtwithExceptionUndo(){
	auto& urMngr(getSUT());

	ASSERT_EQUAL(false, urMngr.isModified());
	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());

	urMngr.doIt(plus);
	ASSERT_EQUAL(true, urMngr.isModified());
	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());

	Plus::throwException() = true;

	ASSERT_THROWSM("Command throws but SUT not!",
			urMngr.undo(), std::logic_error);

	ASSERT_EQUAL(true, urMngr.isModified());
	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}
template<class SUTType>
inline
void UndoRedoManagerTest<SUTType>::IsModifiedtwithExceptionRedo(){
	auto& urMngr(getSUT());

	ASSERT_EQUAL(false, urMngr.isModified());
	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());

	urMngr.doIt(plus);
	urMngr.doIt(plus);
	urMngr.undo();
	ASSERT_EQUAL(true, urMngr.isModified());
	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(true, urMngr.isRedoable());

	urMngr.resetModified();
	ASSERT_EQUAL(false, urMngr.isModified());

	Plus::throwException() = true;

	ASSERT_THROWSM("Command throws but SUT not!",
			urMngr.undo(), std::logic_error);

	ASSERT_EQUAL(false, urMngr.isModified());
	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(true, urMngr.isRedoable());

	ASSERT_THROWSM("Command throws but SUT not!",
				urMngr.redo(), std::logic_error);

	ASSERT_EQUAL(false, urMngr.isModified());
	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(true, urMngr.isRedoable());
}
#endif /* SRC_UNDOREDOMANAGERTEST_H_ */
