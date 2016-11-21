#ifndef CALCULATOR_COMMANDS
#define CALCULATOR_COMMANDS

#include "Calculator.h"

#include <include/Command.h>

#include <iostream>
#include <stdexcept>


class Plus : public UndoRedoFramework::Command
{
public:
	using Command = UndoRedoFramework::Command;
	using Command::SmartPointer;

	Plus(Calculator& calculator, int summand) :
		calculator(calculator), summand(summand){
		throwException() = false;
		throwAtTimes() = 0;
	}

//	Plus(const Plus& source) :
//		calculator(source.calculator), summand(source.summand) {}

	virtual void doIt() override
	{
		if(throwException()) {
			if(throwAtTimes() <= 0)
				throw std::logic_error("Plus.doIt() throws");
			else
				--throwAtTimes();
		}

//		std::cout << "Plus.doIt()" << std::endl;
		calculator.plus(summand);
	}
	virtual void undo() override
	{
		if(throwException()) {
			if(throwAtTimes() <= 0)
				throw std::logic_error("Plus.doIt() throws");
			else
				--throwAtTimes();
		}
		calculator.minus(summand);
	}

	virtual SmartPointer clone() const & override
	{
		using namespace std;
		return SmartPointer( new Plus(*this));
	}

	virtual SmartPointer clone() && override
	{
		using namespace std;
//		cout << "PlusCommand::clone() &&" << endl;
		return SmartPointer ( new Plus( std::move(*this) ));
	}
	static bool& throwException(){
		static bool b = false;
		return b;
	}
	static int& throwAtTimes(){
		static int times = 0;
		return times;
	}
private:
	Calculator& calculator;
	int summand;
};

class Minus : public UndoRedoFramework::Command
{
public:
	using UndoRedoFramework::Command::SmartPointer;


	Minus(Calculator& calculator, int subtrahent):calculator(calculator), subtrahent(subtrahent){}
	virtual void doIt() override
	{
		calculator.minus(subtrahent);
	}
	virtual void undo() override
	{
		calculator.plus(subtrahent);
	}

	virtual SmartPointer clone() const& override
	{
		using namespace std;
//		cout << "MinusCommand::clone() const&" << endl;
		return SmartPointer ( new Minus( std::move(*this) ));
	}
	virtual SmartPointer clone() && override
	{
		using namespace std;
//		cout << "MinusCommand::clone() &&" << endl;
		return SmartPointer ( new Minus( std::move(*this) ));
	}
private:
	Calculator& calculator;
	int subtrahent;
};

#endif //CALCULATOR_COMMANDS
