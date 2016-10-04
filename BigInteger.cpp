#include <iostream>
#include <iomanip>
#include "BigInteger.h"

using namespace std;

const BigInteger BigInteger::Zero(0);
const BigInteger BigInteger::One(1);
const BigInteger BigInteger::Two(2);
const BigInteger BigInteger::Ten(10);

BigInteger::~BigInteger()
{
	BigIntegerNode * curser = tail;
	while (curser != head)
	{
		curser = curser->prev;
		delete curser->next;
	}
	delete curser;
}

BigInteger::BigInteger()
{
	length = 1;
	negative = false;
	head = tail = new BigIntegerNode;
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

BigInteger::BigInteger(const BigInteger & other)
{
	length = 1;
	negative = false;
	head = tail = new BigIntegerNode;
	*this = other;
}

int BigInteger::Size()
{
	return length;
}

ostream& operator<<(ostream& stream, const BigInteger& bigInteger)
{
	ostream& out = stream;
	if (bigInteger.negative)
	{
		out << '-';
	}
	ios state(NULL);
	state.copyfmt(cout);
	for (BigIntegerNode * node = bigInteger.tail; node != NULL; node = node->prev)
	{
		if (node != bigInteger.tail)
			out << setw(9) << setfill('0') << node->value;
		else
			out << node->value;
	}
	state.copyfmt(state);
	return out;
}

BigInteger& BigInteger::operator=(const BigInteger &rhs)
{
	if (this != &rhs)
	{
		// if data is of different sizes
		int sizediff = this->length - rhs.length;
		if (sizediff < 0) // rhs is larger
		{
			// increase size
			BigIntegerNode * curser = this->tail;
			while (sizediff < 0)
			{
				// add a node
				BigIntegerNode * newNode = new BigIntegerNode();
				newNode->prev = curser;
				curser->next = newNode;
				curser = curser->next;
				this->length++;
				sizediff++;
			}
			this->tail = curser;
		}
		else if (sizediff > 0) // lhs is larger
		{
			// increase size
			BigIntegerNode * curser = this->tail;
			while (sizediff > 0)
			{
				// delete a node
				curser = curser->prev;
				delete curser->next;
				curser->next = NULL;
				this->length--;
				sizediff--;
			}
			this->tail = curser;
		}

		// copy data
		BigIntegerNode * lhsCurser = this->head;
		BigIntegerNode * rhsCurser = rhs.head;
		do
		{
			lhsCurser->value = rhsCurser->value;
			lhsCurser = lhsCurser->next;
			rhsCurser = rhsCurser->next;
		} while (lhsCurser != NULL && rhsCurser != NULL);
		this->negative = rhs.negative;
	}
	return *this;
}


const BigInteger& operator+(const BigInteger& lhs, const BigInteger& rhs)
{
	// copy both operands and force positive
	BigInteger a(lhs);
	BigInteger b(rhs);
	a.negative = false;
	b.negative = false;

	if (lhs.negative && !rhs.negative)
		return b - a; // -a + b = b - a
	if (!lhs.negative && rhs.negative)
		return a - b; // a + -b = a - b

	BigInteger * result = new BigInteger(a);
	result->negative = (lhs.negative && rhs.negative);
	BigIntegerNode * rCurser = result->head;
	BigIntegerNode * bCurser = b.head;

	int carry = 0;
	while (true)
	{
		int bValue = 0;
		if (bCurser != NULL)
		{
			bValue = bCurser->value;
			bCurser = bCurser->next;
		}
		int sum = rCurser->value + bValue + carry;
		rCurser->value = sum % LIMIT;
		carry = sum / LIMIT;

		if (bCurser == NULL && carry == 0)
			break;

		if (rCurser->next == NULL)
		{
			rCurser->next = new BigIntegerNode();
			rCurser->next->prev = rCurser;
			result->tail = rCurser->next;
			result->length++;
		}
		rCurser = rCurser->next;
	}
	return *result;
}

int Borrow(BigIntegerNode * node) // helper method for operator-
{
	if (node->value > 0)
	{
		node->value--;
		return LIMIT;
	}

	return Borrow(node->next);
}

const BigInteger& operator-(const BigInteger& lhs, const BigInteger& rhs)
{
	// copy both operands and force positive
	BigInteger a(lhs);
	BigInteger b(rhs);
	a.negative = false;
	b.negative = false;

	if (lhs.negative && rhs.negative)
		return b - a; // -a - -b = b - a
	else if (rhs.negative)
		return a + b; // a - -b = a + b
	else if (lhs.negative) 
	{
		BigInteger * result = new BigInteger(a + b); // -a - b = -(a + b)
		result->negative = true;
		return *result;
	}
	else if (lhs < rhs)
	{
		BigInteger * result = new BigInteger(b - a); // a - b = -(b - a)
		result->negative = true;
		return *result;
	}

	BigInteger * result = new BigInteger(a);
	BigIntegerNode * rCurser = result->tail;
	BigIntegerNode * bCurser = b.tail;

	int sizeDiff = result->length - b.length;
	while (sizeDiff > 0) // align the cursers
	{
		rCurser = rCurser->prev;
		sizeDiff--;
	}

	while (rCurser != NULL)
	{
		int diff = rCurser->value - bCurser->value;
		if (diff < 0) // initiate borrow routine
		{
			diff += Borrow(rCurser->next);
		}

		rCurser->value = diff;
		rCurser = rCurser->prev;
		bCurser = bCurser->prev;
	}

	// trim empty tail nodes
	rCurser = result->tail;
	while (rCurser->value <= 0 && rCurser != result->head)
	{
		rCurser = rCurser->prev;
		delete rCurser->next;
		rCurser->next = NULL;
		result->tail = rCurser;
		result->length--;
	}

	return *result;
}

const BigInteger & BigInteger::Multiply(const BigInteger & a, const BigInteger & b)
{
	if (b <= BigInteger::One)
		return a;

	if (b.head->value % 2 != 0) // if rhs is odd
		return Multiply(a, b - BigInteger::One) + a;
	else // rhs is even
		return Multiply(a + a, Half(b));
}

const BigInteger & operator*(const BigInteger& lhs, const BigInteger& rhs)
{
	// use the smaller number to multiply the large one
	if (lhs < rhs)
		return rhs * lhs;

	BigInteger a(lhs);
	BigInteger b(rhs);
	a.negative = false;
	b.negative = false;
	BigInteger * result = new BigInteger(BigInteger::Multiply(a, b));

	// if both values are positive or both are negative, then result is positive
	if ((lhs.negative && rhs.negative) || (!lhs.negative && !rhs.negative))
		result->negative = false;
	else
		result->negative = true;

	return *result;
}


// finds the largest number of the form X = a * 10^n which is a digit from lhs / rhs
const BigInteger & BigInteger::DivideStep(const BigInteger & lhs, const BigInteger & rhs)
{
	if (lhs < rhs)
		return BigInteger::Zero;

	BigInteger * mult = new BigInteger(BigInteger::One);
	BigInteger * mult2 = new BigInteger(BigInteger::One);
	// scale by factors of 10
	while (true)
	{
		BigInteger temp(*mult * BigInteger::Ten);
		if (lhs < temp * rhs)
			break;
		*mult = BigInteger::Ten * *mult;
	}
	// fine tune number
	while (true)
	{
		BigInteger temp(*mult * (*mult2 + BigInteger::One));
		if (lhs < temp * rhs)
			break;
		*mult2 = BigInteger::One + *mult2;
	}
	return *mult * *mult2;
}

const BigInteger & operator/(const BigInteger & lhs, const BigInteger & rhs)
{
	BigInteger a(lhs);
	BigInteger b(rhs);
	BigInteger * counter = new BigInteger(BigInteger::Zero);
	a.negative = false;
	b.negative = false;
	// find the max number we can multiply 

	while (a >= b && !a.negative)
	{
		BigInteger mult (BigInteger::DivideStep(a, b));
		if (mult < BigInteger::One)
			break;
		*counter = mult + *counter;
		a = a - (b * mult);
	}

	// if both values are positive or both are negative, then result is positive
	if ((lhs.negative && rhs.negative) || (!lhs.negative && !rhs.negative))
		counter->negative = false;
	else
		counter->negative = true;

	return *counter;
}

bool operator>(const BigInteger & lhs, const BigInteger & rhs)
{
	if (lhs.length > rhs.length)
		return true;
	if (rhs.length > lhs.length)
		return false;

	// numbers are of same length
	BigIntegerNode * lhsCurser = lhs.tail;
	BigIntegerNode * rhsCurser = rhs.tail;

	while (lhsCurser != NULL)
	{
		if (lhsCurser->value > rhsCurser->value)
			return true;
		if (lhsCurser->value < rhsCurser->value)
			return false;

		// values are equal so far
		lhsCurser = lhsCurser->prev;
		rhsCurser = rhsCurser->prev;
	}
	return false;
}

bool operator<(const BigInteger & lhs, const BigInteger & rhs)
{
	if (lhs.length < rhs.length)
		return true;
	if (rhs.length < lhs.length)
		return false;

	// numbers are of same length
	BigIntegerNode * lhsCurser = lhs.tail;
	BigIntegerNode * rhsCurser = rhs.tail;

	while (lhsCurser != NULL)
	{
		if (lhsCurser->value < rhsCurser->value)
			return true;
		if (rhsCurser->value < lhsCurser->value)
			return false;

		// values are equal so far
		lhsCurser = lhsCurser->prev;
		rhsCurser = rhsCurser->prev;
	}
	return false;
}

const BigInteger & BigInteger::Factorial(int i)
{
	if (i <= 1)
		return BigInteger::One;

	BigInteger * total = new BigInteger(i);
	while (i > 1)
	{
		BigInteger next(i - 1);
		*total = *total * next;
		i--;
	}
	return *total;
}

BigInteger & BigInteger::Half(const BigInteger & num)
{
	BigInteger * copy = new BigInteger(num);
	BigIntegerNode * curser = copy->tail;
	int carry = 0;
	while (curser != NULL)
	{
		int value = curser->value + carry;
		curser->value = value / 2;
		carry = (value % 2) * LIMIT;
		curser = curser->prev;
	}

	// remove extra length
	curser = copy->tail;
	while (curser->value <= 0 && curser != copy->head)
	{
		curser = curser->prev;
		delete curser->next;
		curser->next = NULL;
		copy->tail = curser;
		copy->length--;
	}
	return *copy;
}

double BigInteger::BinomialCoefficient(int n, int k)
{
	BigInteger numerator (BigInteger::Factorial(n));
	BigInteger demoninatorR (BigInteger::Factorial(k));
	BigInteger demoninatorNR (BigInteger::Factorial(n - k));
	BigInteger denominator (demoninatorNR * demoninatorR);
	BigInteger result (numerator / denominator);

	// calculate the total number of bits
	BigInteger temp (result * BigInteger::One);
	int numBits = 0;
	if (temp > BigInteger::Zero)
	{
		temp = BigInteger::Half(temp);
		numBits++;
	}

	// reduce till the number of bits is less or equal to than 53 (52 for mantissa + 1)
	int exp = 0;
	while (numBits > 53)
	{
		result = Half(result);
		numBits--;
		exp++;
	}
	long mult = (long)1 << exp; // 2^exp

	// generate mantissa number, should have no more than 53 bits
	long total = 0;
	long step = 0;
	for (BigIntegerNode * curser = result.head; curser != NULL; curser = curser->next)
	{
		long multiplier = step * LIMIT;
		if (multiplier == 0)
			multiplier = 1;
		step++;
		total += (long)curser->value * multiplier;
	}

	return (double)total * (double)mult;
}


bool operator<=(const BigInteger & lhs, const BigInteger & rhs)
{
	return !(lhs > rhs);
}

bool operator>=(const BigInteger & lhs, const BigInteger & rhs)
{
	return !(lhs < rhs);
}


