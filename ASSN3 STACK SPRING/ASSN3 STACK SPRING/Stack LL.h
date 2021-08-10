/* ************
Stephen Carter
template<class T>
Stack LL.h
Created 20APR21
First modification
*/

#pragma once
#include "linklist.h"

/* LStack class

Purpose: To manage a linked list as a stack

Canonical Functions
	LStack();
		m_ptr initialized to a default list with 0 nodes

	LStack(List<T>* ptr, int size);
		m_ptr is pointed to an already made list with the size manually given
	~LStack();
		purge m_ptr, then delete the object

	LStack(const LStack<T>& copy);
		temp initialized as a new empty list for a deep copy, then traverses through copy.m_ptr
	LStack(LStack<T>&& move);
		move is set to nullptr

	LStack<T>& operator=(const LStack& copy);
		m_ptr deleted
	LStack<T>& operator=(LStack&& move);
		m_ptr deleted
		move.m_ptr set to nullptr

Methods

	void Push(T value);
		append(value)
	T Pop();
		take m_ptr's tail and extract it after passing the details by value
	T Peek();
		getData()
	int Size();
		returns m_size as count
	bool isEmpty();
		is m_ptr uninitialized or isEmpty()?
*/

template <class T>
class LStack
{
public:
	LStack();
	LStack(List<T>* ptr, int size);
	~LStack();

	LStack(const LStack<T>& copy);
	LStack(LStack<T>&& move);

	LStack<T>& operator=(const LStack& copy);
	LStack<T>& operator=(LStack&& move);

	void push(T value);
	T pop();
	T peek();
	int size();
	bool isEmpty();

private:
	List<T>* m_ptr;
	int m_size;
};

template<class T>
inline LStack<T>::LStack()
	:m_ptr(new List<T>()), m_size(0)
{

}

/* Purpose
*	pass an already created list ptr to the CTOR.
* Post
*	Shallow copy; Doesn't set the original reference to nullptr
*/
template<class T>
inline LStack<T>::LStack(List<T>* ptr, int size)
	:m_ptr(ptr), m_size(size)
{

}

template<class T>
inline LStack<T>::~LStack()
{
	if (!isEmpty())
	{
		m_ptr->purge();
		m_size = 0;
	}
	delete m_ptr;
}

/*
Purpose
	copy CTOR
Precondition
	copy must have initialized m_ptr
Postcondition
	deep copy using append and getNext() to an initialized list
*/
template<class T>
inline LStack<T>::LStack(const LStack<T>& copy)
	:m_size(copy.m_size)
{
	if (copy.m_ptr != nullptr)
	{
		Node<T>* temp = copy.m_ptr->getHead();

		m_ptr = new List<T>();
		while (temp != nullptr)
		{
			m_ptr->append(temp->getData());
			temp = temp->getNext();
		}
	}
	else
	{
		throw Exception("Copy CTOR Failure: copy was uninitialized or empty");
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
template<class T>
inline LStack<T>::LStack(LStack<T>&& move)
{
	if (move.m_ptr != nullptr)
	{
		m_ptr = move.m_ptr;
		m_size = move.m_size;

		move.m_ptr = nullptr;
		move.m_size = 0;
	}
	else
	{
		throw Exception("move CTOR failure: move was uninitialized or empty");
	}
}

/*
Purpose
	opcopy
Precondition
	can't be self
Postcondition
	m_ptr is deleted, initialized to a default List, then deep copy onto it
	returns this
*/
template<class T>
inline LStack<T>& LStack<T>::operator=(const LStack& copy)
{
	if (this->m_ptr!= copy.m_ptr)
	{
		delete m_ptr;


		m_ptr = new List<T>();
		Node<T>* temp = copy.m_ptr->getHead();


		while (temp != nullptr)
		{
			m_ptr->append(temp->getData());
			temp = temp->getNext();
		}


		m_size = copy.m_size;
	}
	else
	{
		throw Exception("Operator=: Can't copy into oneself!");
	}
	return *this;
}

/*
Purpose
	opmove
Precondition
	m_ptr can't be self
Postcondition
	m_ptr is deleted, then move.m_ptr's address is copied to it
	Shallow copy
	returns this
*/
template<class T>
inline LStack<T>& LStack<T>::operator=(LStack&& move)
{
	if (this->m_ptr != move.m_ptr && (!move.isEmpty()))
	{
		delete m_ptr;


		m_ptr = move.m_ptr;
		m_size = move.m_size;


		move.m_ptr = nullptr;
		move.m_size = 0;

	}
	else
	{
		throw Exception("Operator=: Can't move into oneself!");
	}
	return *this;
}

template<class T>
inline void LStack<T>::push(T value)
{
	m_ptr->append(value);
	m_size++;
}

template<class T>
inline T LStack<T>::pop()
{
	if (!isEmpty())
	{
		T temp = m_ptr->getTail()->getData();
		m_ptr->extract(m_ptr->getTail()->getData());
		m_size--;
		return temp;
	}
	else
	{
		throw Exception("Pop underflow: Stack is Empty!");
	}

}
/* Post
*	return tail data by value
*/
template<class T>
inline T LStack<T>::peek()
{
	if (!isEmpty())
	{
		return m_ptr->getTail()->getData();
	}
	else
	{
		throw Exception("Peek underflow: Stack is Empty!");
	}

}

/* Purpose
*	returns the current size of the List according to Stack
*/
template<class T>
inline int LStack<T>::size()
{
	return m_size;
}

/* Purpose
*	Flags true if m_ptr is uninitialized or isEmpty()
* Post
*	If m_ptr doesn't ptr to a list, return true
*	else, return isEmpty();
*/
template<class T>
inline bool LStack<T>::isEmpty()
{
	if (m_ptr != nullptr)
	{
		return m_ptr->isEmpty();
	}
	else
	{
		return true;
	}
	
}

