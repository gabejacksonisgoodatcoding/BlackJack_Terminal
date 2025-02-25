#include <iostream>
#include <random>
#include <vector>
#include "Card.cpp"
#include <algorithm>


using namespace std;


class Deck{
    private:
        vector<Card> cards;

    public:

        Deck() {
            const vector<string> suits = {"\u2665", "\u2666", "\u2663", "\u2660"};
            const vector<string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", 
            "Jack", "Queen", "King", "Ace"};

            for (auto& rank: ranks){
                for(auto& suit: suits){
                    cards.emplace_back(rank, suit);
                }
            }
        }


        void shuffleCards(){

            std::random_device rd;
            std::default_random_engine rng(rd());

            shuffle(cards.begin(), cards.end(), rng);
        } 

        void displayDeck(){
            for(auto& myCards: cards){
                myCards.displayCard();
            }
        }

        Card drawCard(){
            Card drawnCard = cards.back();
            cards.pop_back();
            return drawnCard;
             
        }
        int size(){
            return cards.size();
        }



};