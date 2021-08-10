/* ************
Stephen Carter
Node.h
Created 14APR21
First modification
*/

#pragma once
#include "Exception.h"
#include "Card.h"

/* Node class

Purpose: containers for the list's data

Canonical Functions
	Node()
		3 argument CTOR(0,nullptr,nullptr)
	Node(T data)
		3 argument CTOR (data,nullptr,nullptr)
	Node (T data, Node<T>* next, Node<T>* prev)

	Node(const Node<T>&copy)
		3 argument CTOR(copy,copy,copy)
	Node<Node<T>&& move)
		3 argument CTOR(move,move,move)
		clears move to 0, nullptr, nullptr
	~Node()

	Node<T>& operator=(const Node<T>&rCopy)
	Node<T>& operator=(Node<T>&& rMove)
		clears rMove after set, no dtor

Methods
	getData()
	setData(T data)
	getNext()
	setNext(Node<T>*ptr)
	getPrev()
	setPrev(Node<T>*ptr)

*/
template<class T>
class Node
{
public:
	Node();
	Node(T data);
	Node(T data, Node<T>* next, Node<T>* prev);

	Node(const Node<T>& copy);
	Node(Node<T>&& move);
	~Node();

	Node<T>& operator=(const Node<T>& rCopy);
	Node<T>& operator=(Node<T>&& rMove);

	T& getData();
	void setData(T data);
	Node<T>* getNext();
	void setNext(Node<T>*ptr);
	Node<T>* getPrev();
	void setPrev(Node<T>*ptr);

private:
	T m_data;

	Node<T>* m_next;
	Node<T>* m_prev;
}; 

template<class T>
Node<T>::Node()
	:Node(0,nullptr,nullptr)
{

}

template<class T>
Node<T>::Node(T data, Node<T>* next, Node<T>* prev)
	:m_data(data),m_next(next),m_prev(prev)
{

}

template<class T>
inline Node<T>::Node(const Node<T>& copy)
	:Node(copy->m_data,copy->m_next,copy->m_prev)
{

}

template<class T>
inline Node<T>::Node(Node<T>&& move)
	:Node(move->m_data, move->m_next, move->m_prev)
{
	move->setData(0);
	move->setNext(nullptr);
	move->setPrev(nullptr);
}

template<class T>
Node<T>::Node(T data)
	:Node(data,nullptr,nullptr)
{

}

template<class T>
Node<T>::~Node()
{
	m_data = 0x00;
	m_prev = nullptr;
	m_next = nullptr;
}

template<>
inline Node<Card>::~Node()
{
	m_data = Card();
	m_prev = nullptr;
	m_next = nullptr;
}

template<class T>
Node<T>& Node<T>::operator=(const Node<T>& rCopy)
{
	if (this != &rCopy)
	{
		setData(rCopy->m_data);
		setNext(rCopy->m_next);
		setPrev(rCopy->m_prev);
	}
	return *this;
}

template<class T>
Node<T>& Node<T>::operator=(Node<T>&& rMove)
{
	if (this != &rMove)
	{

		setData(rMove->m_data);
		setNext(rMove->m_next);
		setPrev(rMove->m_prev);

		rMove->setData({});//does this work?
		rMove->setNext(nullptr);
		rMove->setPrev(nullptr);
	}
	return *this;
}

template<class T>
T& Node<T>::getData()
{
	return m_data;
}

template<class T>
void Node<T>::setData(T data)
{
	m_data = data;
}


template<class T>
Node<T>* Node<T>::getNext()
{
		return m_next;	
}

template<class T>
void Node<T>::setNext(Node<T>* ptr)
{
	m_next = ptr;
}


template<class T>
Node<T>* Node<T>::getPrev()
{
		return m_prev;
}

template<class T>
void Node<T>::setPrev(Node<T>* ptr)
{
	m_prev = ptr;
}

