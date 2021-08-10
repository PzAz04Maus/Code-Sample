/* ************
Stephen Carter
moveData.h
Created 23APR21
*/
#pragma once

/* Class: moveData

Purpose:
	to serve as a packet of instructions for delivery to the deck object from the game object.
	We use this to reduce the number of arguments sent in each function.
	moveData objects are always created in the game object and transferred to the deck object. moveData is then used to interpret what the player wants to do

Data Members:
	m_name
		string to house the name of the selected decktype
		This is public because everyone should be able to see the decktype on the console when asking what our instructions actually say

	int m_type;//deck type
		an int that determines whether we're sending a card to the cells, foundation, or cascades
			//1: cell
			//2: foundation
			//3: Cascade
	int m_index;//Which of the arrays do we open?
		index of which container we're taking or placing a card to.
		For cell and foundation, it's just the address of 1 card.
		For cascade, it's the row address
	int cardsMoved;//number of cards to move
		how many cards the player wants to move
		By default this needs to always be initialized to 1 because we assume we can move 1 card. If this is left uninitialized, unexpected behavior will occur
	int deckSize;
		Once the deck Type is chosen, we fill deckSize with the maximum index that we can choose.
		This will be filled by the default maximum index values stored in every moveData object.

	int cellCount = 4;
		Maximum cell index
	int foundCount = 4;
		maximum foundation index
	int cascCount = 8;
		maximum cascade index

Canonicals:
	Because moveData is a static object, all we need to do is to create the object. Since no dynamic memory is allocated, the implicit destructor suffices for our purposes
	moveData(int loc, int addr = 0, int num = 1, int size = 0);
		Full spectrum constructor. Biggest difference is that we assume that the player gives a valid location
		the offered deck location will then be used to set m_name to the correct value
	moveData()
		uses the full spectrum constructor to fill moveData with the default settings...
		Location: empty
		index: 0
		cards moved: 1
		deckSize: 0

	int inputInt(int min, int max);
		Same as in game object

	//setters
		We call the setters after instantiation to populate the required information
	void setType(int type);
	void setFromTypePlayer() and void setToTypePlayer();
		While nominally the same function, setFrom and SetTo have different instructions for the player to read.
		Therefore, we double the setters based on whether our moveData object is a source or destination
	std::wstring setName(int action);
		takes input action (usually m_type) to populate m_name with the correct string
		returns m_name. We do this because we should always check what the current intended location is before telling the player
	void setSize(int action);
		we call setsize to interpret which container type moveData is set to, then set the size to the correct maximum index value of that container
	void setIndex(int addr);
		No boundary checking. This must be double checked by the coder
	void setNumMoves(int count);
		
	//getters
	int getType();
	int getNumMoves();
	int getDeckSize();
	int getIndex();
*/
class moveData
{
public:
	moveData();
	moveData(int loc, int addr = 0, int num = 1, int size = 0);

	int inputInt(int min, int max);

	//void moveCardControls(int* move1, int* move2);
	void setType(int type);
	void setFromTypePlayer();
	void setToTypePlayer();

	std::wstring setName(int action);
	void setSize(int action);
	void setIndex(int addr);

	void setNumMoves(int count);

	int getType();
	int getNumMoves();
	int getDeckSize();
	int getIndex();

	std::wstring m_name;//decktype String

private:
	//input
	int m_type;
	int m_index;
	int cardsMoved;

	//information
	int deckSize;//deck size


	int cellCount = 4;
	int foundCount = 4;
	int cascCount = 8;
};