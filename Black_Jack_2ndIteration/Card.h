#ifndef CARD
#define CARD
#include <iostream>
#include <String>
#include <new>

using namespace std;

//Definition of a card class
class Card
{
	public:
		Card();
		Card(int card);
		void display(ostream & out)const;
		
		int value();//returns the value of the card 2=2 Jack=10, Ace = 1 or 10

		Card(const Card & Original);//copy constructor

		const Card & operator=(const Card & rightSide);//assignment operator

		const string getName();

		//~Card();
					
	private:
		string name;
		string suit;
		int cardVal;
};


ostream & operator<<(ostream & out, Card cardType);

#endif