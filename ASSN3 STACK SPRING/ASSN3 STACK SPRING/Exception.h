#pragma once
/*************
STEPHEN CARTER
EXCEPTION.H
CREATED 1/16/21
*************/

#pragma once
#include <iostream>
using std::ostream;


/* ************
Exception Class
************
Purpose:
	a container that bundles m_msg with management methods to support exception handling

Manager Functions
	Exception()
		default m_msg is nullptr
	Exception(const char* msg)
		uses strcpy for m_msg
	Exception(Exception& copy)
	Exception(Exception&& move)
	~Exception()
	Exception operator =(Exception& copy)
		deletes m_msg, then makes a deep copy
	Exception operator =(Exception&& move)
		deletes m_msg, shallow copies address of move.m_msg, then sets move.m_msg to nullptr

Methods
	getMessage()
	setMessage()
	friend operator <<(ostream& stream, const Exception& result)
		friend function prefacing m_msg to deliver to cout


*************/
class Exception
{
public:
	Exception();
	Exception(const char* msg);
	Exception(Exception& copy);
	Exception(Exception&& move);
	~Exception();
	Exception& operator=(Exception& copy);
	Exception& operator =(Exception&& move);
	const char* getMessage() const;
	void setMessage(const char* msg);
	friend ostream& operator <<(ostream& stream, const Exception& result);

private:
	char* m_msg;
};

