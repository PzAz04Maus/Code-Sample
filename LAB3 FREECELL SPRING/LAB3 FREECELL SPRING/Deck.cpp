#pragma once
#include "Stack A.h"
#include "Stack LL.h"
#include <cmath>


#include "Card.h"
#include "Deck.h"

enum class deckType { EMPTY, CELL, FOUND, CASC };

Deck::Deck()
	:openCell(new Array<Card>())
	, foundation(new Array<Foundation<Card>*>)
	, cascade(nullptr)
	, startingDeck(new Array<Card>())
	, n_move(1)
{

	//there's gotta be a way to simplify this into a single function. But how?
	for (int i = 0; i < foundCount; i++)
	{
		Foundation<Card>* temp = new Foundation<Card>();
		foundation->push_back(temp);
	}


	cascade = new Array<Tableau<Card>*>;
	for (int i = 0; i < cascCount; i++)
	{
		Tableau<Card>* temp = new Tableau<Card>();
		cascade->push_back(temp);
	}

}

Deck::~Deck()
{

	delete openCell;
	openCell = nullptr;
	for (int i = 0; i < foundCount; i++)
	{
		Foundation<Card>* temp = foundation->pop_return();
		delete temp;
	}
	delete foundation;
	foundation = nullptr;

	for (int i = 0; i < cascCount; i++)
	{
		Tableau<Card>* temp = cascade->pop_return();
		delete temp;
	}
	delete cascade;
	cascade = nullptr;
	delete startingDeck;
	startingDeck = nullptr;
}


void Deck::buildNewDeck()
{
	for (int s = 0; s < 4; s++)
	{
		for (int r = 0; r < 13; r++)
		{
			startingDeck->push_back(Card((SUIT)s, (RANK)r));
		}
	}
}


void Deck::shuffleDeck()
{
	int RNG1 = 0;
	int RNG2 = 0;
	for (int i = 0; i < 52; i++)
	{
		RNG1 = RNG(52);
		RNG2 = RNG(52);
		if (RNG1 != RNG2)
		{
			Card temp_1 = (*startingDeck)[RNG1];
			Card temp_2 = (*startingDeck)[RNG2];
			(*startingDeck)[RNG1].copyCard(temp_2.getSuit(), temp_2.getRank());
			(*startingDeck)[RNG2].copyCard(temp_1.getSuit(), temp_1.getRank());
		}

	}
}

void Deck::dealCards()
{
	for (int i = 0; i < 4; i++)
	{
		dealCascade(7, i);
	}

	for (int i = 4; i < 8; i++)
	{
		dealCascade(6, i);
	}
}

void Deck::dealCascade(int num, int address)
{

	Card temp;
	for (int i = 0; i < num; i++)
	{
		if (startingDeck->getLength() != 0)
		{
			temp = startingDeck->pop_return();
			Tableau<Card>* tempDeck = (*cascade)[address];
			tempDeck->push(temp);
		}
		else
		{
			throw Exception(L"Prematurely Ran out of Cards!");
		}

	}
}

bool Deck::moveDestLogic(Array<Card>* temp, moveData * to, int numMove, int* err_i)
{
	int to_i = to->getIndex();

	bool result = false;
	switch ((deckType)to->getType())
	{
	case deckType::EMPTY:
		break;
	case deckType::CELL:
		//check nummove, and if empty
		if (openCell->getLength() < 4)
		{
			result = true;
			openCell->push_back(temp->pop_return());
		}
		else
		{
			*err_i = 1;
		}
		break;
	case deckType::FOUND:
		if ((*foundation).operator[](to_i)->isEmpty() && temp->peek().getRank() == RANK::ACE)
		{
			result = (*foundation).operator[](to_i)->pushRule(temp->peek());
		}
		else
		{
			if (!(*foundation).operator[](to_i)->isEmpty())
			{
				result = (*foundation).operator[](to_i)->pushRule(temp->peek());
				if (result == false)
				{
					*err_i = 1;
				}
				else
				{
					temp->pop_back();
				}
			}
			else
			{
				*err_i = 1;
			}

		}
		break;
	case deckType::CASC:
		//Okay now we gotta shit x cards here but first we gotta check if we can do that but then we can only do this to cascades but if ...
		//requiescat in pace, Maus. He sighed too much.

		if (isCascEmpty(to_i))
		{
			result = true;
			for (int i = 0; i < numMove; i++)
			{
				pushCascade(to_i, temp->pop_return());
			}

		}
		else
		{
			if (pushCascadeQuery(to_i, temp->peek()))
			{
				for (int i = 0; i < numMove; i++)
				{
					//stop from moving an illegal set
					if ((*cascade)[to_i]->pushQuery(temp->peek()))
					{
						result = (*cascade)[to_i]->pushRule((temp->pop_return()));
					}
					else
					{
						*err_i = i;
						i = numMove;
						result = false;
					}
				}
			}
			break;
	default:
		break;
		}
	}

	return result;

}
void Deck::moveCleanup(bool result, Array<Card>* temp, moveData * from, moveData * to, int numMove, int err_i)
{
	//successful result
	if (result == true)
	{

		switch ((deckType)from->getType())
		{
		case deckType::CELL://cell
			extractCell(from->getIndex());
			break;
		case deckType::FOUND://foundation
			popFoundation(from->getIndex());
			break;
		default:
			break;
		}
	}
	else
	{//failed result
		switch ((deckType)from->getType())
		{
		case deckType::CELL:
			wcout << "Cell move failed\n";
			for (int i = 0; i < err_i; i++)
			{
				openCell->push_back(temp->pop_return());
			}
			break;
		case deckType::FOUND:
			wcout << "Foundation move failed\n";
			for (int i = 0; i < err_i; i++)
			{
				foundation->operator[](from->getIndex())->push(temp->pop_return());
			}
			break;
		case deckType::CASC:
			//push casc back
			wcout << "Cascade move failed\n";
			if ((deckType)to->getType() == deckType::CASC)
			{

				for (int i = 0; i < err_i; i++)
				{
					pushCascade(from->getIndex(), popCascade(to->getIndex()));
				}
				if ((deckType)to->getType() == deckType::CASC)
				{
					for (int i = 0; i < numMove - err_i; i++)
					{
						pushCascade(from->getIndex(), temp->pop_return());
					}

				}
			}
			else
			{
				if (!cascade->operator[](from->getIndex())->isEmpty())
				{
					pushCascade(from->getIndex(), temp->pop_return());
				}
			}
			//push temp back

			break;
		default:
			break;
		}
	}

}

//from determines which object we pop from
//to determines which object we push to
//i_from determines where in the object we pop from
//i_to determines where in the object we push to
bool Deck::moveCardLogic(moveData from, moveData to, int numMove)
{
	bool result = false;
	Array<Card>* temp = new Array<Card>();
	int err_i = 0;

	if (!(from.getType() == to.getType() && from.getIndex() == to.getIndex()))
	{
		moveSrcLogic(temp, &from, &to, numMove, err_i);
		result = moveDestLogic(temp, &to, numMove, &err_i);
		moveCleanup(result, temp, &from, &to, numMove, err_i);
	}
	else
	{
		std::wcout << L"self assign not allowed.\n";
	}

	delete temp;
	return result;
}

void Deck::moveSrcLogic(Array<Card>* temp, moveData * from, moveData * to, int numMove, int err_i)
{
	int from_i = from->getIndex();

	switch ((deckType)from->getType())
	{
	case deckType::CELL:
		//needs to be a specific cell
		if (openCell->isEmpty()==false)
		{
			temp->push_back(peekCell(from_i));
			checkEmpty(temp, *to, L"Empty Cell\n");
			//if (temp->peek() == Card())
			//{
			//	std::wcout << L"Empty Cell";
			//	to.setType((int)deckType::EMPTY);//end prematurely
			//}
		}
		else
		{
			to->setType((int)deckType::EMPTY);
		}

		break;
	case deckType::FOUND:
		if (!foundation->isEmpty())
		{
			temp->push_back(peekFoundation(from_i));
			checkEmpty(temp, *to, L"Empty Foundation\n");
		}
		else
		{
			to->setType((int)deckType::EMPTY);
		}
		break;
	case deckType::CASC:
		if (!cascade->operator[](from->getIndex())->isEmpty())
		{
			for (int i = 0; i < numMove; i++)
			{
				Card tempCasc = peekCascade(from_i);
				//we have to dig to the next element

				if (tempCasc == Card())//bad data, we end the loop
				{
					std::wcout << L"Cascade not big enough (i stopped at " << i << ")";
					err_i = i;
					i = numMove;
					to->setType((int)deckType::EMPTY);
				}
				else
				{
					popCascade(from_i);
					temp->push_back(tempCasc);
				}
			}
		}
		else
		{
			to->setType((int)deckType::EMPTY);
		}
		break;
	default:
		//set dest to empty?
		break;
	}
}

void Deck::checkEmpty(Array<Card>* temp, moveData & input, const wchar_t* msg)
{
	if (temp->peek() == Card())
	{
		std::wcout << msg;
		input.setType((int)deckType::EMPTY);
	}
}

void Deck::extractCell(int i)
{
	openCell->extractElement(i);
}

Card Deck::peekCell(int i)
{
	Card temp;
	if (openCell->checkIndexEmpty(i) == false)
	{
		temp = (*openCell)[i];
	}
	return temp;
}

Card Deck::peekFoundation(int i)
{
	Card temp;
	if (foundation->checkIndexEmpty(i) == false)
	{
		Card temp2 = (*foundation)[i]->peek();
		temp.copyCard(temp2.getSuit(), temp2.getRank());
	}
	return temp;
}

Card Deck::peekCascade(int index)
{
	Card temp = Card();
	if (cascade->checkIndexEmpty(index) == false)
	{
		temp = (*cascade)[index]->peek();
	}
	return temp;
}

Card Deck::popCell(int index)
{
	Card& temp = openCell->operator[](index);


	return temp;
}

Card Deck::popFoundation(int index)
{
	return foundation->operator[](index)->pop();
}

Card Deck::popCascade(int index)
{
	return cascade->operator[](index)->pop();
}

void Deck::pushCascade(int index, Card value)
{
	cascade->operator[](index)->push(value);
}

bool Deck::pushCascadeQuery(int index, Card value)
{
	return (*cascade)[index]->pushQuery(value);
}

bool Deck::isCascEmpty(int index)
{
	return (*cascade)[index]->isEmpty();
}

int Deck::getVictoryCondition()
{
	int VP = 0;
	for (int i = 0; i < foundCount; i++)
	{
		if (!foundation->checkIndexEmpty(i))
		{
			if ((*foundation)[i]->checkWin())
			{
				VP++;
			}
		}
	}
	return VP;
}

void Deck::displayStartDeck()
{
	for (int i = 0; i < startingDeck->getLength(); i++)
	{
		(*startingDeck)[i].display();
		std::wcout << " ";
	}
}

void Deck::displayAllCells()
{
	std::wcout << L"Cells: ";
	for (int i = 0; i < cellCount; i++)
	{
		std::wcout << i + 1 << L")";
		if (i < openCell->getLength())
		{
			(*openCell)[i].display();
		}
		else
		{
			Card().display();
		}
	}
}

void Deck::displayFoundation()
{
	Card temp = Card();
	std::wcout << L"|| Foundation: ";
	for (int i = 0; i < foundCount; i++)
	{
		std::wcout << " " << i + 1 << ") ";
		if (foundation->operator[](i)->getSize() == 0)
		{
			temp = Card();
		}
		else
		{
			temp = foundation->operator[](i)->peek();

		}
		temp.display();
	}
}

void Deck::displayAllCascades()
{
	displayCascade(8, 0);
}

void Deck::displayCascade(int row, int i)
{
	Array<Card>* temp = nullptr;

	for (; i < row; i++)
	{
		std::wcout << L"\nCascade #" << i + 1 << L": ";
		if (!(*cascade)[i]->isEmpty())
		{
			temp = (*cascade)[i]->peekAll();


			int num = temp->getLength();
			for (int j = 0; j < num; j++)
			{
				std::wcout << SUITchar[(int)(*temp)[j].getSuit()] << RANKchar[(int)(*temp)[j].getRank()];

				if ((*temp)[j].getRank() != RANK::TEN)
				{
					std::wcout << " ";
				}
			}
			delete temp;
		}
		else
		{
			std::wcout << SUITchar[(int)SUIT::EMPTY] << RANKchar[(int)RANK::EMPTY];
		}

	}
}

int Deck::getN_move()
{
	//count each free cell
	int n_cell = 1;
	//count each free cascade
	int n_casc = 0;

	for (int i = 0; i < cellCount; i++)
	{
		if (openCell->checkIndexEmpty(i))
		{
			n_cell++;
		}
	}

	for (int i = 0; i < cascCount; i++)
	{
		if (cascade->peekElement(i)->isEmpty())
		{
			n_casc++;
		}
	}

	n_move = (pow(2, n_casc) * (n_cell));

	return n_move;
}

int Deck::RNG(int sz)
{
	sz -= 1;
	int r = rand() % sz;  // generate a random number from 0-sz
	//printf("%d\n", r);
	return r;
}
