/*
 * CompositeCommandImpl.h
 *
 *  Created on: 07.11.2016
 *      Author: Gerd
 */

#ifndef COMPOSITECOMMANDIMPL_H_
#define COMPOSITECOMMANDIMPL_H_

#include "CompositeCommand.h"

class CompositeCommandImpl : public CompositeCommand{
public:
	CompositeCommandImpl(UndoRedoStack && urStack);
	CompositeCommandImpl(CompositeCommandImpl && rhs);
	virtual ~CompositeCommandImpl();

	void doIt(Command&& c);
	void doIt(Command const& c);
	void doIt(SmartPointer && cmd);
	void doIt() override;
	void undo() override;

	virtual SmartPointer clone() && override;
	virtual SmartPointer clone() const& override;

private:
	std::unique_ptr<UndoRedoStack> urStack;
	bool doItExceptionCatched;
	bool undoExceptionCatched;
};




#endif /* COMPOSITECOMMANDIMPL_H_ */
