#include "BigInteger.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		cout << "Missing Arguments, Need at least one integer" << endl;
		return 0;
	}
	int input = atoi(argv[1]);
	cout << "Original Input: " << input << endl;
	BigInteger bigInt(atoi(argv[1]));
	cout << "BigInt: \tLength\t" << bigInt.Size() << "\tValue\t" << bigInt << endl;
	BigInteger mult(-100);
	BigInteger & other = bigInt * mult;
	cout << "Other:  \tLength\t" << other.Size() << "\tValue\t" << other << endl;
	BigInteger result;
	result = other - bigInt;
	cout << "Result(-): \tLength\t" << result.Size() << "\tValue\t" << result << endl;
	result = other + bigInt;
	cout << "Result(+): \tLength\t" << result.Size() << "\tValue\t" << result << endl;
	result = bigInt - other;
	cout << "Result(-): \tLength\t" << result.Size() << "\tValue\t" << result << endl;
	result = (bigInt - other) / bigInt;
	cout << "Result(-): \tLength\t" << result.Size() << "\tValue\t" << result << endl;
	result = BigInteger::Factorial(100);
	cout << "100!: \tLength\t" << result.Size() << "\tValue\t" << result << endl;
	result = BigInteger::Factorial(50) * BigInteger::Factorial(50);
	cout << "50!*50!: \tLength\t" << result.Size() << "\tValue\t" << result << endl;
	result = BigInteger::Factorial(100) / BigInteger::Factorial(100);
	cout << "100!/100!: \tLength\t" << result.Size() << "\tValue\t" << result << endl;
	result = BigInteger::Factorial(100) / BigInteger::Factorial(50);
	cout << "100!/50!: \tLength\t" << result.Size() << "\tValue\t" << result << endl;

	/*for (int i = 0; i < 100; i++)
	{
		bigInt = bigInt + bigInt;
		cout << "Sum with self("<< i + 2 <<"): " << bigInt << endl;
		cout << "Length: " << bigInt.Size() << endl;
	}*/

}