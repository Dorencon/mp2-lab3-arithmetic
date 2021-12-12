// реализация пользовательского приложения
#include "arithmetic.h"

#include <iostream>
#include <clocale>

using namespace std;

int main()
{
	cout << "Enter formulas" << endl;
	string s;
	while (getline(cin, s))
	{
		try
		{
			Formula f(s);
			cout << f.Solve() << endl;
		}
		catch (runtime_error* e)
		{
			cerr << e;
		}
	}
	return 0;
}
