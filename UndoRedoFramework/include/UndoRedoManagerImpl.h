#ifndef UNDOREDOMANAGERIMPL_H
#define UNDOREDOMANAGERIMPL_H

#include "undoredomanager.h"
#include "UndoRedoStackImpl.h"
#include "Command.h"

#include <stack>
#include <memory>

namespace UndoRedoFramework{
namespace ByInheritance{

class UndoRedoManagerImpl : public UndoRedoStackImpl, public UndoRedoManager
{

public:

	UndoRedoManagerImpl();
	UndoRedoManagerImpl(UndoRedoManagerImpl && rhs);

	//for non copyable commands
	//for copyable commands
	//for SmartPointers
//	virtual void doIt(Command && command) override;
//	virtual void doIt(Command const& command) override;
	virtual void doIt(SmartPointer && command) override;

//	virtual bool isUndoable() const override;
	virtual void undo() override;

//	virtual bool isRedoable() const override;
	virtual void redo() override;
	
	virtual bool isModified() const override;
	virtual void resetModified() override;
//	virtual std::unique_ptr<UndoRedoManager> clone() && override;

//	virtual void clear() override;
private:
	int modifications;
};

}} // end namespace
#endif //UNDOREDOMANAGERIMPL_H
