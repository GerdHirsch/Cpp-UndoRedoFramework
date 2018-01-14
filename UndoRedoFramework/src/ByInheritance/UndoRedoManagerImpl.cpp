#include <UndoRedoFramework/ByInheritance/UndoRedoManagerImpl.h>
#include <UndoRedoFramework/Command.h>
#include <UndoRedoFramework/IllegalArgumentException.h>

#include <stack>
#include <memory>
#include <iostream>
using namespace std;

namespace UndoRedoFramework{
namespace ByInheritance{

UndoRedoManagerImpl::UndoRedoManagerImpl(UndoRedoManagerImpl && rhs)
	: UndoRedoStackImpl(std::move(rhs)),
	modifications( rhs.modifications)
{
	rhs.modifications = 0;
//	cout << "UndoRedoManagerImpl(UndoRedoManagerImpl&& rhs)" << endl;
}

UndoRedoManagerImpl::UndoRedoManagerImpl() : modifications(0)
{
//	cout << "UndoRedoManagerImpl()" << endl;
}

void UndoRedoManagerImpl::undo()
{
	UndoRedoStackImpl::undo();
	modifications--;
}

void UndoRedoManagerImpl::doIt(SmartPointer && command)
{
	UndoRedoStackImpl::doIt(std::move(command));

	if(modifications >= 0) // else do not change it
		modifications++;
}

void UndoRedoManagerImpl::redo()
{
	UndoRedoStackImpl::redo();
	modifications++;
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
