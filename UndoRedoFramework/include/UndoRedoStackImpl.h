/*
 * UndoRedoStackImpl.h
 *
 *  Created on: 07.11.2016
 *      Author: Gerd
 */

#ifndef UNDOREDOSTACKIMPL_H_
#define UNDOREDOSTACKIMPL_H_

#include "UndoRedoStack.h"

#include <stack>

class UndoRedoStackImpl : public virtual UndoRedoStack{
public:
//	using SmartPointer = std::unique_ptr<Command>;

	UndoRedoStackImpl();
//	UndoRedoManagerImpl(UndoRedoManagerImpl const& rhs);
	UndoRedoStackImpl(UndoRedoStackImpl && rhs);

	//for non copyable commands
	//for copyable commands
	//for SmartPointers

	virtual void doIt(Command && command) override;
	virtual void doIt(Command const& command) override;
	virtual void doIt(SmartPointer && command) override;

	virtual bool isUndoable() const override;
	virtual void undo() override;

	virtual bool isRedoable() const override;
	virtual void redo() override;

	virtual std::unique_ptr<UndoRedoStack> clone() && override;

	virtual void clear() override;
	virtual std::size_t undoStackSize() const{
		return undoStack.size();
	}
private:
	void clearRedoStack();
	void clearUndoStack();

	std::stack<SmartPointer> undoStack;
	std::stack<SmartPointer> redoStack;
};

#endif /* UNDOREDOSTACKIMPL_H_ */
