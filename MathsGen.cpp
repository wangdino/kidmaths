#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

int num(int nmin, int nmax);	// Generate a random integer
bool oper(int opertype);	// Input: 0=random; 1=addition; 2=deduction, Output: 0=addition; 1=deduction
bool neg(int num1, int num2);	// Check whether solution from a deduction is negative or not: 1=neg; 0=pos or 0

int main() 
{
	int exer=100, opertype=0, max1=19, max2=9;
	char const* fname = "Output.txt";

	ofstream exp(fname);
	if (exp.is_open()) {
		for (int i = 0; i < exer; i++)
		{
			int num1 = num(0, max1);
			int num2 = num(0, max2);
			bool op = oper(opertype);
			if (op)
			{
				if (neg(num1, num2))
				{
					int swap = num1;
					num1 = num2;
					num2 = swap;
					// cout << "Swap done." << endl;
				}
				exp << num1 << " - " << num2 << " =\n";
			}
			else
			{
				exp << num1 << " + " << num2 << " =\n";
			}
		}
		exp.close();
		cout << "File generated successfully." << endl;
	}
	else {
		cout << "File operation error!" << endl;
	}
	
	return 0;
}

int num(int nmin, int nmax)
{
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed); 
	uniform_int_distribution<int> distribution(nmin, nmax);
	int num = distribution(generator);
	return num;
}

bool oper(int opertype)
{
	if (opertype != 1 && opertype != 2)
	{
		opertype = num(0, 1);
	}
	if (opertype == 1)
	{
		return false;
	}
	
	return true;
}

bool neg(int num1, int num2)
{
	if (num1 - num2 >= 0)
	{
		return false;
	}
	return true;
}
