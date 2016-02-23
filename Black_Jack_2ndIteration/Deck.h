#ifndef DECK
#define DECK
#include <iostream>
#include <new>
#include <String>
#include <vector>
#include "Player.h"
#include "Card.h"
#include <algorithm> 
#include <ctime>

using namespace std;

//This class produces all 52 different cards by using all numbers from 1 -52 and and creating each individual card this way
class Deck
{
public:
	Deck();

	void shuffle();

	void discard();

	void display();

	bool empty();//check if there is no more cards

	//string getCard();// Method to get the suit and name of a card
	Card drawCard();

private:

	//Card myCardDeck[52];//deck of enum cards
	vector<Card> myCardDeck;

	
};



#endif