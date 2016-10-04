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
	static const BigInteger & DivideStep(const BigInteger & lhs, const BigInteger & rhs);
	friend const BigInteger& operator+(const BigInteger& lhs, const BigInteger& rhs);
	friend const BigInteger& operator-(const BigInteger& lhs, const BigInteger& rhs);
	friend const BigInteger& operator*(const BigInteger& lhs, const BigInteger& rhs);
	friend const BigInteger& operator/(const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator<(const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator>(const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator<=(const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator>=(const BigInteger& lhs, const BigInteger& rhs);

public:
	~BigInteger();
	BigInteger();
	BigInteger(int initialValue);
	BigInteger(const BigInteger& copyValue);
	BigInteger& operator=(const BigInteger& other);
	int Size();

	const static BigInteger Zero;
	const static BigInteger One;
	const static BigInteger Two;
	const static BigInteger Ten;
	static const BigInteger& Factorial(int i);
	static BigInteger& Half(const BigInteger & num);
	static double BinomialCoefficient(int n, int k);
	static const BigInteger & Multiply(const BigInteger & lhs, const BigInteger & rhs);
};

ostream& operator<<(ostream& stream, const BigInteger& bigInteger);
#endif
