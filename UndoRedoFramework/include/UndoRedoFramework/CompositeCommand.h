/*
 * CompositeCommand.h
 *
 *  Created on: 19.02.2015
 *      Author: Gerd
 */

#ifndef COMPOSITECOMMAND_H_
#define COMPOSITECOMMAND_H_

#include "Command.h"

#include<memory>

namespace UndoRedoFramework{

class CompositeCommand: public Command {
public:
//	using SmartPointer = Command::SmartPointer;

	virtual ~CompositeCommand();

	virtual void doIt(Command&& c) = 0;
	virtual void doIt(Command const& c) = 0;
	virtual void doIt(SmartPointer && cmd) = 0;
};
inline
CompositeCommand::~CompositeCommand(){}

}

#endif /* COMPOSITECOMMAND_H_ */
