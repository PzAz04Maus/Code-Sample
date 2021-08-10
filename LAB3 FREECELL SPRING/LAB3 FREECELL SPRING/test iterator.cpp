/* * * * * * * *
* Stephen Carter
* test iterator.cpp
*
* Created 12APR21
* modified 16APR21
 * * * * * * * */

#include <iostream>
#include "exception.h"
#include "linklist.h"
#include "doctest.h"


TEST_CASE("List iterators")
{
	List<int> list1;

	for (int i = 0; i < 10; i++)
	{
		list1.append(i);
	}

	SUBCASE("1. Make an iterator")
	{

		for (auto i : list1)
		{
			std::wcout << i << std::endl;
		}
		CHECK(true);
	}

	SUBCASE("2. fill an iterator, then test its functions")
	{
		auto first = list1.begin();
		auto last = list1.end();

		CHECK(first != last);
		CHECK(!(first == last));

		for (; first != last; ++first)
		{
			*first = 99;
			std::wcout << *first << std::endl;
		}
		CHECK(true);

		CHECK(first == last);
		CHECK(!(first != last));

		CHECK(*list1.begin() == 99);
	}

	SUBCASE("3. Iterate with append ++")
	{
		auto first = list1.begin();
		auto last = list1.end();


		for (; first != last; first++)
		{
			*first = 99;
			std::wcout << *first << std::endl;
		}
		CHECK(true);
	}
}

TEST_CASE("Reverse Iterator")
{
	List<int> list1;

	for (int i = 0; i < 10; i++)
	{
		list1.append(i);
	}

	SUBCASE("1. traverse an iterator backwards, prepended operator")
	{
		auto first = list1.end();
		auto last = list1.begin();

		for (; first != last; --first)
		{
			std::wcout << *first << std::endl;
		}
		CHECK(true);
	}

	SUBCASE("1. negative traverse, appended operator")
	{
		auto first = list1.end();
		auto last = list1.begin();

		for (; first != last; first--)
		{
			std::wcout << *first << std::endl;
		}
		CHECK(true);
	}
}