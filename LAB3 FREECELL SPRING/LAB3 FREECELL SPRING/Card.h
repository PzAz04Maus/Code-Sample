/* ************
Stephen Carter
Card.h
Created 20APR21
*/
#pragma once
#include <string>

enum class SUIT { SPADE, CLUB, DIAMOND, HEART, EMPTY };

enum class RANK { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, EMPTY };

static std::wstring RANKchar[]{ L"A",L"2",L"3",L"4",L"5",L"6",L"7",L"8",L"9",L"10",L"J",L"Q",L"K",L" " };

static wchar_t SUITchar[]{ 0x2660,0x2663,0x2666,0x2665,' ' };

/* Class: Card
Purpose:
	containers that act as the individual card objects

Data Members:
	m_suit
	m_rank

Canonical Functions:
	Card(SUIT suit, RANK face);
	Card();
		Uses the full constructor to initialize an empty card with no rank or suit
	~Card();
		Card is a static object.
	Card(const Card& copy);
	Card& operator=(const Card& copy);
	bool operator==(const Card& cmp);
		

Methods:
	getSuit
	getRank
	display
		uses RANKchar and SUITchar arrays to display the card's value to console.
		SUIT and RANK correlate to a string counterpart, which then is cast to int to select the right character

	copyCard
		support function for op=copy

*/

class Card
{
public:
	Card();
	Card(SUIT suit, RANK face);
	~Card();
	Card(const Card& copy);
	Card& operator=(const Card& copy);
	bool operator==(const Card& cmp);

	SUIT getSuit();
	RANK getRank();

	void copyCard(SUIT suit, RANK face);
	void display();


private:
	SUIT m_suit;
	RANK m_rank;
};