/* ************
Stephen Carter
linklist.h
Created 14APR21
First modification
*/

#pragma once
#include "Node.h"
using std::endl;
using std::wcout;


/* Class: iter_ll

Purpose: Handles iterating through class Array

Manager Functions
	iter_ll(T* value)
	iter_ll(iter_ll<T>& copy)
	iter_ll(iter_ll<T>&& move)
	~iter_ll();
		empty
	operator=(const iter_ll<T>&copy)
	operator=(const iter_ll<T>&& move)

Data Members
	T* m_ptr

Methods
	operator*()
	operator==
	operator!=
	operator++()
	operator++(int)
	operator--()
	operator--(int)

*/

template<class T>
class iter_ll
{
public:
	iter_ll(Node<T>* value);
	iter_ll(iter_ll<T>& copy);
	iter_ll(iter_ll<T>&& move);

	~iter_ll();
	iter_ll<T>& operator=(const iter_ll<T>& copy);
	iter_ll<T>& operator=(const iter_ll<T>&& move);



	T& operator*();
	template<class T> friend bool operator==(const iter_ll<T>& left, const iter_ll<T>& right);
	template<class T> friend bool operator!=(const iter_ll<T>& left, const iter_ll<T>& right);

	iter_ll<T>& operator++();
	iter_ll<T> operator++(int);
	iter_ll<T>& operator--();
	iter_ll<T> operator--(int);
private:
	Node<T>* m_ptr;

};

/* List class

Purpose: To manage and interact with a string of nodes

Canonical Functions

	List();
		both m_prev and m_next start as nullptr
	List(const List<T> & copy);
	List(List<T> && move);
	~List();

	List<T>& operator=(const List<T>& rCopy);
	List<T>& operator=(List<T>&& rMove);

Methods

	bool isEmpty();
		if the head pointer is nullptr, return true
	const T& First();
		return the data of the head node
	const T& Last();
		return the data of the tail node
	void prepend(T data);
		add Node(T data) to beginning
	void append(T data);\
		add Node(T data) to end

	void insertAfter(T new_item, T existing_item);
		find existing_item, then insert new_item after
	void insertBefore(T new_item, T existing_item);
		find existing_item, then insert new_item before

	void purge();
		delete all nodes
	void extract(T data);
		delete a Node with T data in it
	Node<T>* find(T data) const;
		return a ptr to the node with T data in it. If no node is found, return nullptr

	Node<T>* getHead();
		if the list is empty, you get a nullptr
	Node<T>* getTail();
		if the list is empty, you get a nullptr

	void printForwards();
		wcout the nodes in sequence, forwards
	void printBackwards();
		wcout the nodes in sequence, backwards


	void walk();
		traverses through the sequence and applies a function(T& data) to the data
	void walkBackwards();
		traverses backwardsthrough the sequence and applies a function(T& data) to the data

	void walkOld();
		a method to traverse through a linked list using a lambda
	void walkBackwardsOld();
		a method to traverse through a linked list using a lambda
*/
template<class T>
class List
{
public:
	List();
	List(const List<T>& copy);
	List(List<T>&& move);

	~List();
	List<T>& operator=(const List<T>& rCopy);
	List<T>& operator=(List<T>&& rMove);

	bool isEmpty();
	const T& First();
	const T& Last();

	void prepend(T data);
	void append(T data);

	void insertAfter(T new_item, T existing_item);
	void insertBefore(T new_item, T existing_item);

	void purge();
	void extract(T data);
	Node<T>* find(T data) const;

	Node<T>* getHead();
	Node<T>* getTail();

	void printForwards();
	void printBackwards();

	void walkOld();
	void walkBackwardsOld();
	void walk(void (*fn)(T& data));
	void walkBackwards(void (*fn)(T& data));

	//forward iter_ll
	friend class iter_ll<T>;

	iter_ll<T> begin();
	iter_ll<T> end();


private:
	Node<T>* m_head;
	Node<T>* m_tail;

};


template<class T>
List<T>::List()
	:m_head(nullptr), m_tail(nullptr)
{

}

template<class T>
List<T>::List(const List<T>& copy)
	:m_head(nullptr), m_tail(nullptr)
{
	Node <T>* copyTravel = copy.m_head;
	Node <T>* copyTrail = nullptr;

	while (copyTravel != nullptr)
	{
		T newData = copyTravel->getData();

		append(newData);

		copyTrail = copyTravel;
		copyTravel = copyTravel->getNext();
	}

}

template<class T>
inline List<T>::List(List<T>&& move)
	:List(move)
{
	move.purge();
}

template<class T>
List<T>::~List()
{
	purge();
}

template<class T>
List<T>& List<T>::operator=(const List<T>& rhs)
{
	if (this != &rhs && rhs.m_head != nullptr)
	{
		if (m_head == nullptr && m_tail == nullptr)
		{
			m_head = m_tail = new Node<T>();
		}

		m_head->setData((rhs.m_head->getData()));

		Node <T>* travel = rhs.m_head->getNext();
		Node <T>* trail = rhs.m_head;

		while (travel != nullptr)
		{
			append((travel->getData()));
			trail = travel;
			travel = travel->getNext();
		}
	}
	else
	{
		throw Exception(L"selfreference or empty source!");
	}
	return *this;
}

template<class T>
inline List<T>& List<T>::operator=(List<T>&& rMove)
{
	if (this != &rMove && rMove.m_head != nullptr)
	{
		if (m_head == nullptr && m_tail == nullptr)
		{
			m_head = m_tail = new Node<T>();
		}

		m_head->setData((rMove.m_head->getData()));

		Node <T>* travel = rMove.m_head->getNext();
		Node <T>* trail = rMove.m_head;

		while (travel != nullptr)
		{
			append((travel->getData()));
			trail = travel;
			travel = travel->getNext();
		}
		rMove.purge();
	}
	else
	{
		throw Exception(L"selfreference or empty source!");
	}
	return *this;
}

template<class T>
bool List<T>::isEmpty()
{
	if (m_head == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
const T& List<T>::First()
{
	T answer{};

	if (!isEmpty())
	{
		answer = m_head->getData();
	}
	else
	{
		throw Exception(L"First not found!");
	}
	return answer;
}

template<class T>
const T& List<T>::Last()
{
	T answer{};

	if (!isEmpty())
	{
		answer = m_tail->getData();
	}
	else
	{
		throw Exception(L"Last not found!");
	}
	return answer;

}

template<class T>
void List<T>::prepend(T data)
{
	Node <T>* newNode = new Node<T>(data);

	newNode->setNext(m_head);
	newNode->setPrev(nullptr);

	if (m_head != nullptr)
	{
		m_head->setPrev(newNode);
	}

	m_head = newNode;
}

template<class T>
void List<T>::append(T data)
{

	Node<T>* newNode = new Node<T>(data);
	if (isEmpty())
	{
		if (m_head != nullptr)
		{
			delete m_head;
		}
		m_head = newNode;
		m_tail = m_head;
	}
	else
	{
		m_tail->setNext(newNode);
		newNode->setPrev(m_tail);
		m_tail = newNode;
	}

}

template<class T>
void List<T>::insertAfter(T new_item, T existing_item)
{
	Node <T>* s_trail = find(existing_item);
	Node <T>* s_travel = nullptr;

	if (s_trail != nullptr)
	{
		s_travel = s_trail->getNext();

		Node<T>* data = new Node<T>(new_item);

		if (s_trail == m_tail)
		{
			m_tail = data;
		}
		else
		{
			s_travel->setPrev(data);
			data->setNext(s_travel);
		}

		s_trail->setNext(data);
		data->setPrev(s_trail);
	}
	else
	{
		throw Exception(L"Item Not Found!");
	}
}

template<class T>
void  List<T>::insertBefore(T new_item, T existing_item)
{
	Node <T>* s_travel = find(existing_item);
	Node <T>* s_trail = nullptr;

	if (s_travel != nullptr)
	{
		s_trail = s_travel->getPrev();

		Node <T>* data = new Node<T>(new_item, s_travel->getPrev(), s_travel->getNext());

		s_travel->setPrev(data);
		data->setNext(s_travel);

		if (s_travel == m_head)
		{
			m_head = data;
		}
		else
		{
			s_trail->setNext(data);
		}
	}
	else
	{
		throw Exception(L"Item not found!");
	}
}


template<class T>
void List<T>::purge()
{
	Node <T>* travel = m_head;
	Node <T>* trail = nullptr;

	while (travel != nullptr)
	{
		trail = travel;
		travel = travel->getNext();
		delete trail;
		trail = nullptr;
	}

	m_head = nullptr;
	m_tail = nullptr;
}

template<class T>
void List<T>::extract(T data)
{
	if (!isEmpty())
	{
		Node <T>* subject = find(data);

		bool changeHead = false;
		bool changeTail = false;

		if (subject != nullptr)
		{
			(subject == m_head ? changeHead = true : false);
			(subject == m_tail ? changeTail = true : false);

			Node <T>* s_Prev = subject->getPrev();
			Node <T>* s_Next = subject->getNext();

			if (changeHead)
			{
				m_head = s_Next;
			}
			else
			{
				s_Prev->setNext(s_Next);
			}

			if (changeTail)
			{
				m_tail = s_Prev;
			}
			else
			{
				s_Next->setPrev(s_Prev);
			}

			delete subject;
		}
		else
		{
			throw Exception(L"File not found!");
		}
	}
	else
	{
		throw Exception(L"Empty List!");
	}

}

template<class T>
Node <T>* List<T>::find(T data) const
{
	Node <T>* target = nullptr;
	Node <T>* copyTravel = m_head;

	while (copyTravel != nullptr && target == nullptr)
	{
		if (copyTravel->getData() == data)
		{
			target = copyTravel;
		}
		else
		{
			copyTravel = copyTravel->getNext();
		}
	}

	return target;
}

template<class T>
inline Node<T>* List<T>::getHead()
{
	return m_head;
}

template<class T>
inline Node<T>* List<T>::getTail()
{
	return m_tail;
}

template<class T>
void List<T>::printForwards()
{
	Node<T>* travel = nullptr;
	travel = m_head;

	T data;

	while (travel != nullptr)
	{
		data = travel->getData();
		wcout << data << " " << endl;
		travel = travel->getNext();
	}
}

template<class T>
void List<T>::printBackwards()
{
	Node<T>* travel = nullptr;

	travel = m_tail;
	T data;
	while (travel != nullptr)
	{
		data = travel->getData();
		wcout << data << " " << endl;
		travel = travel->getPrev();
	}
}

template<class T>
inline void List<T>::walkOld()
{
	auto lambda = [](Node<T>* traverse)
	{
		while (traverse != nullptr)
		{
			wcout << traverse->getData() << " ";
			traverse = traverse->getNext();

		}

	};

	lambda(m_head);

}

template<class T>
inline void List<T>::walkBackwardsOld()
{
	auto lambda = [](Node<T>* traverse)
	{
		while (traverse != nullptr)
		{
			wcout << traverse->getData() << " ";
			traverse = traverse->getPrev();

		}

	};

	lambda(m_tail);
}

template<class T>
inline void List<T>::walk(void(*fn)(T& data))
{
	Node<T>* traverse=getHead();
	while (traverse != nullptr)
	{
		(*fn)(traverse->getData());
		traverse = traverse->getNext();

	}
}

template<class T>
inline void List<T>::walkBackwards(void(*fn)(T& data))
{
	Node<T>* traverse = getTail();
	while (traverse != nullptr)
	{
		(*fn)(traverse->getData());
		traverse = traverse->getPrev();

	}
}

template<class T>
inline iter_ll<T> List<T>::begin()
{
	return iter_ll<T>(m_head);
}

template<class T>
inline iter_ll<T> List<T>::end()
{
	return iter_ll<T>(m_tail);
}

template<class T>
inline iter_ll<T>::iter_ll(Node<T>* value)
	:m_ptr(value)
{

}

template<class T>
inline iter_ll<T>::iter_ll(iter_ll<T>& copy)
	:m_ptr(copy.m_ptr)
{
}

template<class T>
inline iter_ll<T>::iter_ll(iter_ll<T>&& move)
	: m_ptr(move.m_ptr)
{
	move.m_ptr = nullptr;
}

template<class T>
inline iter_ll<T>::~iter_ll()
{
}

template<class T>
inline iter_ll<T>& iter_ll<T>::operator=(const iter_ll<T>& copy)
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
inline iter_ll<T>& iter_ll<T>::operator=(const iter_ll<T>&& move)
{
	if (*this != move)
	{
		m_ptr = move.m_ptr;
		move.m_ptr = nullptr;
	}
	else
	{
		throw Exception(L"Illegal moving of self!");
	}
	return *this;
}

template<class T>
inline T& iter_ll<T>::operator*()
{
	return m_ptr->getData();
}

template<class T>
inline iter_ll<T>& iter_ll<T>::operator++()
{
	m_ptr = m_ptr->getNext();
	return *this;
}

template<class T>
inline iter_ll<T> iter_ll<T>::operator++(int)
{
	iter_ll temp = *this;
	++(*this);
	return temp;
}

template<class T>
inline iter_ll<T>& iter_ll<T>::operator--()
{
	m_ptr = m_ptr->getPrev();
	return *this;
}

template<class T>
inline iter_ll<T> iter_ll<T>::operator--(int)
{
	iter_ll temp = *this;
	--(*this);
	return temp;
}

template<class T>
inline bool operator==(const iter_ll<T>& left, const iter_ll<T>& right)
{
	return left.m_ptr == right.m_ptr;
}
template<class T>
inline bool operator!=(const iter_ll<T>& left, const iter_ll<T>& right)
{
	return left.m_ptr != right.m_ptr;
}
