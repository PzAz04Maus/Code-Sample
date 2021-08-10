/* * * * * * * *
* Stephen Carter
* test LL.cpp
*
* Modified 14APR21
 * * * * * * * */

#include <string>
#include "doctest.h"
#include "exception.h"
#include "linklist.h"

template<class T>
void addOne(T& data);

TEST_CASE("Exception")
{
	Exception except("Test");
	std::wstring testString = except.getMessage();
	testString == L"Test";
	CHECK(testString.compare(L"Test")==0);
}

TEST_CASE("Exception with L"" text")
{
	Exception except(L"Test");

	CHECK(except.getMessage().compare(L"Test") == 0); 
}


// Short testing function to throw an exception
// You may need to add your own functions for testing
void throwException() {
	throw Exception("Test message");
}

TEST_CASE("Throw Exception")
{
	// Standard C++ code to setup the test
	Exception except("Test");

	// Verify the getMessage() method returns the expected value
	// If this is incorrect, the test fails
	std::wstring testString = except.getMessage();

	CHECK(testString == L"Test");

	// Verify the testing function throws an exception of type Exception
	// This is not needed, but used as an example of testing exceptions
	CHECK_THROWS_AS(throwException(), Exception);
}

TEST_CASE("Requirement 1: Functions check")
{
	List<int> listzero = List<int>();

	listzero.append(1);
	listzero.append(2);
	listzero.append(3);
	listzero.append(4);
	listzero.append(5);

	SUBCASE("Move CTOR")
	{
		List<int> listone = std::move(listzero);
		CHECK(listzero.isEmpty());
	}

	SUBCASE("Move empty")
	{
		List<int> listthree;
		List<int> listtwo(std::move(listthree));
	}

	SUBCASE("Can Add members")
	{
		CHECK(listzero.getTail()->getData() == 5);
	}

	SUBCASE("Walking")
	{
		listzero.walkOld();
		CHECK(true);
	}
	SUBCASE("Walking back")
	{
		listzero.walkBackwardsOld();
		CHECK(true);
	}



	SUBCASE("Printing")
	{
		listzero.printForwards();
		CHECK(true);
		listzero.printBackwards();
		CHECK(true);
	}


	SUBCASE("can remove members")
	{
		listzero.extract(5);
		listzero.extract(4);
		listzero.extract(3);
		listzero.extract(2);
		CHECK(listzero.getTail()->getData() == 1);
	}

	SUBCASE("can remove from the middle + can't find missing thing")
	{
		listzero.extract(3);
		CHECK(listzero.find(3) == nullptr);
	}

	SUBCASE("Can add from the beginning")
	{
		listzero.prepend(9);
		CHECK(listzero.getHead()->getData() == 9);
	}

	SUBCASE("Can add in the middle")
	{
		listzero.insertBefore(9, 3);
		listzero.insertAfter(8, 4);

		Node<int>* check = listzero.getHead();

		CHECK(check->getData() == 1);
		check = check->getNext();
		CHECK(check->getData() == 2);
		check = check->getNext();
		CHECK(check->getData() == 9);
		check = check->getNext();
		CHECK(check->getData() == 3);
		check = check->getNext();
		CHECK(check->getData() == 4);
		check = check->getNext();
		CHECK(check->getData() == 8);

	}

	SUBCASE("Purge! isEmpty?")
	{
		listzero.purge();
		CHECK(listzero.isEmpty());

	}
	SUBCASE("Purge and Purge!")
	{
		listzero.purge();
		listzero.purge();
		CHECK(true);
	}

	SUBCASE("Extraction")
	{
		listzero.extract(4);
		Node<int>* check = listzero.getHead();

		CHECK(check->getData() == 1);
		check = check->getNext();
		CHECK(check->getData() == 2);
		check = check->getNext();
		CHECK(check->getData() == 3);
		check = check->getNext();
		CHECK(check->getData() == 5);

		listzero.extract(1);
		listzero.extract(2);
		listzero.extract(3);
		listzero.extract(5);
		CHECK_THROWS_AS(listzero.extract(4), Exception);
	}

	SUBCASE("Move")
	{
		List<int> movetest = List<int>();
		movetest = std::move(listzero);
	}

	SUBCASE("frist")
	{
		Node<int> check = listzero.First();
		CHECK(check.getData() == 1);
	}

	SUBCASE("last")
	{
		Node<int> check = listzero.Last();
		CHECK(check.getData() == 5);
	}


}

TEST_CASE("Requirement 2: Traversal")
{
	List<int> listzero = List<int>();

	listzero.append(1);
	listzero.append(2);
	listzero.append(3);
	listzero.append(4);
	listzero.append(5);

	SUBCASE("Traversing!")
	{
		Node<int>* node = listzero.getHead();
		CHECK(node->getData() == 1);
		node = node->getNext();
		CHECK(node->getData() == 2);
		node = node->getNext();
		CHECK(node->getData() == 3);
		node = node->getNext();
		CHECK(node->getData() == 4);
		node = node->getNext();
		CHECK(node->getData() == 5);
		CHECK(node->getNext() == nullptr);

		node = node->getPrev();
		CHECK(node->getData() == 4);
		node = node->getPrev();
		CHECK(node->getData() == 3);
		node = node->getPrev();
		CHECK(node->getData() == 2);
		node = node->getPrev();
		CHECK(node->getData() == 1);
		CHECK(node->getPrev() == nullptr);


	}
}

TEST_CASE("Exceptions check")
{
	List<int> L = List<int>();

	SUBCASE("empty list")
	{
		CHECK_THROWS_AS(L.First(), Exception);
		CHECK_THROWS_AS(L.Last(), Exception);
		CHECK_THROWS_AS(L.insertAfter(5, 5), Exception);
		CHECK_THROWS_AS(L.insertBefore(5, 5), Exception);
		CHECK_THROWS_AS(L.extract(5), Exception);
	}

	L.append(1);
	L.append(2);
	L.append(3);
	L.append(4);
	L.append(5);

	SUBCASE("populated List")
	{
		CHECK_THROWS_AS(L.extract(20), Exception);
		CHECK_THROWS_AS(L.insertAfter(5, 20), Exception);
		CHECK_THROWS_AS(L.insertBefore(5, 20), Exception);
	}

	SUBCASE("self-referential")
	{
		CHECK_THROWS_AS(L = L, Exception);

	}

}


TEST_CASE("pass a function and a lambda")
{
	List<int> ListA;

	ListA.append(10);
	ListA.append(111);
	ListA.append(42);
	SUBCASE("foreach forwards")
	{
		wcout << "----------\n";
		ListA.printForwards();

		ListA.walk(addOne);
		Node<int>* m_ptr = ListA.getHead();
		CHECK(m_ptr->getData() == 11);
		m_ptr = m_ptr->getNext();
		CHECK(m_ptr->getData() == 112);
		m_ptr = m_ptr->getNext();
		CHECK(m_ptr->getData() == 43);
		wcout << "----------\n";
		ListA.printForwards();
		ListA.walk(
			[](int& data)
			{
				data *= 2;
			});

		m_ptr = ListA.getHead();
		CHECK(m_ptr->getData() == 22);
		m_ptr = m_ptr->getNext();
		CHECK(m_ptr->getData() == 224);
		m_ptr = m_ptr->getNext();
		CHECK(m_ptr->getData() == 86);
		wcout << "----------\n";
		ListA.printForwards();
	}

	SUBCASE("Foreach backwards")
	{
		wcout << "----------\n";
		ListA.printForwards();

		ListA.walkBackwards(addOne);
		Node<int>* m_ptr = ListA.getHead();
		CHECK(m_ptr->getData() == 11);
		m_ptr = m_ptr->getNext();
		CHECK(m_ptr->getData() == 112);
		m_ptr = m_ptr->getNext();
		CHECK(m_ptr->getData() == 43);
		wcout << "----------\n";
		ListA.printForwards();
		ListA.walkBackwards(
			[](int& data)
			{
				data *= 2;
			});

		m_ptr = ListA.getHead();
		CHECK(m_ptr->getData() == 22);
		m_ptr = m_ptr->getNext();
		CHECK(m_ptr->getData() == 224);
		m_ptr = m_ptr->getNext();
		CHECK(m_ptr->getData() == 86);
		wcout << "----------\n";
		ListA.printForwards();
	}

}

template<class T>
void addOne(T& data)
{
	data += 1;
}

