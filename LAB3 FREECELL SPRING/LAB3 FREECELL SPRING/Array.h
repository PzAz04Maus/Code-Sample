/* ************
Stephen Carter
Array.h
Created 6APR21?
*/
#pragma once
#include "exception.h"
#include "Card.h"

/* Class: iter_array

Purpose: Handles iterating through class Array

Manager Functions
	iter_array(T* value)
	~iter_array();
		empty
	operator=(const iter_array<T>&copy)

Data Members
	T* m_ptr

Methods
	operator*()
	operator==
	operator!=
	operator++()
	operator++(int)

*/


template<class T>
class iter_array
{
public:
	iter_array(T* value);
	~iter_array();
	iter_array<T>& operator=(const iter_array<T>& copy);

	T& operator*();
	template<class T> friend bool operator==(const iter_array<T>& left, const iter_array<T>& right);
	template<class T> friend bool operator!=(const iter_array<T>& left, const iter_array<T>& right);

	iter_array<T>& operator++();
	iter_array<T> operator++(int);
private:
	T* m_ptr;

};

/* Class: Array

Purpose: A single dimensional Dynamic array with iter_array and first class characteristics


New methods
	isEmpty
	peek

Friend classes
	iter_array<T>

Manager Functions:
	Array();
	Array(int size, int index = 0);
	Array(Array<T>& copy);
	Array(Array<T>&& move);
	~Array();

	Array<T>& operator=(Array<T>& copy);
	Array<T>& operator=(Array<T>&& move);

Data Members
	T* m_data;
	int m_size;
	int m_index;
		Default is 0

New Methods(Freecell)
	template<> Array<Card>::Array(int size, int index)
		Constructor specialization  that doesn't dynamically allocate container memory
	bool isEmpty();
		is getLength() 0?
	T peek();
		peek top of the stack
	T peekElement(int i);
		boundary check whether index is a legal size, then peeks at element @ index
	void extractElement(int i);
		take element at index i and remove it from the stack
	bool checkIndexEmpty(int index);
		For Cascade
		Is the container at index empty or is it full?
	template <> bool Array<Card>::checkIndexEmpty(int index)
		Card object instance of checkIndexEmpty
		Checks if there is an object@index, and whether that object is an empty card

Methods
	operator[](int index)
		one problem with the unit testing provided is that they required operator[] to do bounds checking when the specifications REQUIRED it to not boundary check
		Therefoore, operator[] is now an alias for at()
	at(int index)
		boundary checks and returns element @ index
	*data()
		returns raw array data
	for_each
		applies function with 1 argument of a T reference to the entire database
	push_back(T value)
		increases m_size by 1 and initializes that data with value
	pop_back()
		deletes the last element. Doesn't return anything
	pop_return()
		like pop_back, but returns the value of the deleted element
	setLength(int size)
	setStartIndex()
	getLength()
		while the specifications required this to be getSize(), the unit tests required getLength(). Therefore, the code was refactored to adhere to the unit tests
	getStartIndex()

	begin()
		constructs an iter_array of the beginning element
	end()
		constructs an iter_array of the element past the end
*/

template <class T>
class Array
{
public:
	//canonicals
	Array();
	Array(int size, int index = 0);
	Array(Array<T>& copy);
	Array(Array<T>&& move);
	~Array();

	Array<T>& operator=(Array<T>& copy);
	Array<T>& operator=(Array<T>&& move);

	//Freecell content
	bool isEmpty();
	T peek();
	T peekElement(int i);
	void extractElement(int i);
	bool checkIndexEmpty(int index);

	//content
	T& operator[](int index);
	T& at(int index);
	T* data();
	void for_each(void (*fn)(T& data));

	void push_back(T value);
	void pop_back();
	T pop_return();

	void setLength(int size);
	void setStartIndex(int index);

	int getLength();//size();
	int getStartIndex();



	//forward iter_array
	friend class iter_array<T>;

	iter_array<T> begin();
	iter_array<T> end();

private:
	T* m_data;
	int m_size;
	int m_index;
};


template<class T>
inline Array<T>::Array()
	:Array(0)
{

}

template<class T>
inline Array<T>::Array(int size, int index)
	: m_size(size), m_data(nullptr), m_index(index)
{
	if (m_size < 0)
	{
		throw Exception(L"illegal array size");
	}
	else
	{
		if (index > size)
		{
			throw Exception(L"index higher than length");
		}

		m_data = new T[size];
	}
}
template<>
inline Array<Card>::Array(int size, int index)
	: m_size(size), m_data(nullptr), m_index(index)
{
	if (m_size < 0)
	{
		throw Exception(L"illegal array size");
	}
	else
	{
		if (index > size)
		{
			throw Exception(L"index higher than length");
		}

	}
}


template<class T>
inline Array<T>::Array(Array<T>& copy)
	:m_size(copy.m_size), m_data(new T[copy.m_size]), m_index(copy.m_index)
{
	for (int i = 0; i < m_size; i++)
	{
		at(i) = copy.at(i);
	}
}

template<class T>
inline Array<T>::Array(Array<T>&& move)
	:m_size(move.m_size), m_data(move.m_data), m_index(move.m_index)
{
	move.m_size = 0;
	move.m_index = 0;
	move.m_data = nullptr;
}

template<class T>
inline Array<T>::~Array()
{
	delete[]m_data;
}

template<class T>
inline Array<T>& Array<T>::operator=(Array<T>& copy)
{
	if (this != &copy)
	{
		delete[]m_data;
		m_size = copy.m_size;
		m_index = copy.m_index;

		m_data = new T[m_size];
		for (int i = 0; i < m_size; i++)
		{
			m_data[i] = copy.m_data[i];
		}

		m_size = copy.m_size;
		m_index = copy.m_index;
	}
	else
	{
		throw Exception(L"Cannot copy to self!");
	}
	return *this;
}

template<class T>
inline Array<T>& Array<T>::operator=(Array<T>&& move)
{
	if (this != &move)
	{
		delete m_data;

		m_data = move.m_data;
		m_size = move.m_size;
		m_index = move.m_index;

		move.m_data = nullptr;
		move.m_size = 0;
		move.m_index = 0;
	}
	else
	{
		throw Exception(L"Cannot move to self!");
	}

	return *this;
}

template<class T>
inline T& Array<T>::operator[](int index)
{

	//since this doesn't have bounds testing DESPITE the requirements asking for no bounds checking...
	return at(index);
	//return m_data[index - m_index];
}

template<class T>
inline T& Array<T>::at(int index)
{

	if (m_data == nullptr)
	{
		throw Exception(L"Empty array!");
	}
	else
	{
		if ((index > m_size + m_index) || (index < m_index))
		{
			throw Exception(L"Out of bounds!");
		}
		else
		{
			return m_data[index - m_index];
		}
	}

}

template<class T>
inline T* Array<T>::data()
{
	return m_data;
}

template<class T>
inline void Array<T>::for_each(void(*fn)(T& data))
{
	for (int i = 0; i < m_size; i++)
	{
		(*fn)(m_data[i]);
	}
}

template<class T>
inline void Array<T>::setLength(int size)
{
	if (size < 0)
	{
		throw Exception(L"length not right");
	}
	else
	{
		T* temp = new T[m_size];
		for (int i = 0; i < m_size; i++)
		{
			temp[i] = m_data[i];
		}
		delete[]m_data;
		m_data = new T[size];

		int shortest = m_size < size ? m_size : size;

		for (int i = 0; i < shortest; i++)
		{
			m_data[i] = temp[i];
		}

		m_size = size;
		delete[]temp;
		temp = nullptr;
	}
}

template<class T>
inline void Array<T>::setStartIndex(int index)
{
	m_index = index;
}

template<class T>
inline int Array<T>::getLength()
{
	return m_size;
}

template<class T>
inline int Array<T>::getStartIndex()
{
	return m_index;
}

template<class T>
inline bool Array<T>::isEmpty()
{
	return (getLength() == 0);
}

template<class T>
inline T Array<T>::peek()
{
	return m_data[m_size - 1];
}

template<class T>
inline T Array<T>::peekElement(int i)
{
	if (i < m_size)
	{
		return m_data[i];
	}
	
}

template<class T>
inline bool Array<T>::checkIndexEmpty(int index)
{
	bool check = true;
	if (m_data != nullptr)
	{
		check = (m_data[index] == nullptr);
	}

	return check;
}

template<>
inline bool Array<Card>::checkIndexEmpty(int index)
{
	bool check = true;
	if (m_data != nullptr)
	{
		if (&m_data[index] != nullptr)
		{

			if (index < getLength())//don't go into garbage
			{
				if (m_data[index].getRank() != RANK::EMPTY
					&& m_data[index].getSuit() != SUIT::EMPTY)
				{
					check = false;
				}
			}
		}
	}

	return check;
}

template<class T>
inline iter_array<T> Array<T>::begin()
{
	return iter_array<T>(&m_data[0]);
}

template<class T>
inline iter_array<T> Array<T>::end()
{
	return iter_array<T>(&m_data[m_size]);
}

template<class T>
inline void Array<T>::push_back(T value)
{
	setLength(m_size + 1);
	m_data[m_size - 1] = value;
}

template<class T>
inline void Array<T>::pop_back()
{
	setLength(m_size - 1);
}

template<class T>
inline T Array<T>::pop_return()
{
	T data = m_data[m_size - 1];
	setLength(m_size - 1);
	return data;
}


template<class T>
inline void Array<T>::extractElement(int place)
{
	T* temp = new T[m_size - 1];
	int temp_i = 0;
	if (place > 0 || place < m_size)
	{
		for (int i = 0; i < m_size; i++)
		{
			if (i != place)
			{
				temp[temp_i] = m_data[i];
				temp_i++;
			}

		}
	}
	delete[]m_data;

	m_size -= 1;
	m_data = new T[m_size];

	for (int i = 0; i < m_size; i++)
	{
		m_data[i] = temp[i];
	}
	delete[]temp;
	temp = nullptr;
}

template<class T>
inline T& iter_array<T>::operator*()
{
	return *m_ptr;
}

template<class T>
inline iter_array<T>& iter_array<T>::operator++()
{
	m_ptr++;
	return *this;
}

template<class T>
inline iter_array<T> iter_array<T>::operator++(int)
{
	iter_array temp = *this;
	++(*this);
	return temp;
}

template<class T>
inline iter_array<T>::iter_array(T* value)
	:m_ptr(value)
{

}

template<class T>
inline iter_array<T>::~iter_array()
{

}

template<class T>
inline iter_array<T>& iter_array<T>::operator=(const iter_array<T>& copy)
{
	if (*this != copy)
	{
		m_ptr = copy.m_ptr;
	}
	else
	{
		throw Exception(L"Illegal copying of self!");
	}
	return *this;
}

template<class T>
inline bool operator==(const iter_array<T>& left, const iter_array<T>& right)
{
	return left.m_ptr == right.m_ptr;
}
template<class T>
inline bool operator!=(const iter_array<T>& left, const iter_array<T>& right)
{
	return left.m_ptr != right.m_ptr;
}
