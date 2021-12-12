// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#pragma once

#include "stack.h"

#include <string>
#include <vector>

using namespace std;

class Part
{
public:
	Part();
	Part(string& s);
	char Type();
	string Operation();
	double& Value();
	bool Pr();
private:
	string operation;
	double value;
	char type;
	bool pr;
};

class Formula
{
public:
	Formula(string& s);
	double Solve();
	~Formula();
private:
	Part* A;
	size_t size;
};