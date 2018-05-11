/*
Maths Exercise Generation by @wangdino
Version: 0.9.0
*/

#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int num(int nmin, int nmax);	// Generate a random integer in a certain range
char oper(int opertype);	// Input: 0=random; 1=addition; 2=deduction
bool neg(int num1, int num2);	// Check whether solution from a deduction is negative or not: 1=neg; 0=pos(incl.0)
vector<int> ReadConfig(string cfgname); // Function to read in configurations

int main() 
{
	vector<int> cfg = ReadConfig("Maths.ini");
	int exer = cfg[0];
	int opertype = cfg[1];
	int max1 = cfg[2];
	int min1 = cfg[3];
	int max2 = cfg[4];
	int min2 = cfg[5];

	char const* fname = "Output.txt";

	ofstream exp(fname);
	if (exp.is_open()) 
	{
		for (int i = 0; i < exer; i++)
		{
			int num1 = num(min1, max1);
			int num2 = num(min2, max2);
			char op = oper(opertype);
			if (op=='-' && neg(num1,num2))
			{
				int swap = num1;
				num1 = num2;
				num2 = swap;
			}
			exp << setw(2) << num1 << setw(2) << op << setw(3) << num2 << " =\n";
			
		}
		exp.close();
		cout << "File generated successfully." << endl;
	}
	else 
	{
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

char oper(int opertype)
{
	if (opertype != 1 && opertype != 2)
	{
		opertype = num(1, 2);
	}
	char op;
	if (opertype == 1)
	{
		op = '+';
	}
	else if (opertype == 2)
	{
		op = '-';
	}
	return op;
}

bool neg(int num1, int num2)
{
	if (num1 - num2 >= 0)
	{
		return false;
	}
	return true;
}

vector<int> ReadConfig(string cfgname)
{
	vector<int> out;
	int exer = 100, opertype = 0, max1 = 19, min1 = 0, max2 = 9, min2 = 0, tmax = 0;

	if (cfgname == "")
	{
		cfgname = "Maths.ini";
	}

	ifstream cfg_in(cfgname);
	if (cfg_in.is_open() == false)
	{
		out.push_back(exer);
		out.push_back(opertype);
		out.push_back(max1);
		out.push_back(min1);
		out.push_back(max2);
		out.push_back(min2);
		out.push_back(tmax);
		return out;
	}

	string cfg_line;
	istringstream param;

	while (getline(cfg_in, cfg_line))
	{
		param.str(cfg_line.substr(cfg_line.find("=") + 1));
		if (cfg_line.find("No. of Exercises") != string::npos)
		{
			param >> exer;
		}
		else if (cfg_line.find("Operation Type") != string::npos)
		{
			param >> opertype;
		}
		else if (cfg_line.find("Num1 Max") != string::npos)
		{
			param >> max1;
		}
		else if (cfg_line.find("Num1 Min") != string::npos)
		{
			param >> min1;
		}
		else if (cfg_line.find("Num2 Max") != string::npos)
		{
			param >> max2;
		}
		else if (cfg_line.find("Num2 Min") != string::npos)
		{
			param >> min2;
		}
		else if (cfg_line.find("Result Max") != string::npos)
		{
			param >> tmax;
		}
		param.clear();
	}
	out.push_back(exer);
	out.push_back(opertype);
	out.push_back(max1);
	out.push_back(min1);
	out.push_back(max2);
	out.push_back(min2);
	out.push_back(tmax);
	return out;
}