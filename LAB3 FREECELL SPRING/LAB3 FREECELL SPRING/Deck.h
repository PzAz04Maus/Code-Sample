/* ************
Stephen Carter
Deck.h
Created 20APR21
*/
#pragma once
#include "moveData.h"

template<class T> class Array;
template<class T> class AStack;
template<class T> class LStack;
template<class Card> class Foundation;
template<class Card> class Tableau;
enum class deckType;

/* class: Deck

Purpose: 
	handles the cell, foundation, and cascade containers for the game object.
	All actions linking through the game to the data objects route through here

Data Members:
	Array<Card>* openCell;
		Cell container
	Array<Foundation<Card>*>* foundation;
		Foundation container
	Array<Tableau<Card>*>* cascade;
		8x7 cascade containers

	Array<Card>* startingDeck;
		Container holding the original starter deck.
		Only used for initialization

	int n_move;
		maximum number of moves allowed by the game

Standard values
	int cellCount = 4;
	int foundCount = 4;
	int cascCount = 8;
		How many arrays can we fit?

	3 class defined variables which determine the size of the container

Canonicals:
	Because only one object will ever be created, only Deck() and ~Deck() are required.
	Deck();
	~Deck();
	
Methods:
	//Initialization
	buildNewDeck()
		creates a fresh deck of all 4 suits with 13 cards each
	shuffleDeck()
		swaps 2 random cards 52 times
	dealCards()
		Calls dealCascade to fill up each cascade with our newly created deck
	dealCascade()
		Pops startingDeck to push into cascade column(address) num times.
		This is called 8 times to fill each cascade with the starting cards

	//Moving Logic
	bool moveCardLogic(moveData from, moveData to, int numMove);
		Manager function that contains all the important information of a card swap
		from: a data object describing the selected container we're taking a card from
		to: data object describing the selected container we're putting a card
		numMove: the number of cards we can select

		moveCardLogic calls SrcLogic, DestLogic, and Cleanup to cover all 3 bases of a potential card move.

	void moveSrcLogic(Array<Card>* temp, moveData * from, moveData * to, int numMove, int err_i);
		srclogic checks whether we can actually take this card from x.
		If moveSrcsLogic fails, we update err_i

		err_i tells us how far we need to rewind an action before it failed. If the action fails, we need to put all the cards we took back where they belong
		
	bool moveDestLogic(Array<Card>* temp, moveData * to, int numMove, int* err_i);
		DestLogic checks whether we can place the selected card in the destination.
		If the action fails, we need to update err_i to when the action failed.
		We tell moveCardLogic whether this transfer succeeded or failed
		
	void moveCleanup(bool result, Array<Card>* temp, moveData * from, moveData * to, int numMove, int err_i);
		moveCleanup handles the last remaining card transfers left from the process.
		If the process failed, we have to put the cards back, including the illegally moved ones, denoted by err_i
		All the rest have to be popped from the temp stack back to their original destination

		If successful, we only have to clean up cell or foundation of any duplicate cards

	//Support
	void checkEmpty(Array<Card>* temp, moveData& input, const wchar_t* msg);
		If temp contains an empty card, the transfer has failed and we need to immediately cut the transfer off before it causes damage
	void extractCell(int i);
		calls Array's extractElement() function

	Card peekCell(int i)
		we can inspect any of the 4 open cells for our desired card.
		i indexes to 1 of 4 elements
		contains boundary protection
		If we return a blank Card(), the peek has failed: This spot is therefore empty
		
	Card peekFoundation()
		we can inspect any of the 4 open foundations for a card.
		i indexes to 1 of 4 elements
		contains boundary protection
		If we return a blank Card(), the peek has failed: This spot is therefore empty

	Card peekCascade(int i)
		we can inspect the top card of any cascade
		i indexes to 1 of 8 arrays in the cascade range
		contains boundary protection
		If we return a blank Card(), the peek has failed: This spot is therefore empty
		
	popCell(index)
		Creates a temp card populated with the indexed element
	popFoundation(index)
		returns a popped element from the indexed foundation
		calls AStack->Pop
	popCascade(index)
		returns a popped element from the indexed cascade array
		calls LStack->Pop

	void pushCascade(int index, Card value);
		Indexes to the correct Cascade array, then pushes Card value onto that stack
		calls LStack->push()
	bool pushCascadeQuery(int index, Card value);
		Queries the indexed cascade array on whether Card value can legally be moved onto that stack
		Checks whether it's the right suit and card
	bool isCascEmpty(int index);
		Queries the indexed cascade array on whether it's actually empty
		calls LStack->isEmpty()

	int getVictoryCondition();
		Inspects each foundation for whether it has a king on top
		We start with counter VP, which represents the number of kings. For each King detected, we increment this counter by 1
		Return VP. If VP == 4, we've won

Display
	void displayStartDeck();
		debug display that shows the initial deck that will be used to populate the cascades
	void displayAllCells();
		displays the contents of all cell containers
		has out-of-bounds protection
		if the contents are empty, displays a blank card instead
	void displayFoundation();
		displays the top content of each foundation container
		has out-of-bounds protection
		if the contents are empty, displays a blank card instead

	void displayAllCascades();
		Calls displayCascade for every available cascade object we have
	void displayCascade(int row, int i);
		Display Cascade iterates through the array object to display each card of a set.
		We can call certain cascades by saying which cascade to start displaying up to which one we end on
		i is the starting position, starting at 0
		row is the number of rows we wish to display

	int getN_move();
		While described as a get, getN_move is both a setter and a getter.
		When we try to get n_move, we update the number of available cards we can move, then return the updated value
		This value is then saved as n_move.

	int RNG(int sz);
		function called by shuffleDeck to effectively randomize our deck
		initialized and seeded by class Game using the time

*/

class Deck
{
public:
	Deck();
	~Deck();

	void buildNewDeck();
	void shuffleDeck();
	void dealCards();
	void dealCascade(int i, int address);

	bool moveCardLogic(moveData from, moveData to, int numMove);
	void moveSrcLogic(Array<Card>* temp, moveData * from, moveData * to, int numMove, int err_i);
	bool moveDestLogic(Array<Card>* temp, moveData * to, int numMove, int* err_i);
	void moveCleanup(bool result, Array<Card>* temp, moveData * from, moveData * to, int numMove, int err_i);

	void checkEmpty(Array<Card>* temp, moveData& input, const wchar_t* msg);
	void extractCell(int i);

	
	Card peekCell(int index);
	Card peekFoundation(int index);
	Card peekCascade(int index);

	Card popCell(int index);
	Card popFoundation(int index);
	Card popCascade(int index);

	void pushCascade(int index, Card value);
	bool pushCascadeQuery(int index, Card value);
	bool isCascEmpty(int index);

	int getVictoryCondition();

	void displayStartDeck();
	void displayAllCells();
	void displayFoundation();

	void displayAllCascades();
	void displayCascade(int row, int i);

	int getN_move();

	int RNG(int sz);

	int cellCount = 4;
	int foundCount = 4;
	int cascCount = 8;
private:
	Array<Card>* openCell;
	Array<Foundation<Card>*>* foundation;
	Array<Tableau<Card>*>* cascade;
	Array<Card>* startingDeck;

	int n_move;
};

