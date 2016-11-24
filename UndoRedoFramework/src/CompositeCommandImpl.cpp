/*
 * CompositeCommandImpl.cpp
 *
 *  Created on: 19.02.2015
 *      Author: Gerd
 */

#include <UndoRedoFramework/CompositeCommandImpl.h>
#include <UndoRedoFramework/UndoRedoStack.h>
#include <UndoRedoFramework/CannotRollbackException.h>

#include <iostream>
using namespace std;

namespace UndoRedoFramework{


CompositeCommandImpl::CompositeCommandImpl(std::unique_ptr<UndoRedoStack> && urStack)
: urStack(std::move(urStack)),
  doItExceptionCatched(false),
  undoExceptionCatched(false)
{ }

CompositeCommandImpl::CompositeCommandImpl(UndoRedoStack && urStack)
: CompositeCommandImpl(std::move(urStack).clone()) // Delegate Ctor
{ }

CompositeCommandImpl::CompositeCommandImpl(CompositeCommandImpl && rhs)
: CompositeCommandImpl(std::move(rhs.urStack)) // Delegate Ctor
{  }

std::unique_ptr<Command> CompositeCommandImpl::clone() const&
{
	// ugly hack, but we must implement all virtual Operations
	// CompositeCommandImpls cannot be copied
	throw std::logic_error("Operation not supported");
}
std::unique_ptr<Command> CompositeCommandImpl::clone() &&
{
	return std::unique_ptr<Command>( new CompositeCommandImpl( std::move(*this) ));
}
CompositeCommandImpl::~CompositeCommandImpl() {
	//definition wird wegen unique_ptr<..> urMngr ben�tigt
}

/**
 * f�gt das Command c in den internen CommandManager
 * (UndoRedoHandler.doit(Command c) ein
 *
 * @param c
 */
void CompositeCommandImpl::doIt(Command&& command) {
	doIt(std::move(command).clone());
}
void CompositeCommandImpl::doIt(Command const& command) {
	doIt(command.clone());
}
void CompositeCommandImpl::doIt(SmartPointer&& c) {
	try{
		urStack->doIt( std::move(c) );
	}catch(...){
		doItExceptionCatched = true;
		undo();
		urStack->clear();
		throw;
	}
}
/**
 * f�hrt die Commands wieder aus
 * nach dem sie r�ckg�ngig gemacht wurden
 * @see undo()
 *
 * @throws Exception
 */
void CompositeCommandImpl::doIt() {
	try{
		while (urStack->isRedoable()) {
			urStack->redo();
	}
	}catch(std::exception& e){
		doItExceptionCatched = true;
		if(undoExceptionCatched){
			undoExceptionCatched = false;
			throw CannotRollbackException("undo not possible, cause Command.doIt() throws Exception see getCause()", e);
		}else{
			undo();
			doItExceptionCatched = false;
			throw;
		}
	}
}
/**
 * Commands m�ssen in der umgekehrten Reihenfolge r�ckg�ngig gemacht werden,
 * wie sie ausgef�hrt wurden! Dazu wird ein UndoRedoManager benutzt.
 *
 * @directed true
 * @supplierRole Command Manager
 */
void CompositeCommandImpl::undo() {
	try{
		while (urStack->isUndoable()) {
			urStack->undo();
		}
	}catch(std::exception& e){
		undoExceptionCatched = true;
		if(doItExceptionCatched){
			doItExceptionCatched = false;
			throw CannotRollbackException("doIt not possible, cause Command.undo() throws Exception see getCause()", e);
		}else{
			doIt();
			undoExceptionCatched = false;
			throw; // throws original exception
		}
	}
}

}//end namespace UndoRedoFramework

