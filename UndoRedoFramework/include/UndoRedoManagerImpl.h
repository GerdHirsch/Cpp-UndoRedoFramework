#ifndef UNDOREDOMANAGERIMPL_H
#define UNDOREDOMANAGERIMPL_H

#include <stack>
#include <memory>
//#include <boost/shared_ptr.hpp>

#include "undoredomanager.h"
#include "Command.h"


class UndoRedoManagerImpl : public UndoRedoManager
{

public:
//	using SmartPointer = std::unique_ptr<Command>;

	UndoRedoManagerImpl();
//	UndoRedoManagerImpl(UndoRedoManagerImpl const& rhs);
	UndoRedoManagerImpl(UndoRedoManagerImpl && rhs);


	virtual void doIt(Command && command) override;
	virtual void doIt(Command const& command) override;
	virtual void doIt(SmartPointer && cmd) override;

	virtual bool canUndo() const override;
	virtual void undo() override;

	virtual bool canRedo() const override;
	virtual void redo() override;
	
	virtual bool isModified() const override;
	virtual void resetModified() override;
	virtual std::unique_ptr<UndoRedoManager> clone() && override;

private:
	void clearRedoStack();

	std::stack<SmartPointer> undoStack;
	std::stack<SmartPointer> redoStack;
	int modifications;
};

#endif //UNDOREDOMANAGERIMPL_H
