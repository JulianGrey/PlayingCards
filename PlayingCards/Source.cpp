#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>
using namespace std;

class Card {
  public:
	int value;
	string suit, strValue, colour;
	void setValues(int a, string c, string s, string v) {
		value = a;
		colour = c;
		suit = s;
		strValue = v;
	}
	string printName() { return strValue + " of " + suit; }
};

string wordify(int value) {
	int number[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	string strValue[13] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

	return strValue[value - 1];
}

Card * buildDeck(Card deck[]) {
	Card * card;
	string * strValue = new string;
	string * strSuit = new string;
	string * colour = new string;
	int * counter = new int;
	(*counter) = 0;

	for(unsigned i = 1; i < 5; i++) {
		switch(i) {
		case 1:
			*strSuit = "Spades";
			*colour = "Black";
			break;
		case 2:
			*strSuit = "Hearts";
			*colour = "Red";
			break;
		case 3:
			*strSuit = "Clubs";
			*colour = "Black";
			break;
		case 4:
			*strSuit = "Diamonds";
			*colour = "Red";
			break;
		}
		for(unsigned j = 1; j < 14; j++) {
			card = new Card;
			int * value = new int;
			*strValue = wordify(j);
			*value = j;
			card->setValues(*value, *colour, *strSuit, *strValue);
			deck[*counter] = *card;
			(*counter)++;
			delete card;
		}
	}
	delete colour;
	delete counter;
	delete strSuit;
	delete strValue;

	return deck;
}

vector<Card> * resetDeck(Card deck[]) {
	vector<Card> * vDeck = new vector < Card > ;
	for(unsigned i = 0; i < 52; i++) {
		(*vDeck).push_back(deck[i]);
	}
	return vDeck;
}

void randomCard(vector<Card> * deck, Card * card, std::mt19937 * rng) {
	std::uniform_int_distribution<std::mt19937::result_type> distDeck(0, (*deck).size() - 1);
	*card = (*deck).at(distDeck(*rng));
}

void dealCard(vector<Card> * deck, Card * card, vector<Card> * hand, int * score, int * houseInitScore, int cardDealNum) {
	(*hand).push_back(*card);
	if((*card).value > 10) {
		*score += 10;
		if(cardDealNum == 0) {
			*houseInitScore += 10;
		}
	}
	else if((*card).strValue == "Ace") {
		*score += 11;
		if(cardDealNum == 0) {
			*houseInitScore += 11;
		}
	}
	else {
		*score += (*card).value;
		if(cardDealNum == 0) {
			*houseInitScore += (*card).value;
		}
	}
	for(unsigned i = 0; i < (*deck).size(); i++) {
		if((*deck).at(i).printName() == (*card).printName()) {
			(*deck).erase((*deck).begin() + i);
		}
	}
}

void printPlayerHand(vector<Card> * hand, int * score) {
	std::cout << "\nPlayer hand: ";
	for(unsigned i = 0; i < (*hand).size(); i++) {
		if(i != 0) {
			std::cout << ", ";
		}
		std::cout << (*hand).at(i).printName();
	}
	std::cout << " (score: " << *score << ")\n\n";
}

void playBlackJack(Card deck[]) {
	Card * chosenCard = new Card;
	vector<Card> * vDeck = resetDeck(deck);
	vector<Card> * houseHand = new vector<Card>;
	vector<Card> * playerHand = new vector<Card>;
	char * option = new char;
	int * turn = new int;
	int * houseScore = new int;
	int * houseInitScore = new int; // Score of the first card in House's hand
	int * playerScore = new int;

	bool * selectDouble = new bool;
	bool * selectSplit = new bool;
	bool * isPlayerTurn = new bool;

	*houseInitScore = *playerScore = 0;

	std::mt19937 * rng = new mt19937;
	(*rng).seed(std::random_device()());

	// Deal cards and calculate values
	for(unsigned i = 0; i < 4; i++) {
		randomCard(vDeck, chosenCard, rng);

		if(i % 2 == 0) {
			dealCard(vDeck, chosenCard, houseHand, houseScore, houseInitScore, i);
		}
		else {
			dealCard(vDeck, chosenCard, playerHand, playerScore, houseInitScore, i);
		}
	}

	std::cout << "House hand: " << (*houseHand).at(0).printName();
	std::cout << ", ??? (score: " << *houseInitScore << ")";
	printPlayerHand(playerHand, playerScore);
	
	// Gameplay
	*turn = 1;
	*isPlayerTurn = true;
	*selectDouble = false;
	*selectSplit = false;

	while(*turn == 1) {
		if(*playerScore < 21) {
			std::cout << "What do you want to do?\n" << "([H]it, S[t]and, [D]ouble";
			if((*playerHand).at(0).value == (*playerHand).at(1).value || (*playerHand).at(0).value >= 10 && (*playerHand).at(1).value >= 10) {
				std::cout << ", S[p]lit";
			}
			std::cout << "): ";
			std::cin >> *option;

			switch(*option) {
			case 'H':
			case 'h':
				std::cout << "Hit chosen\n";
				randomCard(vDeck, chosenCard, rng);
				dealCard(vDeck, chosenCard, playerHand, playerScore, houseInitScore, 0);
				printPlayerHand(playerHand, playerScore);
				(*turn)++;
				break;
			case 'T':
			case 't':
				std::cout << "Stand chosen\n";
				*isPlayerTurn = false;
				(*turn)++;
				break;
			case 'D':
			case 'd':
				std::cout << "Double chosen\n";
				*selectDouble = true;
				*isPlayerTurn = false;
				randomCard(vDeck, chosenCard, rng);
				dealCard(vDeck, chosenCard, playerHand, playerScore, houseInitScore, 0);
				printPlayerHand(playerHand, playerScore);
				(*turn)++;
				break;
			case 'P':
			case 'p':
				if((*playerHand).at(0).value == (*playerHand).at(1).value || (*playerHand).at(0).value >= 10 && (*playerHand).at(1).value >= 10) {
					std::cout << "Split chosen\n";
					*selectSplit = true;
					(*turn)++;
					break;
				}
				else {
					std::cout << "Cannot split\n";
				}
			default:
				std::cout << "Invalid option, choose again\n";
				break;
			}
		}
		else {
			std::cout << "21\n";
			(*turn)++;
		}
	}

	while(*playerScore < 21 && *isPlayerTurn == true && *turn > 1) {
		std::cout << "What do you want to do?\n" << "([H]it, [S]tand)" << '\n';
		std::cin >> *option;
		switch(*option) {
			case 'H':
			case 'h':
				std::cout << "Hit chosen\n";
				randomCard(vDeck, chosenCard, rng);
				dealCard(vDeck, chosenCard, playerHand, playerScore, houseInitScore, 0);
				printPlayerHand(playerHand, playerScore);
				(*turn)++;
				break;
			case 'T':
			case 't':
				std::cout << "Stand chosen\n";
				*isPlayerTurn = false;
				(*turn)++;
				break;
			default:
				std::cout << "Invalid option, choose again\n";
				break;
		}
	}

	if(*playerScore > 21) {
		std::cout << "BUST!!\n\n";
	}

	// Debug listing remaining cards in deck
	/*for(unsigned i = 0; i < (*vDeck).size(); i++) {
		std::cout << (*vDeck).at(i).printName() << '\n';
	}*/
}

int main() {
	Card deck[52]; // Default deck
	Card * pDeck = buildDeck(deck); // Dynamic deck. This will be used as cards are taken from the deck
	playBlackJack(pDeck);

	system("PAUSE");
	return 0;
}