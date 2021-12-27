// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"

#include <exception>
#include <sstream>
#include <iostream>

using namespace std;

vector<char> correct = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '+', '-', '*', '/', '(', ')' };

Part::Part(){};

Part::Part(string& s)
{
	if (((s[0] >= '0') && (s[0] <= '9')) || ((s.size() > 1) && (s[1] >= '0') && (s[1] <= '9')))
	{
		value = stod(s);
		type = 'v';
	}
	else if ((s[0] == '(') || (s[0] == ')'))
	{
		operation = s;
		type = 'b';
	}
	else
	{
		if ((s == "+") || (s == "-"))
		{
			pr = 0;
		}
		else
		{
			pr = 1;
		}
		operation = s;
		type = 'o';
	}
}

char Part::Type()
{
	return type;
}

string Part::Operation()
{
	return operation;
}

double& Part::Value()
{
	return value;
}

bool Part::Pr()
{
	return pr;
}

void error_search(vector<Part> A)
{
	TStack<size_t> st(5);
	stringstream sserr;
	string serr;
	for (size_t i = 0; i < A.size(); i++)
	{
		if (A[i].Type() == 'v')
		{
			if ((i > 0) && ((A[i - 1].Type() == 'v') || ((A[i - 1].Type() == 'b') && (A[i - 1].Operation() == ")"))))
			{
				sserr << "Missing operation for value at " << i + 1;
				getline(sserr, serr);
				throw runtime_error(serr);
			}
		}
		else if (A[i].Type() == 'o')
		{
			if (A[i].Operation() != "-")
			{
				if ((i == 0) || ((A[i - 1].Type() == 'b') && (A[i - 1].Operation() == "(")))
				{
					sserr << "Missing value for operation at " << i + 1;
					getline(sserr, serr);
					throw runtime_error(serr);
				}
			}
			if ((i > 0) && (A[i - 1].Type() == 'o'))
			{
				sserr << "Two operations without a value at " << i + 1;
				getline(sserr, serr);
				throw runtime_error(serr);
			}
		}
		else if (A[i].Type() == 'b')
		{
			if (A[i].Operation() == "(")
			{
				st.push(i);
			}
			else
			{
				if (!st.is_empty())
				{
					st.pop();
				}
				else
				{
					sserr << "Missing left bracket for bracket at " << i + 1;
					getline(sserr, serr);
					throw runtime_error(serr);
				}
			}
		}
	}
	if (!st.is_empty())
	{
		sserr << "Missing right bracket for bracket at " << st.peek() + 1;
		getline(sserr, serr);
		throw runtime_error(serr);
	}
	if (A[A.size() - 1].Type() == 'o')
	{
		sserr << "Missing value at " << A.size();
		getline(sserr, serr);
		throw runtime_error(serr);
	}
}

Formula::Formula(string& s)
{
	string s1;
	A = new Part[s.size()];
	size_t l = 0;
	TStack<Part> st(5);
	char pr = 'n';
	size_t pos = 0;
	bool minus = false;
	stringstream sserr;
	string serr;
	size_t i = 0;
	vector<Part> pv;
	while (i < s.size())
	{
		if (((s[i] < '0') || (s[i] > '9')) && (s[i] != '.'))
		{
			if (s[i] == ' ')
			{
				i++;
				continue;
			}
			if ((s[i] == '+') || (s[i] == '-') || (s[i] == '*') || (s[i] == '/') || (s[i] == '(') || (s[i] == ')'))
			{
				s1 = "";
				s1 = s1 + s[i];
			}
			else if (s[i] == 'x')
			{
				cout << "Please enter x" << endl;
				getline(cin, s1);
			}
			else
			{
				sserr << "Wrong symbol at " << i + 1;
				getline(sserr, serr);
				throw runtime_error(serr);
			}
			i++;
		}
		else
		{
			size_t j = i;
			stringstream ss;
			while ((j < s.size()) && (((s[j] >= '0') && (s[j] <= '9')) || (s[j] == '.')))
			{
				ss << s[j];
				j++;
			}
			ss >> s1;
			i = j;
		}
		Part p(s1);
		pv.push_back(p);
	}
	try
	{
		error_search(pv);
	}
	catch (runtime_error* e)
	{
		throw runtime_error(e->what());
	}
	for (size_t i = 0; i < pv.size(); i++)
	{
		Part p = pv[i];
		char t = p.Type();
		if (t == 'v')
		{
			pr = 'v';
			if (!minus)
			{
				A[l] = p;
			}
			else
			{
				p.Value() = -p.Value();
				A[l] = p;
				minus = false;
			}
			l++;
		}
		else if (t == 'o')
		{
			while (!((st.is_empty()) || ((st.peek().Type() == 'b') && (st.peek().Operation() == "(")) || (p.Pr() > st.peek().Pr())))
			{
				A[l] = st.peek();
				l++;
				st.pop();
			}
			if ((p.Operation() == "-") && ((l == 0) || (pr == 'l')))
			{
				minus = true;
				pos += 2;
				continue;
			}
			st.push(p);
			pr = 'o';
		}
		else if (t == 'b')
		{
			if (p.Operation() == "(")
			{
				st.push(p);
				pr = 'l';
			}
			else
			{
				while (!((st.peek().Type() == 'b') && (st.peek().Operation() == "(")))
				{
					A[l] = st.peek();
					l++;
					st.pop();
				}
				st.pop();
				pr = 'r';
			}
		}
	}
	while (!st.is_empty())
	{
		A[l] = st.peek();
		l++;
		st.pop();
	}
	size = l;
}

double Formula::Solve()
{
	TStack<double> st(size);
	double t1, t2;
	for (size_t i = 0; i < size; i++)
	{
		if (A[i].Type() == 'v')
		{
			st.push(A[i].Value());
		}
		else
		{
			if (A[i].Operation() == "+")
			{
				t1 = st.peek();
				st.pop();
				t2 = st.peek();
				st.pop();
				st.push(t1 + t2);
			}
			else if (A[i].Operation() == "-")
			{
				if ((st.is_empty()) || (A[i - 1].Type() == 'o'))
				{
					A[i + 1].Value() *= -1;
				}
				t1 = st.peek();
				st.pop();
				t2 = st.peek();
				st.pop();
				st.push(t2 - t1);
			}
			else if (A[i].Operation() == "*")
			{
				t1 = st.peek();
				st.pop();
				t2 = st.peek();
				st.pop();
				st.push(t1 * t2);
			}
			else if (A[i].Operation() == "/")
			{
				t1 = st.peek();
				st.pop();
				t2 = st.peek();
				st.pop();
				st.push(t2 / t1);
			}
		}
	}
	return st.peek();
}

Formula::~Formula()
{
	size = 0;
	delete[](A);
}