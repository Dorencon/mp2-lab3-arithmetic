// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#include <exception>

using namespace std;

template <typename T>
class TStack
{
public:
	TStack(int n)
	{
		if (n < 0)
		{
			throw runtime_error("Negative size");
		}
		size = 0;
		Msize = n;
		A = new T[n];
	};
	void push(T b)
	{
		if (size == Msize)
		{
			T* B = new T[size * 2];
			for (size_t i =0; i < size; i++)
			{
				B[i] = A[i];
			}
			delete[](A);
			A = B;
		}
		A[size] = b;
		size++;
	};
	void pop()
	{
		if (size == 0)
		{
			throw runtime_error("Pop used on empty stack");
		}
		size--;
	};
	T& peek()
	{
		if (size == 0)
		{
			throw runtime_error("Peek used on empty stack");
		}
		return A[size - 1];
	};
	bool is_empty()
	{
		return !size;
	};
	size_t length()
	{
		return size;
	};
	void clear()
	{
		size = 0;
	};
	~TStack()
	{
		size = 0;
		delete[](A);
	};
private:
	size_t size;
	size_t Msize;
	T* A;
};