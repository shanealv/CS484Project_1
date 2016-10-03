#ifndef BigInteger_H
#define BigInteger_H
#define LIMIT 1000000000 // 1,000,000,000
#include <iostream>

using namespace std;

struct BigIntegerNode
{
	unsigned int value = 0;	// must be between 0 and 999,999,999
	BigIntegerNode * next = NULL;
	BigIntegerNode * prev = NULL;
};

class BigInteger
{
private:
	int length;
	bool negative;
	BigIntegerNode * head; // represents the least significant digits
	BigIntegerNode * tail; // represents the most significant digits
	friend ostream& operator<<(ostream& stream, const BigInteger& bigInteger);

public:
	BigInteger();
	BigInteger(int initialValue);
	BigInteger& operator=(const BigInteger &rhs);
	BigInteger& operator+(BigInteger& other);
	BigInteger& operator-(BigInteger& other);
	BigInteger& operator*(BigInteger& other);
	BigInteger& operator/(BigInteger& other);
	bool operator<(const BigInteger& other);
	bool operator>(const BigInteger& other);
	bool operator<=(const BigInteger& other);
	bool operator>=(const BigInteger& other);
	int Size();

	static BigInteger Zero;
	static BigInteger One;
	static BigInteger Two;
	static BigInteger& Factorial(int i);
	static double BinomialCoefficient(int n, int k);
	static void Half(BigInteger & num);
};

ostream& operator<<(ostream& stream, const BigInteger& bigInteger);
#endif
