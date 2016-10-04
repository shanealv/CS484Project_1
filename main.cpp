#include "BigInteger.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		cout << "### Description ###" << endl;
		cout << "This program calculates the probability of more than the target number of users is active at any given moment in time" << endl;
		cout << endl;
		cout << "### Usage ###" << endl;
		cout << "program [int] [int] [float]" << endl;
		cout << endl;
		cout << "### Example ###" << endl;
		cout << "program 35 10 0.10" << endl;
		cout << endl;
		cout << "### Argument Overview ###" << endl;
		cout << "This program requires 5 arguments:" << endl;
		cout << "[integer] total bandwidth of the system" << endl;
		cout << "[integer] per user bandwidth of the system" << endl;
		cout << "[integer] number of users in the system" << endl;
		cout << "[integer] target number of users" << endl;
		cout << "[double]  probability a user is idle" << endl;
		cout << endl;
		return 0;
	}

	else if (argc != 6)
	{
		cout << "Invalid Number of Arguments" << endl;
		return 0;
	}

	int tb = atoi(argv[1]);
	if (tb <= 0)
	{
		cout << "Invalid Total Bandwidth" << endl;
		return 0;
	}

	int ub = atoi(argv[2]);
	if (ub <= 0)
	{
		cout << "Invalid User Bandwidth" << endl;
		return 0;
	}

	int n = atoi(argv[3]);
	if (n <= 0)
	{
		cout << "Invalid Number of Users" << endl;
		return 0;
	}
	else if (n > 250)
	{
		cout << "Total user counts above 250 not supported" << endl;
		return 0;
	}

	int t = atoi(argv[4]);
	if (t <= 0)
	{
		cout << "Invalid targer number of users" << endl;
		return 0;
	}
	else if (t >= n)
	{
		cout << "Target number of users must be less than or equal to total user count" << endl;
		return 0;
	}

	double p = (double)atof(argv[5]);
	if (p <= 0.0 || p > 1.0)
	{
		cout << "Probability of user being idle must be in range (0,1]" << endl;
		return 0;
	}

	cout << "Total Bandwidth:" << tb << endl;
	cout << "User Bandwidth:\t" << ub << endl;
	cout << "Num Users:\t" << n << endl;
	cout << "Target Users:\t" << t << endl;
	cout << "P(Idle):\t" << p << endl << endl;

	double finalResult = 0.0;
	for (int k = 0; k <= t; k++)
	{
		finalResult +=
			BigInteger::BinomialCoefficient(n, k)
			* pow(p, k) * pow(1.0 - p, n - k);
	}

	cout << "Probability of greater than " << t << " users: " << (1 - finalResult) << endl;
}
