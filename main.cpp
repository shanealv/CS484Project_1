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
	cout << "BigInt:    \tLength\t" << bigInt.Size() << "\tValue\t" << bigInt << endl;
	BigInteger mult(-125);
	BigInteger & other = bigInt * mult;
	cout << "Other:     \tLength\t" << other.Size() << "\tValue\t" << other << endl;
	BigInteger result;
	BigInteger result2;
	result = other - bigInt;
	cout << "o - i:     \tLength\t" << result.Size() << "\tValue\t" << result << endl;
	result = other + bigInt;
	cout << "o + i:     \tLength\t" << result.Size() << "\tValue\t" << result << endl;
	result = bigInt - other;
	cout << "i - o:     \tLength\t" << result.Size() << "\tValue\t" << result << endl;
	result = (bigInt - other) / bigInt;
	cout << "(i - o)/i: \tLength\t" << result.Size() << "\tValue\t" << result << endl;
	result = BigInteger::Factorial(30);
	cout << "30!:      \tLength\t" << result.Size() << "\tValue\t" << result << endl;
	result = result + result;
	cout << "30!+30!:   \tLength\t" << result.Size() << "\tValue\t" << result << endl;
	result = BigInteger::Factorial(50);
	result = result * result;
	cout << "50!*50!:   \tLength\t" << result.Size() << "\tValue\t" << result << endl;
	result = BigInteger::Factorial(100) / (BigInteger::Factorial(50) * BigInteger::Factorial(50));
	cout << "100!/50!50!:  \tLength\t" << result.Size() << "\tValue\t" << result << endl;
	result = BigInteger::Factorial(100) / BigInteger::Factorial(100);
	cout << "100!/100!: \tLength\t" << result.Size() << "\tValue\t" << result << endl;
	result2 = BigInteger::Ten / BigInteger::Ten;
	cout << "10/10:     \tLength\t" << result2.Size() << "\tValue\t" << result2 << endl;

	result2 = BigInteger::BinomialCoefficient(35, 10);
	cout << "10_C_10:   \tLength\t" << result2.Size() << "\tValue\t" << result2 << endl;

	/*for (int i = 0; i < 100; i++)
	{
		bigInt = bigInt + bigInt;
		cout << "Sum with self("<< i + 2 <<"): " << bigInt << endl;
		cout << "Length: " << bigInt.Size() << endl;
	}*/

}