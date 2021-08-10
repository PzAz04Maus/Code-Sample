/* * * * * * * *
* Stephen Carter
* test game.cpp
*
* Created 12APR21
* modified 23APR21
 * * * * * * * */
#pragma once
#include <io.h>
#include <fcntl.h>
#include <cstdio>
#include "doctest.h"

#include <iostream>
#include <string>
#include "Stack A.h"
#include "Stack LL.h"


#include "Card.h"
#include "Deck.h"
#include "Game.h"

#include <crtdbg.h>

using std::wcout;
using std::endl;


template <typename T> class AStack;
class Deck;

TEST_CASE("Foundation test")
{
	Foundation<Card>* testFound = new Foundation<Card>();
	Card* testCard = new Card(SUIT::SPADE, RANK::ACE);

	testFound->pushRule(*testCard);
	testFound->pushRule(Card(SUIT::SPADE, RANK::TWO));
	testFound->pushRule(Card(SUIT::SPADE, RANK::FIVE));

	Card takeCard = testFound->popRule();
	testCard->display();
	testFound->pushRule(*testCard);
	testFound->checkWin();

	delete testFound;
	delete testCard;
	CHECK(true);
}

TEST_CASE("Tableau Test")
{

	Tableau<Card>* testTab = new Tableau<Card>();

	testTab->getSize();

	testTab->push(Card(SUIT::SPADE, RANK::KING));
	testTab->push(Card(SUIT::SPADE, RANK::KING));
	testTab->push(Card(SUIT::SPADE, RANK::KING));
	testTab->pushQuery(Card(SUIT::HEART, RANK::QUEEN));
	testTab->pushQuery(Card(SUIT::SPADE, RANK::QUEEN));

	testTab->pushRule(Card(SUIT::SPADE, RANK::QUEEN));
	testTab->pushRule(Card(SUIT::HEART, RANK::QUEEN));
	testTab->pushQuery(Card(SUIT::HEART, RANK::TEN));
	testTab->pushRule(Card(SUIT::HEART, RANK::TEN));
	testTab->pushRule(Card(SUIT::HEART, RANK::JACK));
	testTab->pushRule(Card(SUIT::CLUB, RANK::JACK));

	testTab->getHead();
	testTab->getSize();
	testTab->isEmpty();
	testTab->peek();
	Array<Card>* memCheck = testTab->peekAll();
	testTab->pop();

	delete testTab;
	delete memCheck;
	CHECK(true);
}

TEST_CASE("Deck Test")
{

	Deck* t_deck = new Deck();

	t_deck->buildNewDeck();
	t_deck->displayAllCascades();
	t_deck->shuffleDeck();
	t_deck->dealCards();

	//int move = t_deck->getN_move();
	//t_deck->getVictoryCondition();

	delete t_deck;
	CHECK(true);
}

TEST_CASE("Array Test")
{
	Array<int>* newarray = new Array<int>;
	newarray->push_back(1);
	newarray->extractElement(0);
	newarray->push_back(1);
	newarray->pop_back();
	newarray->push_back(1);
	newarray->getLength();
	delete newarray;
	CHECK(true);
}

