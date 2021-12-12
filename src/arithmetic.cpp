// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"

#include <exception>
#include <sstream>

using namespace std;

vector<char> correct = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '+', '-', '*', '/', '(', ')' };

Part::Part(){};

Part::Part(string& s)
{
	bool t;
	for (size_t i = 0; i < s.size(); i++)
	{
		t = true;
		for (size_t j = 0; j < correct.size(); j++)
		{
			if (s[i] == correct[j])
			{
				t = false;
				break;
			}
		}
		if (t)
		{
			throw runtime_error("Wrong symbol");
		}
	}
	if (((s[0] >= '0') && (s[0] <= '9')) || ((s.size() > 1) && (s[1] >= '0') && (s[1] <= '9')))
	{
		value = stod(s);
		type = 'v';
	}
	else if((s[0] == '(') || (s[0] == ')'))
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

Formula::Formula(string& s)
{
	stringstream ss;
	ss << s;
	string s1;
	A = new Part[s.size() / 2 + 1];
	size_t l = 0;
	TStack<Part> st(5);
	char pr = 'n';
	size_t pos = 0;
	bool minus = false;
	stringstream sserr;
	string serr;
	while (ss >> s1)
	{
		try
		{
			Part p(s1);
		}
		catch (runtime_error* e)
		{
			sserr << "Wrong symbol from " << pos << " to " << pos + s.size();
			getline(sserr, serr);
			throw runtime_error(serr);
		}
		Part p(s1);
		char t = p.Type();
		if (t == 'v')
		{
			if (pr == 'v')
			{
				sserr << "Missed operator between two values at " << pos - 1;
				getline(sserr, serr);
				throw runtime_error(serr);
			}
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
			if (l == 0)
			{
				sserr << "Missing value at " << pos;
				getline(sserr, serr);
				throw runtime_error(serr);
			}
			st.push(p);
			pr = 'o';
		}
		else if (t == 'b')
		{
			if (p.Operation() == "(")
			{
				if (pr == 'v')
				{
					sserr << "Missed operator before bracket at " << pos;
					getline(sserr, serr);
					throw runtime_error(serr);
				}
				st.push(p);
				pr = 'l';
			}
			else
			{
				if (pr = 'o')
				{
					sserr << "Missing value at " << pos - 1;
					getline(sserr, serr);
					throw runtime_error(serr);
				}
				while (!((st.peek().Type() == 'b') && (st.peek().Operation() == "(")))
				{
					if (st.is_empty())
					{
						sserr << "Missed left bracket. The right bucket was at " << pos;
						getline(sserr, serr);
						throw runtime_error(serr);
					}
					A[l] = st.peek();
					l++;
					st.pop();
				}
				st.pop();
				pr = 'r';
			}
		}
		pos += 1 + s1.size();
	}
	if (pr == 'o')
	{
		sserr << "Missing value at " << pos;
		getline(sserr, serr);
		throw runtime_error(serr);
	}
	while (!st.is_empty())
	{
		if ((st.peek().Type() == 'b') && (st.peek().Operation() == "("))
		{
			sserr << "Missed right bracket";
			getline(sserr, serr);
			throw runtime_error(serr);
		}
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