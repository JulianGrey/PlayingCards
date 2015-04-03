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
	int suit, value;
	string strSuit, strValue, colour;
	void setValues(int a, int b, string c, string s, string v) {
		suit = a;
		value = b;
		colour = c;
		strSuit = s;
		strValue = v;
	}
	string printName() { return strValue + " of " + strSuit; }
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
			*strValue = wordify(j);
			card->setValues(i, j, *colour, *strSuit, *strValue);
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

void pickRandomCard(Card deck[]) {
	Card * chosenCard = new Card;
	vector<Card> * vDeck = resetDeck(deck);
	std::mt19937 * rng = new mt19937;
	(*rng).seed(std::random_device()());

	std::uniform_int_distribution<std::mt19937::result_type> distDeck(0, (*vDeck).size() - 1);

	*chosenCard = (*vDeck).at(distDeck(*rng));

	cout << "Chosen card: " << (*chosenCard).printName() << '\n';
	for(unsigned i = 0; i < (*vDeck).size(); i++) {
		if((*vDeck).at(i).printName() == (*chosenCard).printName()) {
			(*vDeck).erase((*vDeck).begin() + i);
			break;
		}
	}
	std::cout << "\n\n";
	for(unsigned i = 0; i < (*vDeck).size(); i++) {
		cout << (*vDeck).at(i).printName() << '\n';
	}
}

int main() {
	Card deck[52];
	Card * pDeck = buildDeck(deck);
	pickRandomCard(pDeck);

	system("PAUSE");
	return 0;
}