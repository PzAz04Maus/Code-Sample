/* ************
Stephen Carter
template<class T>
Stack A.h
Created 20APR21
First modification
*/

#pragma once
#include "Array.h"

/* AStack class

Purpose: To manage and interact with an array as a stack

Canonical Functions

	List();
		m_ptr is passed a default array. m_max(10)
	AStack(Array<T>* ptr, int maxSize = 10);
		m_ptr is assigned to a created array
	~AStack();
		deletes m_ptr.

	AStack(const AStack<T>& copy);
	AStack(AStack<T>&& move);
		move.m_ptr set to nullptr

	AStack<T>& operator=(const AStack& copy);
		m_ptr deleted
	AStack<T>& operator=(AStack&& move);
		m_ptr deleted
		move.m_ptr set to nullptr

Methods

	void Push(T value);
		throws exception if m_length goes over m_max
	T Pop();
		throws exception if isEmpty()
	const T Peek();
		throws exception if isEmpty()

	const bool isEmpty();
		true if m_ptr is 0 or Size() is 0
	bool isFull();
		true if Size >= m_max
	void setSize(int size);
		Changes max size to m_ptr->setLength(size)

	int Size();
		m_ptr->getLength();
*/

template <typename T>
class AStack
{
public:
	AStack();
	AStack(Array<T>* ptr, int maxSize = 10);
	~AStack();


	AStack(const AStack<T>& copy);
	AStack(AStack<T>&& move);

	AStack<T>& operator=(const AStack& copy);
	AStack<T>& operator=(AStack&& move);

	void push(T value);
	T pop();
	const T peek();
	int size();
	bool isEmpty();

	bool isFull();
	void setSize(int size);
private:
	Array<T>* m_ptr;
	int m_max;

};

template<typename T>
inline AStack<T>::AStack()
	:m_ptr(new Array<T>()), m_max(10)
{

}

/* Purpose
*	pass an already created array ptr to the CTOR.
* Post
*	Shallow copy; Doesn't set the original reference to nullptr
*/
template<typename T>
inline AStack<T>::AStack(Array<T>* ptr, int maxSize)
	:m_ptr(ptr), m_max(maxSize)
{

}

template<typename T>
inline AStack<T>::~AStack()
{
	delete m_ptr;
	m_ptr = nullptr;
}

/*
Purpose
	copy CTOR
Precondition
	copy must have initialized m_ptr
Postcondition
	initializes a default array, then uses opcopy
*/
template<typename T>
inline AStack<T>::AStack(const AStack<T>& copy)
	:m_max(copy.m_max), m_ptr(nullptr)
{
	if (copy.m_ptr != nullptr)
	{
		m_ptr = new Array<T>();
		*m_ptr = *copy.m_ptr;
	}
	else
	{
		throw Exception("copy or copy.array is empty");
	}
}

/*
Purpose
	Move CTOR
Precondition
	move must have initialized m_ptr
Postcondition
	shallow copy; move.m_ptr set to nullptr
*/
template<typename T>
inline AStack<T>::AStack(AStack<T>&& move)
	:m_ptr(nullptr), m_max(10)
{
	if (move.m_ptr != nullptr)
	{
		m_max = move.m_max;
		m_ptr = move.m_ptr;

		move.m_ptr = nullptr;
		delete move.m_ptr;
	}
	else
	{
		throw Exception("Move or move.array is empty");
	}
}

/*
Purpose
	opcopy
Precondition
	copy can't be self
Postcondition
	m_ptr is deleted, then initialized to a default Array
	Then deep copy
	returns this
*/
template<typename T>
inline AStack<T>& AStack<T>::operator=(const AStack& copy)
{
	if (this->m_ptr == copy.m_ptr)
	{
		throw Exception("Operator=: Can't copy into oneself!");
	}
	else
	{
		delete m_ptr;
		m_ptr = new Array<T>();
		m_ptr->setLength(copy.m_ptr->getLength());

		for (int i = 0; i < m_ptr->getLength(); i++)
		{
			(*m_ptr)[i] = (*copy.m_ptr)[i];
		}

	}

	return *this;
}

/*
Purpose
	opmove
Precondition
	move can't be self
	move cannot be empty
Postcondition
	m_ptr is deleted, then move.m_ptr's address is copied to it
	Shallow copy
	returns this
*/
template<typename T>
inline AStack<T>& AStack<T>::operator=(AStack&& move)
{
	if (this->m_ptr != move.m_ptr)
	{
		if (!move.isEmpty())
		{
			delete m_ptr;

			m_max = move.m_max;
			m_ptr = move.m_ptr;

			move.m_ptr = nullptr;
		}
		else
		{
			throw Exception("Operator=: Move is empty");
		}
	}
	else
	{
		throw Exception("Operator=: Cannot move into onself!");
	}
	return *this;
}

template<typename T>
inline void AStack<T>::push(T value)
{
	if (size() + 1 > m_max)
	{
		throw Exception("Push failed: Stack overflow!");
	}
	else
	{
		m_ptr->push_back(value);
	}

}

template<typename T>
inline T AStack<T>::pop()
{
	if (!isEmpty())
	{
		T temp = (*m_ptr)[m_ptr->getLength() - 1];
		m_ptr->setLength(m_ptr->getLength() - 1);
		return temp;
	}
	else
	{
		throw Exception("Pop failed: Stack underflow!");
	}

}

template<typename T>
const inline T AStack<T>::peek()
{
	if (!isEmpty())
	{
		return (*m_ptr)[m_ptr->getLength() - 1];
	}
	else
	{
		throw Exception("Peek Failed: Stack underflow!");
	}

}


/*Purpose
*	flags true if empty or uninitialized
* Post
*	returns is m_ptr initialized and Size() == 0?
*/
template<typename T>
inline bool AStack<T>::isEmpty()
{
	return ((m_ptr == nullptr) || size() == 0);
}
/* Purpose
*	Flags true if Size() >= m_max
* Post
*	Other functions are expected to manage maximum array size; isFull() only tells you if it's full
*/
template<typename T>
inline bool AStack<T>::isFull()
{
	return size() >= m_max;
}

/* Purpose
*	Adjusts m_max
* Pre
*	size must be greater than 0
* Post
*	Arrays are only updated when information is added or removed from the list by 1 array element
*	If size is bigger than m_max, set m_max to size
*	If size is smaller than m_max, remove the difference, set m_max to size
*/
template<typename T>
inline void AStack<T>::setSize(int size)
{
	if (size < m_max)
	{
		if (size < 1)
		{
			throw Exception("Set size failed: Underflow!");
		}

		m_ptr->setLength(size);
	}
	//else
	m_max = size;
}


/* Purpose
*	returns the current size of the Array
* Pre
*	I believe m_ptr must be initialized with an Array object
*/
template<typename T>
inline int AStack<T>::size()
{
	return m_ptr->getLength();
}
