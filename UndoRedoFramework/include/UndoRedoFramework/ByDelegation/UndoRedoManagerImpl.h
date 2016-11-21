#ifndef UNDOREDOMANAGERIMPLBYDELEGATION_H
#define UNDOREDOMANAGERIMPLBYDELEGATION_H

#include <UndoRedoFramework/ByDelegation/UndoRedoStackImpl.h>
#include <UndoRedoFramework/ByDelegation/UndoRedoManager.h>
#include <UndoRedoFramework/Command.h>

#include <stack>
#include <memory>

namespace UndoRedoFramework{
namespace ByDelegation{

class UndoRedoManagerImpl :  public UndoRedoManager
{

public:
	UndoRedoManagerImpl(UndoRedoStack && urStack);
	UndoRedoManagerImpl();
	UndoRedoManagerImpl(UndoRedoManagerImpl && rhs);

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
	
	virtual bool isModified() const override;
	virtual void resetModified() override;
	virtual std::size_t undoStackSize() const override;
	virtual void clear() override;
	virtual std::unique_ptr<UndoRedoStack> clone() && override;
private:
	std::unique_ptr<UndoRedoStack> urStack;
	int modifications;
};
}} // end namespace
#endif //UNDOREDOMANAGERIMPLBYDELEGATION_H
