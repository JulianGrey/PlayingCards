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

int main() {
	Card deck[52]; // Create a constant deck array
	vector<Card> * vdeck = new vector<Card>;
	Card * card;
	string * strValue = new string;
	string * strSuit = new string;
	string * colour = new string;
	int * counter = new int;
	*counter = 0;

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
			(*vdeck).push_back(*card);
			deck[*counter] = *card;
			(*counter)++;
			delete card;
		}
	}
	delete colour;
	delete strSuit;
	delete strValue;

	Card * chosenCard = new Card;
	std::mt19937 * rng = new mt19937;
	(*rng).seed(std::random_device()());
	*counter = 0;

	std::uniform_int_distribution<std::mt19937::result_type> distDeck(0, (*vdeck).size() - 1);

	*chosenCard = (*vdeck).at(distDeck(*rng));

	cout << (distDeck(*rng)) << '\n';
	cout << (*chosenCard).printName() << '\n';
	for(unsigned i = 0; i < (*vdeck).size(); i++) {
		if((*vdeck).at(i).printName() == (*chosenCard).printName()) {
			(*vdeck).erase((*vdeck).begin() + i);
			break;
		}
	}

	for(unsigned i = 0; i < (*vdeck).size(); i++) {
		cout << (*vdeck).at(i).printName() << '\n';
	}

	system("PAUSE");
	return 0;
}