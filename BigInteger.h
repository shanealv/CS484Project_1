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
	friend BigInteger* operator+(const BigInteger& left, const BigInteger& right);
	friend BigInteger* operator-(const BigInteger& left, const BigInteger& right);
	friend BigInteger* operator<(const BigInteger& left, const BigInteger& right);
	friend BigInteger* operator>(const BigInteger& left, const BigInteger& right);

public:
	BigInteger();
	BigInteger(int initialValue);
	int Size();
};

ostream& operator<<(ostream& stream, const BigInteger& bigInteger);
#endif
