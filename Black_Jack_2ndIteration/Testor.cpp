#include "Deck.h"
#include <iostream>
using namespace std;

void showCommands()
{
	cout << "\nUse the following commands to test player class:\n"
		<< "h --- hit\n"
		<< "s --- stay\n"
		<< "b --- bet\n"
		<< "g --- get your chip amount\n"
		<< "p --- get the Pot amount\n"
		<< "r --- display rules\n";
}

void showGameExplanation()
{
	cout << "\nBlackJack rules\n"
		<< "Rules:\n"
		<< "In blackjack, players don't play against each other; and they don't co-operate.\n"
		<< "The only competition is the dealer. The aim of the game is to accumulate a\n"
		<< "higher point total than the dealer, but without going over 21. The game\n"
		<< "starts with the players and the dealer receiving two cards each.\n"
		<< "The players' cards are normally dealt face up, while the dealer has one face\n" 
		<< "down (called the hole card) and one face up. When all players have finished\n"
		<< "their actions, the dealer turns over his hole card. If the dealer doesn't\n"
		<< "have a blackjack, he hits (takes more cards) or stands depending on the\n" 
		<< "value of the hand. Contrary to the player, though, the dealer's action is\n"
		<< "completely dictated by the rules. The dealer must hit if the value of the\n" 
		<< "hand is lower than 17, otherwise the dealer will stand.\n";
	cout << "\nTerms to know:\n"
		<< "\nPush - the hand is a draw. The player keeps his bet, neither winning nor losing."
		<< "\nNatural - player or dealer has 21 with two card"
		<< "\nBust - having a higher card total than 21.";
		
	cout << "\nHow to win\n"
		<< "\nGet a higher total than the dealer to win";
}

int main()
{
	char command;
	char playAgain;
	int Wins = 0;
	int Losses = 0;
	int Pot = 0;
	int chips = 100; //set chips for player to 10
	int bets = 0;
	cout<< "Welcome to Blackjack!\n"
	    << "You have been given 100 chips to bet with.\n"
		<< "Please press R to view the rules!\n"
		<< "Good luck!\n";

			
	do{
		showCommands();
		cout<<"\n--- New Game ---\n";
		Pot = 0;
		Deck theDeck;
		theDeck.shuffle();

		Player dealer;
		dealer.hit(theDeck.drawCard());
		dealer.hit(theDeck.drawCard());
		dealer.displayHole();
		Player playerOne;

		playerOne.addChips(100); //add chips

		playerOne.hit(theDeck.drawCard());
		playerOne.hit(theDeck.drawCard());
		
		cout << "\nYour hand: ";
		playerOne.display();
		cout<<"\nCard total: " << playerOne.getCardSum();

		do
		{
			cout << "\nCommand? ";
			cin >> command;
			if (isupper(command)) command = tolower(command);

			switch(command)
			{
				case 'h'://draw card

					playerOne.hit(theDeck.drawCard());
					cout<<"\nHit\n";
					playerOne.display();
					cout<<"\nCard total: " << playerOne.getCardSum();

				break;

				case 'c':

					cout<<"\nYour sum " << playerOne.getCardSum();

				break;

				case 'b':

					if(chips > 0)
					{
						cout << "\nPlease enter a bet, you have " << chips << " chips left.\n";
						cin >> bets;
						if (bets <= chips && bets >= 0)
						{
							chips = chips - bets;
							Pot = Pot + bets + bets;// dealer matches players bet
						}
						else
							cout<<"You don't have that much to bet\n";
					}
					else
						cout<<"\nYou have no more chips to bet\n";
					

				break;

				case 'r':
				
					showGameExplanation();

				break;

				case 'g':
				
					cout<<"Chips left: " << chips;

				break;

				case 's'://stay
				
					

				break;

				case 'p'://pot
				
					cout<<"Pot total: "<<Pot << endl;

				break;
		
				default:
						cout << "*** Illegal command: " << command << endl;
				}
			}
		while (command != 's'&& playerOne.getCardSum() < 21);

		if(playerOne.getCardSum() > 21){
			cout<<"\nYour total is over 21!"
				<<"\nPlayer busts!";
				Losses = Losses + 1;
				cout<<"\nPlayer loses " << bets << " chips.";
		}
		else{
	
			while(dealer.getCardSum() < 17){
				cout <<"\nHouse total: "<<dealer.getCardSum();
				cout <<"\nHouse hits!";
				dealer.hit(theDeck.drawCard());
			}

			if(dealer.getCardSum()> 21){
				cout<< "\nHouse busts!";
				cout<<"\nPlayer wins " << bets << " chips.";
				chips = chips + Pot;
				Wins = Wins + 1;
			}
			else if(dealer.getCardSum()==playerOne.getCardSum())
			{
				cout<<"\nHouse and player have the same total!";
				cout<<"\nTie\n";
				chips = chips + bets;
			}
			else if(dealer.getCardSum()< playerOne.getCardSum())
			{
				cout<<"\nPlayers hand is higher!";
				cout<<"\nPlayer Wins!\n";
				cout<<"\nPlayer wins " << bets << " chips!";
	
				chips = chips + Pot;
				Wins = Wins + 1;
			}
			else if (dealer.getCardSum() > playerOne.getCardSum()){
				cout<<"\nHouse's hand is higher!";
				cout<<"\nHouse Wins!\n";
				cout<<"\nPlayer loses " << bets << " chips.";
				Losses = Losses + 1;
			}
			else
			{
				cout<<"\nHouse Wins!\n";
			}


			cout<< "\nHOUSE HAND: ";
			dealer.display();
			cout <<"\nHOUSE: "<<dealer.getCardSum();

			//display players hand
			cout << "\nYOUR HAND: ";
			playerOne.display();
			cout <<"\nYOU: "<< playerOne.getCardSum();

			
		}

		cout << "\n\nWins: " << Wins;
		cout << "\nLosses: " << Losses;
		cout << "\nChips: " << chips;

		if( chips > 0 && chips < 250)
			cout<< "\nn to stop or any other key to keep playing\n";
		else
			cout<< "\nPress key to continue...\n";

		cin >> playAgain;
		if (isupper(playAgain)) playAgain = tolower(playAgain);
	}
	//while (playAgain != 'n');
	while (playAgain != 'n' && chips > 0 && chips < 250);
	if (chips <= 0)
	{
		cout << "You've run out of chips :'(!\n"
			 << "GAME OVER!\n THANKS FOR PLAYING!";
		//system("exit");
	}
	else if (chips >= 250)
	{
		cout << "The house has run out of money!!\n"
			 << "YOU WIN!\n GREAT JOB!";
		//system("exit");
	}
	//while (playAgain != 'n' && chips > 0);
	
	char a;
	cin>> a;
	return 0;
}