// тесты для вычисления арифметических выражений

#include <gtest.h>
#include <arithmetic.h>

TEST(Formula, plus_makes_sum)
{
	string s = "1+2";
	Formula f(s);
	ASSERT_EQ(f.Solve(), 3);
}

TEST(Formula, multiplication_makes_composition)
{
	string s = "3 * 2";
	Formula f(s);
	ASSERT_EQ(f.Solve(), 6);
}

TEST(Formula, minus_makes_difference)
{
	string s = "1 - 2";
	Formula f(s);
	ASSERT_EQ(f.Solve(), -1);
}

TEST(Formula, division_makes_ratio)
{
	string s = "1 / 2";
	Formula f(s);
	ASSERT_EQ(f.Solve(), 0.5);
}

TEST(Formula, cant_use_forbidden_symbols)
{
	string s = "b";
	ASSERT_ANY_THROW(Formula f(s));
}

TEST(Formula, cant_lose_operation)
{
	string s = "1 2";
	ASSERT_ANY_THROW(Formula f(s));
}

TEST(Formula, cant_lose_right_bracket)
{
	string s = "1 + ( 2 - 3 ";
	ASSERT_ANY_THROW(Formula f(s));
}

TEST(Formula, cant_lose_left_bracket)
{
	string s = "2 + 2 ) / 4";
	ASSERT_ANY_THROW(Formula f(s));
}

TEST(Formula, cant_lose_value)
{
	string s = "1 +";
	ASSERT_ANY_THROW(Formula f(s));
}