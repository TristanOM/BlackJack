#include "Deck.h"
#include "Player.h"
#include "Card.h"

#include <sstream>
#include <iostream>

using namespace std;

//DECK CLASS DEFINITIONS_________________________________________________________________________
Deck::Deck(){

//	myCardDeck[52];//Method to declare a deck of 52 different cards
	for(int i =0; i <52; i++){
		int Cardtype= i + 1;
		Card nCard = Card(i+1);
		
		myCardDeck.push_back(nCard);
		//myCardDeck[i] = nCard;
	}
	myCardDeck.shrink_to_fit();
}

//shuffle method (this method uses <ctime>)
void Deck::shuffle(){
	int xRan;
	srand( time(0)); // This will ensure a really randomized number by help of time.
	
	xRan=rand()%15+1; // Randomizing the number between 1-15.
		
	while(xRan !=0){
		random_shuffle(myCardDeck.begin(),myCardDeck.end());
		xRan = xRan - 1;
	}
}


Card Deck::drawCard(){
	Card a = myCardDeck.back();
	//return myCardDeck.back();
	myCardDeck.pop_back();//decrements the vector of the card drawn
	return a;
}

bool Deck::empty(){
	if(myCardDeck.end()!=myCardDeck.begin())
		return false;
	else
		return true;
}

void Deck::discard(){
	if(!empty())
		//deckPlace = deckPlace-1;//decrement decplace
		myCardDeck.pop_back();
	else
		cerr << "out of cards";
}

void Deck::display(){
	//for(int i =0; i<52;i++){
	//	myCardDeck[i].display(cout);
	//	//cout << myCardDeck[i];
	//}
	for(vector<Card>::iterator it = myCardDeck.begin(); it != myCardDeck.end(); ++it){
		Card h = *it;
		h.display(cout);
	}

}

//CARD CLASS DEFINITIONS_________________________________________________________________________
Card::Card(){
	name = "unNamed";
	suit = "unNamed";
	cardVal = 0;
}

Card::Card(int card){ // card must be from 1 to 52
	int cardMod13 = card % 13;
	if (cardMod13==0){
		name = "KING";
		cardVal = 10;
	}
	else if(cardMod13==1){
		name = "ACE";
		cardVal = cardMod13;//the card val is set to one for Ace
	}
	else if(cardMod13 <= 10){//if the card is a number than just get it by converting to a string
	string Result;//string which will contain the result

	stringstream convert; // stringstream used for the conversion

	convert << cardMod13;//add the value of Number to the characters in the stream

	name = convert.str();
	
	cardVal = cardMod13;//sets the card val 
	}
	else if(cardMod13 == 11){
		name = "JACK";
		//name = "\n  _________   \n"
		//	   "      |       \n"
		//       "      |       \n"
		//       "      |       \n"
		//	   "      |       \n"
		//	   "      |       \n"
		//	   " \\    |       \n"
		//	   "  \\   |       \n"
		//	   "   ---        \n";
		cardVal = 10;
	}
	else if(cardMod13 == 12){
		name = "QUEEN";
		//name = "\n    _____     \n"
		//	   "   /     \\   \n"
		//       "  /       \\  \n"
		//       " |         | \n"
		//	   " |         | \n"
		//	   " |         |  \n"
		//	   "  \\     \\ /  \n"
		//	   "   \\     /   \n"
		//	   "    -----  \\ \n";
		cardVal = 10;
	}
	else
		cerr<< "no suitable name";
	
	//This makes each numbers order represent the suit if the deck was split into 4ths
	if(card<=13){
		suit="HEARTS";
	}
	else if(card<=26){
		suit="CLUBS";
	}
	else if(card<=39){
		suit="SPADES";
	}
	else if(card<=52){
		suit="DIAMONDS";
		//suit="\n"
		//	   "   /\\     \n"
		//	   "  //\\\\    \n"
		//	   " ///\\\\\\   \n"
		//	   " \\\\\////   \n"
		//	   "  \\\///    \n"
		//	   "   \\/     \n";
	}
	else cerr<< "no suitable suit";
}

int Card::value(){
	return cardVal;
}

void Card::display(ostream & out)const {
	out<<" "<< name<< " of "<< suit;
}

//--- Definition of copy constructor
Card::Card(const Card & Original){

	//string h = Original.getName();
	name = Original.name;
	
	suit = Original.suit;
	cardVal = Original.cardVal;

}

//--- Definition of assignment operator
const Card & Card::operator=(const Card & rightSide){
	//check if equal 
	if(name== rightSide.name&& suit == rightSide.suit)
	{}
	else{
    name = rightSide.name;
	suit = rightSide.suit;
	cardVal = rightSide.cardVal;
	}
	return *this;
}

ostream & operator<<(ostream & out, const Card & cardVal)
{
	cardVal.display(out);
	return out;
}

const string Card::getName(){
	return name;
}

//Card::~Card(void){//May not need destructor since Card class has no pointers
//	delete this;
//}

//PLAYER CLASS DEFINITIONS_________________________________________________________________________
Player::Player(){
	cardSum = 0;
	cardCount = 0;
	chips = 0;
}

void Player::hit(Card newCard){//allows player to recieve card
	if(getCardSum() < 21){
		cardHand.push_back(newCard);
		cardSum = getCardSum();
		cardCount= cardCount + 1;
	}
	else{
		cerr << "Bust";//This is a temporary way to tell if a player has busted
	}
}

int Player::getCardSum(){//method to add the sum of cards taking into accound that an Ace can be a 1 or 11
	int sum = 0;
	int aceCount= 0;
	
	for(int i =0; i<cardCount;i++){
		if(cardHand[i].value() == 1)
			aceCount = aceCount + 1;
		else 
			sum = sum + cardHand[i].value();
	}
	while(aceCount >0){//add the Aces to the total sum
		if(sum + 11 <=21)
			sum = sum + 11;
		else
			sum = sum + 1;
		aceCount = aceCount - 1;
	}

	return sum;
}

void Player::display(){
	//cout << "\nYour hand: ";
	for(int i =0; i<cardCount;i++){
		cardHand[i].display(cout);
	}
}

void Player::displayHole(){
	cout<<"\nHouses' Hole Card: ";
	cardHand[0].display(cout);
}

//void Player::addChips(int a){
//	tenPointChips = tenPointChips + a;
//	cout<< "\nYou have been given "<< a<< " chips\n";
//}

void Player::addChips(int amount){
	chips = chips + amount;
}

//int Player::betChips(int a){
//	if(a<= tenPointChips){
//		tenPointChips = tenPointChips - a;
//		return a;
//	}
//	else{
//		cerr<< " \nYou don't have that many chips";
//		return 0;
//	}
//}

int Player::betChips(int bet){
	if(bet <= chips)
	{
		chips = chips - bet;
		return bet;
	}
	else
	{
		cerr << " \nYou don't have that many chips remaining.";
		return 0;
	}
}

int Player::getChips(){
	return chips;
}

int Player::getPoints(){
	int points = tenPointChips*10;
	return points;
}