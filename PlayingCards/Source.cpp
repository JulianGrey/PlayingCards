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

void playBlackJack(Card deck[]) {
	Card * chosenCard = new Card;
	vector<Card> * vDeck = resetDeck(deck);
	vector<Card> * cpuHand = new vector<Card>;
	vector<Card> * playerHand = new vector<Card>;
	int * cpuScore = new int;
	int * cpuScoreFC = new int; // Score of the first card in House's hand
	int * playerScore = new int;
	*cpuScore = *playerScore = 0;

	std::mt19937 * rng = new mt19937;
	(*rng).seed(std::random_device()());

	// Deal cards and calculate values
	for(unsigned i = 0; i < 4; i++) {
		std::uniform_int_distribution<std::mt19937::result_type> distDeck(0, (*vDeck).size() - 1);
		*chosenCard = (*vDeck).at(distDeck(*rng));

		if(i % 2 == 0) {
			(*cpuHand).push_back(*chosenCard);
			if((*chosenCard).value > 10) {
				*cpuScore += 10;
				if(i == 0) {
					*cpuScoreFC = 10;
				}
			}
			else if((*chosenCard).strValue == "Ace") {
				(*cpuScore) += 11;
				if(i == 0) {
					*cpuScoreFC = 11;
				}
			}
			else {
				*cpuScore += (*chosenCard).value;
				if(i == 0) {
					*cpuScoreFC = (*chosenCard).value;
				}
			}
			for(unsigned j = 0; j < (*vDeck).size(); j++) {
				if((*vDeck).at(j).printName() == (*chosenCard).printName()) {
					(*vDeck).erase((*vDeck).begin() + j);
					break;
				}
			}
		}
		else {
			(*playerHand).push_back(*chosenCard);
			if((*chosenCard).value > 10) {
				*playerScore += 10;
			}
			else if((*chosenCard).strValue == "Ace") {
				(*playerScore) += 11;
			}
			else {
				*playerScore += (*chosenCard).value;
			}
			for(unsigned j = 0; j < (*vDeck).size(); j++) {
				if((*vDeck).at(j).printName() == (*chosenCard).printName()) {
					(*vDeck).erase((*vDeck).begin() + j);
					break;
				}
			}
		}
	}

	std::cout << "House hand: " << (*cpuHand).at(0).printName();
	std::cout << ", ??? (score: " << *cpuScoreFC << ")";
	std::cout << "\nPlayer hand: ";

	for(unsigned i = 0; i < (*playerHand).size(); i++) {
		if(i != 0) {
			std::cout << ", ";
		}
		std::cout << (*playerHand).at(i).printName();
	}
	std::cout << " (score: " << *playerScore << ")";
	std::cout << "\n\n";

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