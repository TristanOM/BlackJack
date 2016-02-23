#ifndef PLAYER
#define PLAYER
#include <iostream>
#include <new>
#include <String>
#include <vector>
#include "Card.h"

using namespace std;

class Player
{
public:
	//default constructor
	Player();
	
	//constructor which gives the player starting cards
	Player(int cardA, int cardB);

	//get a new card from the deck
	void hit(Card newCard);

	//returns the sum of the cards
	int getCardSum();

	void display();

	void displayHole();

	void addChips(int a);//method to add a specified number of 10 point chips

	//int betChips(int a);

	int betChips(int a);

	int getChips();

	int getPoints();

private:
	vector<Card> cardHand;
	int cardSum;
	int cardCount;

	int tenPointChips;
	int chips;
	int total;

};

#endif