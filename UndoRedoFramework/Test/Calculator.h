#ifndef SIMPLE_CALCULATOR_H
#define SIMPLE_CALCULATOR_H


#include <iostream>
class Calculator
{
public:
	Calculator() : result(0){};
	~Calculator(){};

	void plus(int summand){
<<<<<<< HEAD
//		std::cout << "Calculator.plus: " << summand << std::endl;
=======
		std::cout << "Calculator.plus: " << summand << std::endl;
>>>>>>> branch 'add-tests' of https://github.com/GerdHirsch/Cpp-UndoRedoFramework.git
		result += summand;
	}
	void minus(int subtrahent){
<<<<<<< HEAD
//		std::cout << "Calculator.minus: " << subtrahent << std::endl;
=======
		std::cout << "Calculator.minus: " << subtrahent << std::endl;
>>>>>>> branch 'add-tests' of https://github.com/GerdHirsch/Cpp-UndoRedoFramework.git
		result -= subtrahent;
	}
	int getResult(){ return result; }
	void clear() { result = 0; }
private:
	int result;
};



#endif //SIMPLE_CALCULATOR_H

