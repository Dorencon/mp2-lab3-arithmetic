// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<double> st(5));
}

TEST(TStack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<double> st(-5));
}

TEST(TStack, can_add_to_stack)
{
	TStack<double> st(5);
	st.push(10);
	ASSERT_EQ(st.peek(), 10);
}

TEST(TStack, can_delete_elements)
{
	TStack<double> st(5);
	st.push(10);
	st.push(12);
	st.push(13);
	st.pop();
	ASSERT_EQ(st.peek(), 12);
}

TEST(TStack, cant_delete_elements_when_size_is_zero)
{
	TStack<double> st(5);
	ASSERT_ANY_THROW(st.pop());
}

TEST(TStack, cant_peek_elements_when_size_is_zero)
{
	TStack<double> st(5);
	ASSERT_ANY_THROW(st.peek());
}

TEST(TStack, can_check_emptyness)
{
	TStack<double> st(5);
	ASSERT_EQ(st.is_empty(), true);
}

TEST(TStack, can_clear_stack)
{
	TStack<double> st(5);
	st.push(1);
	st.push(2);
	st.clear();
	ASSERT_EQ(st.is_empty(), true);
}

TEST(TStack, length_function_returns_stack_size)
{
	TStack<double> st(5);
	st.push(1);
	st.push(2);
	ASSERT_EQ(st.length(), 2);
}