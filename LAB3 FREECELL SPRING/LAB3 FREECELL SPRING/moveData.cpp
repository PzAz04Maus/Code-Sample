#pragma once
#include <iostream>
#include <string>

#include "moveData.h"

using std::wcout;
using std::cin;

moveData::moveData()
	:moveData(0, 0, 1, 0)
{
}

moveData::moveData(int loc, int addr, int num, int size)
	: m_type(loc), m_index(addr), cardsMoved(num), deckSize(size)
{
	setName(loc);
}

int moveData::inputInt(int min, int max)
{
	int action = min - 1;
	while (action<min || action>max)
	{
		wcout << L" ";
		cin >> action;
	}
	return action;
}

void moveData::setType(int type)
{
	m_type = type;
}

//get the from parameters (name, size)
void moveData::setFromTypePlayer()
{
	wcout << L"Move From \n";
	wcout << L"1) Cells\n";
	wcout << L"2) Foundations\n";
	wcout << L"3) Cascades\n";

	m_type = inputInt(1, 3);

	setName(m_type);
	setSize(m_type);

	wcout << L"Choose which " << m_name << L" to move (1-" << deckSize << ")\n";
	setIndex(inputInt(1, deckSize)-1);
}

//get the to parameters (name, size)
void moveData::setToTypePlayer()
{
	wcout << L" To \n";
	wcout << L"1) Cells\n";
	wcout << L"2) Foundations\n";
	wcout << L"3) Cascades\n";

	m_type = inputInt(1, 3);

	setName(m_type);
	setSize(m_type);

	wcout << L"Choose a " << m_name << L" to send (1-" << deckSize << ")\n";
	setIndex(inputInt(1, deckSize)-1);
}

std::wstring moveData::setName(int action)
{
	switch (action)
	{
	case 1:
		m_name = L"Cell";
		break;
	case 2:
		m_name = L"Foundation";
		break;
	case 3:
		m_name = L"Cascade";
		break;
	default:
		break;
	}
	return m_name;
}

void moveData::setNumMoves(int count)
{
	cardsMoved = count;
}

int moveData::getType()
{
	return m_type;
}

int moveData::getNumMoves()
{
	return cardsMoved;
}

int moveData::getDeckSize()
{
	return deckSize;
}

int moveData::getIndex()
{
	return m_index;
}

void moveData::setSize(int action)
{
	switch (action)
	{
	case 1:		//result = "Cell";
		deckSize = cellCount;
		break;
	case 2:		//result = "Foundation";
		deckSize = foundCount;
		break;
	case 3://result = "Cascade";
		deckSize = cascCount;
		break;
	default:
		deckSize = 0;
		break;
	}
}

void moveData::setIndex(int addr)
{
	m_index = addr;
}
