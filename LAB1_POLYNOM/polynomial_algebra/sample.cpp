#include <iostream>
#include "../polynomial_algebra/expression.h"


using namespace std;

int main()
{
	string a = "result = var_1 + var_2 * 2";
	string postfix = InfixToPostfixConverter::Convert(a);
	cout << PostfixCalculator::Calculate(postfix) << '\n';
}

