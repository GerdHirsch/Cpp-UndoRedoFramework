#ifndef SIMPLE_CALCULATOR_H
#define SIMPLE_CALCULATOR_H


#include <iostream>
class Calculator
{
public:
	Calculator() : result(0){};
	~Calculator(){};

	void plus(int summand){
		std::cout << "Calculator.plus: " << summand << std::endl;
		result += summand;
	}
	void minus(int subtrahent){
		std::cout << "Calculator.minus: " << subtrahent << std::endl;
		result -= subtrahent;
	}
	int getResult(){ return result; }
	void clear() { result = 0; }
private:
	int result;
};



#endif //SIMPLE_CALCULATOR_H

