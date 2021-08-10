/* ************
Stephen Carter
Game.h
Created 20APR21
*/
#pragma once
#include <ctime>
class Card;
class Deck;
template <typename Card> class AStack;

#include "moveData.h"

/* Class: Game

Purpose: This is the game's interface between player and its containers.

Data Members:
	

Canonical Functions
	because we're creating only 1 object, all we need to do are create and destroy one instance
	Game()
		forms a new deck object
	~Game()
		Deletes our deck

Methods:
	void gameLoad(int seed = time(nullptr));
		master function containing all game setup methods
	void gameInit();
		game setup method. calls deck to build, shuffle, and deal the cards.
	void gameLoop();
		main gameplay loop
	void begin();
		loads the game by calling setup, then begins the loop.
	void gameDisplay();
		main gameplay display. All the cards are laid out here for the player to see

	//state management
	bool endGameQuery(int* state);
		queries what state the game is in at the end of every turn.
		state gets modified by endGameQuery depending on the method's findings. This is effectively returned
		method returns whether we should end the game or not with a bool.
		If we return true, we end the game loop
		Otherwise, no change

		state -1: continue game
		state 0: early quit
		state 1: game won

	bool victoryCondition();
		calls maindeck to update which foundations hold a king on the top of their stack.
		If we reach 4 of these, we win the game

	//instructions
	int actions(int action);
		Interface interpreter for every available action in Freecell.
		This takes the return from controls to interpret/resolve the next action
		Depending on how the next action resolves, we return a gamestate which endGameQuery() will interpret at the end of every turn.
	int controls();
		control surface that accepts/curates player inputs. Controls will always become an argument in actions.
		This surface also outputs the control instructions, as well as the maximum number of cards we can move
		returns a call to inputInt with the correct arguments

	int inputInt(int min, int max);
		Generic input implementation. Instructions are always left outside of the function, then we place the player in a while loop until he produces a legal instruction
		All legal instructions must be an integer that fits between min and max.

	//card movement instructions
	bool moveCardMaster(moveData from, moveData to);
		Calls the deck object and delivers the instructions to it for processing. Deck object returns whether we succeeded or not
		we store most of the information as a moveData object for easy management
	void setNumMove(moveData* from, moveData* to);
		interpreter function for how many cards we're able to move.

		If we're moving between cascades, the player may choose to move as many cards as legally allowed 
		otherwise, we can only move 1

		we stash the player's decision into the from instruction object

	//debug
	debugAll
		Displays the start deck and how many cards we can move
	debugDisplayStartDeck
		Calls the display function for the starting deck container

*/

class Game
{
	
public:
	Game();
	~Game();

	void gameLoad(int seed = time(nullptr));
	void gameInit();
	void gameLoop();
	void begin();
	void gameDisplay();


	bool endGameQuery(int* state);
	bool victoryCondition();
	int actions(int action);
	int controls();
	int inputInt(int min, int max);

	bool moveCardMaster(moveData from, moveData to);
	void setNumMove(moveData* from, moveData* to);

	void debugAll();
	void debugDisplayStartDeck();

private:
	friend class moveData;
	Deck* mainDeck;
	bool debug;
};
