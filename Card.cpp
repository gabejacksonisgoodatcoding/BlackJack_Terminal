#include <iostream>
using namespace std;

class Card{
    public:
        string rank, suit;
        Card(const string& rank, const string& suit) : rank(rank), suit(suit){};

        void displayCard() const{
            cout << rank << suit << endl; 
        }
        void displayRank() const{
            cout << rank << endl;
        }
};

