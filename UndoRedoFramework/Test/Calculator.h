#ifndef SIMPLE_CALCULATOR_H
#define SIMPLE_CALCULATOR_H


#include <iostream>
class Calculator
{
public:
	Calculator() : result(0){};
	~Calculator(){};

	void plus(double summand){
		std::cout << "Calculator.plus: " << summand << std::endl;
		result += summand;
	}
	void minus(double subtrahent){
		std::cout << "Calculator.minus: " << subtrahent << std::endl;
		result -= subtrahent;
	}
	double getResult(){ return result; }
	void clear() { result = 0; }
private:
	double result;
};



#endif //SIMPLE_CALCULATOR_H

