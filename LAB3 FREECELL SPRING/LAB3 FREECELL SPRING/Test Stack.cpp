/* * * * * * * *
* Stephen Carter
* testStack.cpp
*
* Created 23APR21
* No modifications
 * * * * * * * */

#include "doctest.h"
#include "Stack A.h"
#include "Stack LL.h"


TEST_CASE("Requirement 0: Main must boot")
{
	CHECK(true);
}

TEST_CASE("Requirement 1: Array Stack Management")
{
	AStack<int>* newStack = new AStack<int>();

	newStack->push(1);
	CHECK(newStack->peek() == 1);
	newStack->push(2);
	CHECK(newStack->peek() == 2);
	newStack->push(3);
	CHECK(newStack->peek() == 3);
	newStack->push(4);
	CHECK(newStack->peek() == 4);

	CHECK(newStack->pop() == 4);
	CHECK(newStack->pop() == 3);
	CHECK(newStack->pop() == 2);
	CHECK(newStack->pop() == 1);
	CHECK_THROWS_AS(newStack->pop(), Exception);
	CHECK_THROWS_AS(newStack->peek(), Exception);

	delete newStack;
}

TEST_CASE("Requirement 2: Array Stack Movement")
{
	AStack<int>* Stack1 = new AStack<int>();
	AStack<int>* Stack2 = new AStack<int>(new Array<int>);
	CHECK(Stack1->isEmpty());
	Stack1->push(1);
	Stack1->push(2);
	CHECK(!Stack1->isEmpty());

	CHECK(Stack2->isEmpty());
	Stack2->push(3);
	Stack2->push(4);
	CHECK(!Stack2->isEmpty());

	delete Stack1;
	delete Stack2;
}

TEST_CASE("List Stack copy, copy ctor, and movement")
{
	LStack<int>* Stack1 = new LStack<int>();
	Stack1->push(10);

	LStack<int>* Stack2 = new LStack<int>(*Stack1);				//Copy CTOR
	LStack<int>* Stack3 = new LStack<int>(std::move(*Stack1));	//Move CTOR

	CHECK(Stack2->peek() == 10);	//Stack1 copied
	CHECK(Stack3->peek() == 10);	//Stack1 moved
	CHECK(Stack1->isEmpty());		//Stack1 gone

	LStack<int>* Stack4 = new LStack<int>();
	LStack<int>* Stack5 = new LStack<int>();
	LStack<int>* Stack6 = new LStack<int>();

	Stack4->push(11);
	Stack5->push(22);
	Stack6->push(33);

	*Stack4 = *Stack5;				//Stack4 op= copy
	*Stack5 = std::move(*Stack6);	//Stack5 op= move

	CHECK(Stack4->peek() == 22);	//4 is 5
	CHECK(Stack5->peek() == 33);	//5 is 6
	CHECK(Stack6->isEmpty());		//6 is empty


	delete Stack1;
	delete Stack2;
	delete Stack3;
	delete Stack4;
	delete Stack5;
	delete Stack6;
}

TEST_CASE("List Stack copy, copy ctor, and movement")
{
	AStack<int>& Stack1 = *new AStack<int>();
	Stack1.push(10);
	AStack<int>* Stack2 = new AStack<int>(Stack1);				//copy CTOR
	AStack<int>* Stack3 = new AStack<int>(std::move(Stack1));	//Move CTOR

	CHECK(Stack1.isEmpty());
	CHECK(Stack2->peek() == 10);
	CHECK(Stack3->peek() == 10);

	AStack<int>& Stack4 = *new AStack<int>();
	AStack<int>& Stack5 = *new AStack<int>();
	AStack<int>& Stack6 = *new AStack<int>();

	Stack4.push(20);
	Stack5.push(30);
	Stack6.push(40);

	Stack4 = Stack5;			//Stack4 op= copy
	Stack5 = std::move(Stack6); //Stack5 op= move 

	CHECK(Stack4.peek() == 30); //4 is 5
	CHECK(Stack5.peek() == 40); //5 is 6
	CHECK(Stack6.isEmpty());	//6 is empty


	delete& Stack1;
	delete Stack2;
	delete Stack3;
	delete& Stack4;
	delete& Stack5;
	delete& Stack6;
}



TEST_CASE("Requirement 2: Array Overflow management")
{
	AStack<int>* newStack = new AStack<int>();

	CHECK(newStack->isEmpty());

	newStack->push(1);
	newStack->push(2);
	newStack->push(3);
	newStack->push(4);
	newStack->push(5);
	newStack->push(6);
	newStack->push(7);
	newStack->push(8);
	newStack->push(9);

	CHECK(newStack->getSize() == 9);

	CHECK(!newStack->isEmpty());

	newStack->push(0);

	CHECK_THROWS_AS(newStack->push(-1), Exception);
	CHECK(newStack->isFull());

	CHECK_THROWS_AS(newStack->setSize(-1), Exception);

	newStack->setSize(11);
	CHECK(!newStack->isFull());

	newStack->push(-1);
	CHECK(newStack->isFull());


	delete newStack;
}

TEST_CASE("Requirement 1: Linked List Stack Management")
{
	LStack<int>* newStack = new LStack<int>();
	CHECK(newStack->isEmpty());
	CHECK_THROWS_AS(newStack->pop(), Exception);
	CHECK_THROWS_AS(newStack->peek(), Exception);

	newStack->push(1);
	newStack->push(2);
	newStack->push(3);
	newStack->push(4);
	newStack->push(5);
	newStack->push(6);
	newStack->push(7);
	newStack->push(8);
	newStack->push(9);

	CHECK(newStack->peek() == 9);
	CHECK(newStack->pop() == 9);
	CHECK(newStack->pop() == 8);
	CHECK(newStack->getSize() == 7);

	delete newStack;
}
