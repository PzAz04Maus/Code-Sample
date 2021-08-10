/* * * * * * * *
* Stephen Carter
* test.cpp
*
* Created 12APR21
* No modifications
 * * * * * * * */

#include <iostream>
#include "exception.h"
#include "Array.h"
#include "doctest.h"


TEST_CASE("Array iterators")
{
	Array<int> array1(10);
	SUBCASE("1. Make an iterator")
	{
		int j = 0;
		for (auto i : array1)
		{
			std::cout << i << std::endl;
		}
		CHECK(true);
	}

	SUBCASE("2. fill an iterator, then test its functions")
	{
		auto first = array1.begin();
		auto last = array1.end();

		CHECK(first != last);
		CHECK(!(first == last));

		for (; first != last; ++first)
		{
			*first = 99;
			std::cout << *first << std::endl;
		}
		CHECK(true);

		CHECK(first == last);
		CHECK(!(first != last));

		CHECK(*array1.begin() == 99);
	}
}

TEST_CASE("Push and Pop")
{
	Array<int> array1(10);
	int j = 10;

	for (int i = 0; i < array1.getLength(); i++)
	{
		array1[i] = j * i;
	}

	for (auto i : array1)
	{
		std::cout << i << std::endl;
	}

	for (int i = 0; i < array1.getLength(); i++)
	{
		std::cout << array1[i] << std::endl;
	}

	array1.push_back(11);
	CHECK(array1[10] == 11);

	array1.pop_back();
	CHECK(array1.getLength() == 10);

	int test = array1.pop_return();

	CHECK(test == 90);
}