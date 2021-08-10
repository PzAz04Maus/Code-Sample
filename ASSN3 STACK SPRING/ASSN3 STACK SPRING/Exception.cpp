/*************
STEPHEN CARTER
EXCEPTION.CPP
CREATED 1/16/21
*************/

#pragma once
#include "Exception.h"

/* ************
Operator <<
************
Delivers error message and m_msg in a stream object(?)
*************/
ostream& operator <<(ostream& stream, const Exception& result)
{
	stream << "Error Message:\t";
	stream << result.getMessage()<< std::endl;

	return stream;
}
/* ************
Default CTOR
************
Initializes a null string
*************/
Exception::Exception()
	:m_msg(nullptr)
{

}
/* ************
CTOR
************
Initializes a string container and populates it with msg
*************/
Exception::Exception(const char* msg)
	:Exception()
{
	m_msg = new char[strlen(msg) + 1];
	strcpy(m_msg, msg);
}
/* ************
Copy CTOR
************
Calls the normal CTOR by passing copy.m_msg
*************/
Exception::Exception(Exception& copy)
	:Exception(copy.m_msg)
{

}
/* ************
Move CTOR
************
Initializes a default CTOR, then assigns the address of move.m_msg to the initialized object
*************/
Exception::Exception(Exception&& move)
	:Exception()
{
	m_msg = move.m_msg;
	move.m_msg = nullptr;

}
/* ************
DTOR
************
deletes the dynamic array m_msg and sets it to null
*************/
Exception::~Exception()
{
	delete[]m_msg;
	m_msg = nullptr;
}
/* ************
Copy Operator=
************
Copies over the array copy.m_msg to this object after deallocating the original m_msg

Object cannot copy itself

deep copy is stored in m_msg. The whole object is returned as *this
*************/
Exception& Exception::operator=(Exception& copy)
{
	if (this != &copy)
	{
		delete[]m_msg;
		m_msg = new char[strlen(copy.m_msg) + 1];
		strcpy(m_msg, copy.m_msg);
	}
	return *this;
}
/* ************
Move Operator=
************
Copies the address copy.m_msg to this object, then sets copy.m_msg to nullptr

Object cannot move itself

m_msg is emptied of any contents, then assigned the address of copy.m_msg
*************/
Exception& Exception::operator =(Exception&& move)
{
	if (this != &move)
	{
		delete[]m_msg;
		m_msg = move.m_msg;
		move.m_msg = nullptr;
	}
	return *this;
}
const char* Exception::getMessage() const
{
	return m_msg;
}
/* ************
setMessage
************
sets message to an arbitrary string

must be a valid string

msg can either be set to nullptr or is passed a string that it deep copies
*************/
void Exception::setMessage(const char* msg)
{
	if (msg == nullptr)
	{
		delete[]m_msg;
		m_msg = nullptr;
	}

	if (msg != m_msg)
	{
		delete[]m_msg;

		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
}

