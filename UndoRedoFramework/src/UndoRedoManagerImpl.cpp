#include <stack>
#include <memory>
//#include <boost/shared_ptr.hpp>

#include "../include/UndoRedoManagerImpl.h"
#include "../include/Command.h"

#include <iostream>
//using namespace boost;
using namespace std;


//UndoRedoManagerImpl::UndoRedoManagerImpl(UndoRedoManagerImpl const& rhs)
//:
//	undoStack(rhs.undoStack),
//	redoStack(rhs.redoStack),
//	modifications(rhs.modifications)
//{
//	cout << "UndoRedoManagerImpl(UndoRedoManagerImpl const&)" << endl;
//}
UndoRedoManagerImpl::UndoRedoManagerImpl(UndoRedoManagerImpl && rhs)
	:
	undoStack( std::move(rhs.undoStack) ),
	redoStack( std::move(rhs.redoStack) ),
	modifications( rhs.modifications)
{
	cout << "UndoRedoManagerImpl(UndoRedoManagerImpl &&)" << endl;
	// TODO: was sollte rhs.isModified() nach move zurückliefern?
	rhs.modifications = 0;
}


UndoRedoManagerImpl::UndoRedoManagerImpl() : modifications(0)
{
}
//unique_ptr<UndoRedoManager> UndoRedoManagerImpl::clone() const &
//{
//	cout << "UndoRedoManagerImpl::clone() const &"<< endl;
//	return unique_ptr<UndoRedoManager>(new UndoRedoManagerImpl(*this));
//}
unique_ptr<UndoRedoManager> UndoRedoManagerImpl::clone() &&
{
	cout << "UndoRedoManagerImpl::clone() &&"<< endl;
	return unique_ptr<UndoRedoManager>(new UndoRedoManagerImpl( std::move(*this) ));
}

void UndoRedoManagerImpl::doIt(Command && command)
{
	doIt(std::move(command).clone());
//
//	if(modifications < 0)
//		modifications = undoStack.size() + 1;
//	modifications++;
//
//	undoStack.push( std::move(command).clone());
//	clearRedoStack();
//
//	undoStack.top()->doIt();
}
void UndoRedoManagerImpl::doIt(Command const& command)
{
	doIt(command.clone());
//
//	if(modifications < 0)
//		modifications = undoStack.size() + 1;
//	modifications++;
//
//	undoStack.push( command.clone());
//	clearRedoStack();
//
//	undoStack.top()->doIt();
}
void UndoRedoManagerImpl::doIt(SmartPointer && command)
{
	if(modifications < 0)
		modifications = undoStack.size() + 1;
	modifications++;

	undoStack.push( std::move(command) );
	clearRedoStack();

	undoStack.top()->doIt();
}
void UndoRedoManagerImpl::clearRedoStack(){
	while(!redoStack.empty())
		redoStack.pop();
}
bool UndoRedoManagerImpl::canUndo() const
{
	return !undoStack.empty();
}
void UndoRedoManagerImpl::undo()
{
/* ohne move nur mit shared_ptr möglich
	undoStack.top()->undo();
	modifications--;
	redoStack.push(undoStack.top());
	undoStack.pop();
*/
	undoStack.top()->undo();
	modifications--;
	redoStack.push(std::move(undoStack.top()));
	undoStack.pop();
}

bool UndoRedoManagerImpl::canRedo() const
{
	return !redoStack.empty();
}
void UndoRedoManagerImpl::redo()
{
/* ohne move nur mit shared_ptr möglich
	redoStack.top()->doIt();
	modifications++;
	undoStack.push(redoStack.top());
	redoStack.pop();
*/
	redoStack.top()->doIt();
	modifications++;
	undoStack.push(std::move(redoStack.top()));
	redoStack.pop();

}

bool UndoRedoManagerImpl::isModified() const
{
	return modifications != 0;
}
void UndoRedoManagerImpl::resetModified()
{
	modifications = 0;
}

