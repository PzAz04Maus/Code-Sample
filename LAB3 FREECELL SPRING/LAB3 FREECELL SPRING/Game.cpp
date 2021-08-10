#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <list>


using std::pair;
using std::make_pair;
using std::wcout;
using std::wcin;
using std::cin;
using std::endl;


#include "Game.h"
#include "Deck.h" 

enum class deckType;


Game::Game()
	:debug(true), mainDeck(nullptr)
{
	mainDeck = new Deck();
}

Game::~Game()
{
	delete mainDeck;
}

void Game::gameLoad(int seed)
{
	std::wcout << "Loading game\n";
	srand(seed);
	gameInit();

}

void Game::gameInit()
{
	mainDeck->buildNewDeck();
	mainDeck->shuffleDeck();
	mainDeck->dealCards();

	if (debug == true) { debugAll(); }
}

void Game::gameLoop()
{
	bool gameOver = false;
	int state = 0;

	while (gameOver == false)
	{
		wcout << "\n----------------\n";

		gameDisplay();

		state = actions(controls());

		gameOver = endGameQuery(&state);
	}
	wcout << "Game over\n";
}

void Game::begin()
{
	gameLoad();
	gameLoop();
}

void Game::gameDisplay()
{
	mainDeck->displayAllCells();
	mainDeck->displayFoundation();
	mainDeck->displayAllCascades();
	std::wcout << endl;
}

bool Game::endGameQuery(int* state)
{
	if (victoryCondition())
	{
		*state = 1;
	}
	//check whether you won here
	//if you won, change the state.
	bool returnState = false;
	switch (*state)
	{
	case 0:
		returnState = true;
		break;
	case 1:
		//Win
		returnState = true;
		wcout << "You Won!";
		break;
	default:
		returnState = false;
		break;
	}
	return returnState;
}

bool Game::victoryCondition()
{
	bool VP = false;
	if (mainDeck->getVictoryCondition() == 4)
	{
		VP = true;
	}
	return VP;
}

int Game::actions(int action)
{
	int state = -1;
	int move1 = 0;//ptr to return
	int move2 = 0;//ptr to return
	moveData from;
	moveData to;
	switch (action)
	{
	case 1://move
		moveCardMaster(from, to);
		break;
	case 2://exit
		state = 0;
		break;
	default:
		wcout << "Something broke here...";
		break;
	}
	return state;
}

int Game::controls()
{
	int fail;
	int action = 0;

	wcout << L"----------------\n";
	std::wcout << L"You may move up to " << mainDeck->getN_move() << " cards";
	std::wcout << endl;
	wcout << L"1) Move\n";
	wcout << L"2) Exit\n";

	return inputInt(1, 2);
}

//used to be moveCardDisplay,moveCardControls, and getFrom/GetTo
bool Game::moveCardMaster(moveData from, moveData to)
{
	wcout << L"----------------\n";

	from.setFromTypePlayer();
	to.setToTypePlayer();

	setNumMove(&from, &to);

	return mainDeck->moveCardLogic(from, to, from.getNumMoves());
}

void Game::setNumMove(moveData* from, moveData* to)
{
	int numMove = mainDeck->getN_move();
	if (from->getType() == 3 && to->getType() == 3)
	{
		wcout << L"How many do you want to move? (max is " << numMove << ")\n";
		from->setNumMoves(inputInt(1, numMove));
	}
	//else, just 1 card
}

int Game::inputInt(int min, int max)
{
	int action = min - 1;
	while (action<min || action>max)
	{
		wcout << L" ";
		cin >> action;
	}
	return action;
}

void Game::debugAll()
{
	debugDisplayStartDeck();
	wcout << L"\nYou can move up to " << mainDeck->getN_move() << L" Cards";
}

void Game::debugDisplayStartDeck()
{
	if (debug)
	{
		mainDeck->displayStartDeck();
	}
}