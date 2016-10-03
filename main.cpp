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
		cout << "This program requires 3 arguments:" << endl;
		cout << "[integer] number of users in the system" << endl;
		cout << "[integer] target number of users" << endl;
		cout << "[double]  probability a user is idle" << endl;
		cout << endl;
		return 0;
	}
	else if (argc < 4)
	{
		cout << "Invalid Number of Arguments" << endl;
		return 0;
	}
	int n = atoi(argv[1]);
	int t = atoi(argv[2]);
	double p = (double) atof(argv[3]);
	
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

	cout << "Probability of greater than " << t << " users: " << (1 -finalResult) << endl;
}
