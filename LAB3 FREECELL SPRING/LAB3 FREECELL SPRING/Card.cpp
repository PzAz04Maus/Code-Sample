#pragma once
#include <iostream>
#include <string>


#include "Card.h"


Card::Card()
	:Card(SUIT::EMPTY, RANK::EMPTY)
{

}

Card::Card(SUIT suit, RANK face)
	:m_suit(suit), m_rank(face)
{

}

Card::~Card() {}

Card::Card(const Card& copy)
	:Card(copy.m_suit,copy.m_rank)
{

}

Card& Card::operator=(const Card& copy)
{
	if (&copy != this)
	{
		copyCard(copy.m_suit, copy.m_rank);
	}
	else
	{
		//throw exception?
	}
	return *this;
}

bool Card::operator==(const Card& copy)
{
	bool result = false;
	result = (getSuit() == copy.m_suit) && (getRank() == copy.m_rank);
	return result;
}

SUIT Card::getSuit()
{
	return m_suit;
}

RANK Card::getRank()
{
	return m_rank;
}

void Card::copyCard(SUIT suit, RANK face)
{
	m_suit = suit;
	m_rank = face;
}

void Card::display()
{
	std::wcout << SUITchar[(int)m_suit];
	std::wcout << RANKchar[(int)m_rank];
}
