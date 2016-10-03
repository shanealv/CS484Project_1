#include <iostream>
#include <iomanip>
#include "BigInteger.h"

using namespace std;

BigInteger BigInteger::Zero(0);
BigInteger BigInteger::One(1);
BigInteger BigInteger::Two(2);

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


BigInteger& BigInteger::operator+(BigInteger& other)
{
	bool isNegative = false;
	if (this->negative && other.negative) // -a + -b = -(a + b)
		isNegative = true;
	else if (this->negative) // -a + b = b - a
	{
		this->negative = false; // make positive
		BigInteger & result = other - *this;
		this->negative = true; // restore sign
		return result;
	}
	else if (other.negative) // a + -b = a - b
	{
		other.negative = false; // make positive
		BigInteger & result = *this - other;
		other.negative = true; // restore sign
		return result;
	}

	BigInteger * out = new BigInteger();
	*out = *this; // copy this to out
	out->negative = isNegative;
	BigIntegerNode * outCurser = out->head;
	BigIntegerNode * rhsCurser = other.head;

	int carry = 0;
	while (true)
	{
		int rhsValue = 0;
		if (rhsCurser != NULL)
		{
			rhsValue = rhsCurser->value;
			rhsCurser = rhsCurser->next;
		}
		int sum = outCurser->value + rhsValue + carry;
		outCurser->value = sum % LIMIT;
		carry = sum / LIMIT;

		if (rhsCurser == NULL && carry == 0)
			break;

		BigIntegerNode * newNode = outCurser->next;
		if (newNode == NULL)
		{
			newNode = new BigIntegerNode();
			newNode->prev = outCurser;
			outCurser->next = newNode;
			out->tail = newNode;
			out->length++;
		}
		outCurser = newNode;
	}
	return *out;
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

BigInteger& BigInteger::operator-(BigInteger& other)
{
	if (this->negative && other.negative) // -a - -b = b - a
	{
		this->negative = false;
		other.negative = false;
		BigInteger & result = other - *this;
		this->negative = !(this->negative);
		other.negative = true;
		return result;
	}
	else if (this->negative) // -a - b = -(a + b)
	{
		this->negative = false;
		BigInteger & result = *this + other;
		result.negative = true;
		this->negative = true;
		return result;
	}
	else if (other.negative) // a - -b = a + b
	{
		other.negative = false;
		BigInteger & result = *this + other;
		other.negative = true;
		return result;
	}
	else if (other > *this) // a - b = -(b - a)
	{
		BigInteger & result = other - *this;
		result.negative = true;
		return result;
	}

	BigInteger * out = new BigInteger();
	*out = *this; // copy this to out
	BigIntegerNode * outCurser = out->tail;
	BigIntegerNode * rhsCurser = other.tail;

	int sizeDiff = out->length - other.length;
	while (sizeDiff > 0) // align the cursers
	{
		outCurser = outCurser->prev;
		sizeDiff--;
	}

	while (outCurser != NULL)
	{
		int diff = outCurser->value - rhsCurser->value;
		if (diff < 0) // initiate borrow routine
		{
			diff += Borrow(outCurser->next);
		}

		outCurser->value = diff;
		outCurser = outCurser->prev;
		rhsCurser = rhsCurser->prev;
	}

	outCurser = out->tail;
	while (outCurser->value <= 0 && outCurser != out->head)
	{
		outCurser = outCurser->prev;
		delete outCurser->next;
		outCurser->next = NULL;
		out->tail = outCurser;
		out->length--;
	}

	return *out;
}

BigInteger & BigInteger::operator*(BigInteger & other)
{
	// use the smaller number to multiple the large one
	if (*this < other)
		return other * (*this);

	BigInteger * result = new BigInteger();
	BigInteger * counter = new BigInteger();
	*counter = other;
	counter->negative = false;
	while (*counter > BigInteger::Zero)
	{
		*result = *result + *this;
		*counter = *counter - BigInteger::One;
	}
	delete counter;

	// if both values are positive or both are negative, then result is positive
	if ((this->negative && other.negative) || (!this->negative && !other.negative))
		result->negative = false;
	else
		result->negative = true;

	return *result;
}

BigInteger & BigInteger::operator/(BigInteger & other)
{
	BigInteger * lhs_copy = new BigInteger();
	BigInteger * rhs_copy = new BigInteger();
	BigInteger * counter = new BigInteger();
	*lhs_copy = *this;
	*rhs_copy = other;
	lhs_copy->negative = false;
	rhs_copy->negative = false;
	while (*lhs_copy > BigInteger::Zero)
	{
		*lhs_copy = *lhs_copy - *rhs_copy;
		*counter = *counter + BigInteger::One;
	}
	delete lhs_copy;
	delete rhs_copy;

	// if both values are positive or both are negative, then result is positive
	if ((this->negative && other.negative) || (!this->negative && !other.negative))
		counter->negative = false;
	else
		counter->negative = true;

	return *counter;
}

bool BigInteger::operator>(const BigInteger& other)
{
	if (this->length > other.length)
		return true;
	if (other.length > this->length)
		return false;

	// numbers are of same length
	BigIntegerNode * lhsCurser = this->tail;
	BigIntegerNode * rhsCurser = other.tail;

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

bool BigInteger::operator<(const BigInteger& other)
{
	if (this->length < other.length)
		return true;
	if (other.length < this->length)
		return false;

	// numbers are of same length
	BigIntegerNode * lhsCurser = this->tail;
	BigIntegerNode * rhsCurser = other.tail;

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

BigInteger & BigInteger::Factorial(int i)
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

void BigInteger::Half(BigInteger & num)
{
	BigIntegerNode * curser = num.tail;
	int carry = 0;
	while (curser != NULL)
	{
		int value = curser->value + carry;
		curser->value = value / 2;
		carry = (value % 2) * (LIMIT / 2);
		curser = curser->prev;
	}

	// remove extra length
	curser = num.tail;
	while (curser->value <= 0 && curser != num.head)
	{
		curser = curser->prev;
		delete curser->next;
		curser->next = NULL;
		num.tail = curser;
		num.length--;
	}
}

double BigInteger::BinomialCoefficient(int n, int k)
{
	BigInteger & numerator = BigInteger::Factorial(n);
	BigInteger & demoninatorR = BigInteger::Factorial(k);
	BigInteger & demoninatorNR = BigInteger::Factorial(n - k);
	BigInteger & denominator = demoninatorNR * demoninatorR;
	BigInteger & result = numerator / denominator;

	// calculate the total number of bits
	BigInteger & temp = result * BigInteger::One;
	int numBits = 0;
	if (temp > BigInteger::Zero)
	{
		BigInteger::Half(temp);
		numBits++;
	}

	// reduce till the number of bits is less or equal to than 53 (52 for mantissa + 1)
	int exp = 0;
	while (numBits > 53)
	{
		Half(result);
		numBits--;
		exp++;
	}
	long mult = (long) 1 << exp; // 2^exp

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


bool BigInteger::operator<=(const BigInteger& other)
{
	return !(*this > other);
}

bool BigInteger::operator>=(const BigInteger& other)
{
	return !(*this < other);
}


