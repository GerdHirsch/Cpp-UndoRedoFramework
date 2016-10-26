#ifndef COMMAND_H
#define COMMAND_H
#include <memory>

class Command
{
public:
//	using SmartPointer = std::unique_ptr<Command>;
	typedef std::unique_ptr<Command> SmartPointer;
//	using SmartPointer = std::shared_ptr<Command>;
//	using SmartPointer = boost::shared_ptr<Command>;

	virtual ~Command(){}

	virtual void doIt() = 0;
	virtual void undo() = 0;

	virtual SmartPointer clone() && = 0;
	virtual SmartPointer clone() const & = 0;
};

#endif //COMMAND_H
