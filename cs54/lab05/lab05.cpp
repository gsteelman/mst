//Gary Steelman
//CS54-D
//9.19.07
//Lab 05 does black jack 

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

struct cards
{
	int rank; // Let Ace = 1, Jack = 11, Queen = 12, and King = 13
	int score; //The card's individual actual score
	char suit; // Let spades = 's', clubs = 'c', hearts, 'h', and diamonds = 'd'
};

struct blackjack
{
	struct cards first;
	struct cards second;
	struct cards third;
};

int main()
{
	int suitRand = 0; //the suit randomizer
	int scoreTotal = 0; //total score of the hand
	
	char hit = 'n'; //whether the user wants to hit for another card or not
	
	cout << "Welcome to the blackjack program!" << endl;
	
	srand(time(NULL)); //seeds rand
	
	blackjack cards; //sets cards for easy use
	
	cards.first.rank = ((rand() % 13) + 1); //gets first rank randomly
	cards.second.rank = ((rand() % 13) + 1); //gets second rank randomly
	
	suitRand = ((rand() % 4) + 1); // gets first num equivilant of suit first
	
	//1 = spades, 2 = clubs, 3 = hearts, 4 = diamonds for card 1
	switch (suitRand)
	{
		case 1:
			cards.first.suit = 's';
			break;
		case 2:
			cards.first.suit = 'c';
			break;
		case 3:
			cards.first.suit = 'h';
			break;
		case 4:
			cards.first.suit = 'd';
			break;
		default:
			cards.first.suit = 'f';
			break;
	}
	
	suitRand = ((rand() % 4) + 1); // gets second num equivilant of suit second 
	
	//1 = spades, 2 = clubs, 3 = hearts, 4 = diamonds for card 2
	switch (suitRand)
	{
		case 1:
			cards.second.suit = 's';
			break;
		case 2:
			cards.second.suit = 'c';
			break;
		case 3:
			cards.second.suit = 'h';
			break;
		case 4:
			cards.second.suit = 'd';
			break;
		default:
			cards.second.suit = 'f';
			break;
	}

	//outputs the cards and their suits
	cout << "Card 1: [" << cards.first.rank << "] of " << cards.first.suit << endl;
	cout << "Card 2: [" << cards.second.rank << "] of " << cards.second.suit << endl;
	
	//assigns scores for the cards if theyre face cards
	switch (cards.first.rank)
	{
		case 1: 
			cards.first.score = 11;
			break;
		case 11:
			cards.first.score = 10;
			break;
		case 12:
			cards.first.score = 10;
			break;
		case 13:
			cards.first.score = 10;
			break;
		default:
			cards.first.score = cards.first.rank;
			break;
	}
	
	switch (cards.second.rank)
	{
		case 1: 
			cards.second.score = 11;
			break;
		case 11:
			cards.second.score = 10;
			break;
		case 12:
			cards.second.score = 10;
			break;
		case 13:
			cards.second.score = 10;
			break;
		default:
			cards.second.score = cards.second.rank;
			break;
	}
	
	//if the hand is 2 aces then the score is 12
	if (cards.first.rank == 1)
		if (cards.second.rank == 1)
			scoreTotal = 12; //2 aces
	//otherwise normal score
	else
	{
		scoreTotal = (cards.first.score + cards.second.score);
		cout << "Total Score: " << scoreTotal << endl;
	}
	
	//check for bust
	if (scoreTotal > 21) { cout << "Bust! Game over." << endl; }
	
	//checks for bonuses
	if (cards.first.rank == 1)
	{
		if (cards.first.suit == 'h')
			if (cards.second.rank == 13)
				if (cards.second.suit == 'd')
					cout << "You get a free meal at Clayton's Cafeteria!" << endl;	
		else if (cards.first.suit == 'c')
			if (cards.second.rank == 12)
				if (cards.second.suit == 'd')
					cout << "Bad luck hand! Get up and leave. Now." << endl;
		else if (cards.first.suit == 's')
			if (cards.second.rank == 11)
				if (cards.second.suit == 's')
					cout << "Jackpot hand! Win three times more than normal!" << endl;
	}
	
	if (cards.second.rank == 13)
		if (cards.second.suit == 'd')
			if (cards.first.rank == 11)
				if (cards.first.suit == 'h')
					cout << "You get a free meal at Clayton's Cafeteria!" << endl;
	if (cards.second.rank == 12)
		if (cards.second.suit == 'd')
			if (cards.first.rank == 11)
				if (cards.first.suit == 's')
					cout << "Bad luck hand! Get up and leave. Now." << endl;
	if (cards.second.rank == 11)
		if (cards.second.suit == 's')
			if (cards.first.rank == 11)
				if (cards.first.suit == 's')
					cout << "Jackpot hand! Win three times more than normal!" << endl;
	
	cout << "Would you like to hit [y/n]: "; //self explainatory
	cin >> hit;
	
	//generates a third card if the user hits
	if (hit == 'y')
	{
		cards.third.rank = ((rand() % 13) + 1); //gets third rank randomly
		suitRand = ((rand() % 4) + 1); // gets third num equivilant of suit third
		
		switch (suitRand)
		{
			case 1:
				cards.third.suit = 's';
				break;
			case 2:
				cards.third.suit = 'c';
				break;
			case 3:
				cards.third.suit = 'h';
				break;
			case 4:
				cards.third.suit = 'd';
				break;
			default:
				cards.third.suit = 'f';
				break;
		}
		
		switch (cards.second.rank)
		{
			case 1: 
				cards.third.score = 11;
				break;
			case 11:
				cards.third.score = 10;
				break;
			case 12:
				cards.third.score = 10;
				break;
			case 13:
				cards.third.score = 10;
				break;
			default:
				cards.third.score = cards.third.rank;
				break;
		}
	}
	
	//shows the user the third card and then checks for bust and thanks them for using this program
	cout << "Card 3: [" << cards.third.rank << "] of " << cards.third.suit << endl;
	
	scoreTotal = (cards.first.score + cards.second.score + cards.third.score);
	cout << "Total Score: " << scoreTotal << endl;
	
	if (scoreTotal > 21) { cout << "Bust! Game over. Shouldn't've hit." << endl; }
	
	cout << "Thanks for playing" << endl;
	
	return 0;
}
