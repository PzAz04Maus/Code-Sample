#pragma once
/*************
STEPHEN CARTER
EXCEPTION.H
CREATED 10APR21
MODIFIED 25APR21
	Replaced char* with wstring
*************/

#pragma once
#include <iostream>
#include <string>
#include <vector>
using std::ostream;
using std::wstring;


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
		friend function prefacing m_msg to deliver to wcout


*************/
class Exception
{
public:
	//New methods
	Exception(const char* msg);

	//canonicals
	Exception();
	Exception(const wstring msg);
	Exception(Exception& copy);
	Exception(Exception&& move);
	~Exception();
	Exception& operator=(Exception& copy);
	Exception& operator =(Exception&& move);
	const wstring getMessage() const;
	void setMessage(wstring msg);
	friend ostream& operator <<(ostream& stream, const Exception& result);

private:
	wstring m_msg;
};

