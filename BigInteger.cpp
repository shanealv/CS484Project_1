#include <iostream>
#include <iomanip>
#include "BigInteger.h"

using namespace std;

BigInteger::BigInteger()
{
	length = 1;
	negative = false;
	head = new BigIntegerNode;
	tail = head;
}

BigInteger::BigInteger(int initialValue)
{
	length = 1;
	negative = (initialValue < 0);
	head = new BigIntegerNode;
	if (negative)
	{
		initialValue = -initialValue;
	}

	if (initialValue < LIMIT)
	{
		head->value = initialValue;
		tail = head;
	}
	else
	{
		tail = new BigIntegerNode;
		head->value = initialValue % LIMIT;
		tail->value = initialValue / LIMIT;
		head->next = tail;
		tail->prev = head;
		length++;
	}
}

int BigInteger::Size()
{
	return length;
}

ostream& operator<<(ostream& stream, const BigInteger& bigInteger)
{
	ostream& current = stream;
	if (bigInteger.negative)
	{
		current << '-';
	}
	ios state(NULL);
	state.copyfmt(cout);
	for (BigIntegerNode * node = bigInteger.tail; node != NULL; node = node->prev)
	{
		if (node != bigInteger.tail)
			current << setw(9) << setfill('0') << node->value;
		else
			current << node->value;
	}
	state.copyfmt(state);
	return current;
}


BigInteger* operator+(const BigInteger& left, const BigInteger& right)
{
	BigInteger * out = new BigInteger();
	BigIntegerNode * outNode = out->head;
	BigIntegerNode * leftCurser = left.head;
	BigIntegerNode * rightCurser = right.head;
	int carry = 0;
	while (true)
	{
		int lvalue = 0;
		int rvalue = 0;

		if (leftCurser != NULL)
		{
			lvalue = leftCurser->value;
			leftCurser = leftCurser->next;
		}

		if (rightCurser != NULL)
		{
			rvalue = rightCurser->value;
			rightCurser = rightCurser->next;
		}

		int sum = lvalue + rvalue + carry;
		outNode->value = sum % LIMIT;
		carry = sum / LIMIT;

		if (leftCurser != NULL || rightCurser != NULL || carry != 0)
		{
			BigIntegerNode * newNode = new BigIntegerNode();
			newNode->prev = outNode;
			outNode->next = newNode;
			outNode = newNode;
			out->length++;
		}
		else
			break;
	}
	out->tail = outNode;
	return out;
}

BigInteger* operator-(const BigInteger& left, const BigInteger& right)
{
	BigInteger * out = new BigInteger();
	BigIntegerNode * outNode = out->head;
	BigIntegerNode * leftCurser = left.head;
	BigIntegerNode * rightCurser = right.head;
	int carry = 0;
	while (true)
	{
		int lvalue = 0;
		int rvalue = 0;

		if (leftCurser != NULL)
		{
			lvalue = leftCurser->value;
			leftCurser = leftCurser->next;
		}

		if (rightCurser != NULL)
		{
			rvalue = rightCurser->value;
			rightCurser = rightCurser->next;
		}

		int sum = lvalue + rvalue + carry;
		outNode->value = sum % LIMIT;
		carry = sum / LIMIT;

		if (leftCurser != NULL || rightCurser != NULL || carry != 0)
		{
			BigIntegerNode * newNode = new BigIntegerNode();
			newNode->prev = outNode;
			outNode->next = newNode;
			outNode = newNode;
			out->length++;
		}
		else
			break;
	}
	out->tail = outNode;
	return out;
}



