#include "BigInteger.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		cout << "Missing Arguments, Need at least one number" << endl;
		return 0;
	}
	int input = atoi(argv[1]);
	cout << "Original Input: " << input << endl;
	BigInteger * bigInt = new BigInteger(atoi(argv[1]));
	cout << "BigInteger Version: " << *bigInt << endl;
	cout << "Length: " << bigInt->Size() << endl;
	for (int i = 0; i < 100; i++)
	{
		bigInt = *bigInt + *bigInt;
		cout << "Sum with self("<< i + 2 <<"): " << *bigInt << endl;
		cout << "Length: " << bigInt->Size() << endl;
	}

}