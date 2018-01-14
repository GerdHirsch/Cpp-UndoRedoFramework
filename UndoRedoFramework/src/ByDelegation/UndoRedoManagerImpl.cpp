#include <UndoRedoFramework/ByDelegation/UndoRedoManagerImpl.h>
#include <UndoRedoFramework/Command.h>
#include <UndoRedoFramework/IllegalArgumentException.h>

#include <stack>
#include <memory>
#include <iostream>
using namespace std;

namespace UndoRedoFramework{
namespace ByDelegation{

UndoRedoManagerImpl::UndoRedoManagerImpl(UndoRedoManagerImpl && rhs)
	:
	urStack(std::move(rhs).urStack),
	modifications( rhs.modifications)
{
	rhs.modifications = 0;
//	cout << "UndoRedoManagerImpl(UndoRedoManagerImpl&& rhs)" << endl;

}

UndoRedoManagerImpl::UndoRedoManagerImpl()
:
	urStack(new UndoRedoStackImpl),
	modifications(0)
{
//	cout << "UndoRedoManagerImpl()" << endl;
}

std::unique_ptr<UndoRedoStack> UndoRedoManagerImpl::clone()&&{
	return std::unique_ptr<UndoRedoStack>(
			new UndoRedoManagerImpl(std::move(*this)));
}

void UndoRedoManagerImpl::undo()
{
	urStack->undo();
	modifications--;
}

void UndoRedoManagerImpl::doIt(Command && command){
	doIt(std::move(command).clone());
}

void UndoRedoManagerImpl::doIt(Command const & command){
	doIt(command.clone());
}

void UndoRedoManagerImpl::clear(){
	return urStack->clear();
}
void UndoRedoManagerImpl::doIt(SmartPointer && command)
{
	urStack->doIt(std::move(command));

	if(modifications >= 0) // else do not change it
		modifications++;
}

void UndoRedoManagerImpl::redo()
{
	urStack->redo();
	modifications++;
}

bool UndoRedoManagerImpl::isUndoable() const {
	return urStack->isUndoable();
}
bool UndoRedoManagerImpl::isRedoable() const {
	return urStack->isRedoable();
}

std::size_t UndoRedoManagerImpl::undoStackSize() const {
	return urStack->undoStackSize();
}
std::size_t UndoRedoManagerImpl::redoStackSize() const {
	return urStack->redoStackSize();
}

bool UndoRedoManagerImpl::isModified() const
{
	return modifications != 0;
}
void UndoRedoManagerImpl::resetModified()
{
	modifications = 0;
}

}} // end namespace
