#include <iostream>
#include <random>
#include <ctime>
#include "Deck.cpp"
#include <algorithm>


using namespace std;
using hand = vector<Card>; 


int cardAdd(hand cards){
    int total = 0;
    int aceCount = 0;

    for(auto& card: cards){
        if (card.rank != "Jack" && card.rank != "Queen" && card.rank != "King" && card.rank != "Ace"){
            total+= stoi(card.rank);
        }else if (card.rank != "Ace"){
            total += 10;
        }else{
            total+= 11;
            aceCount++;
        }
    }

    while (total > 21 && aceCount > 0) {
        total -= 10;
        aceCount--;
    }

    return total;
}

hand dealPlayer(Deck& deck){
    hand playerHand;

    while(playerHand.size() < 2){
        Card dealtCard = deck.drawCard();
        playerHand.push_back(dealtCard);
    }
    return playerHand;
}

void playerTurn(Deck* deck, hand* playerHand, Card& dealerCard, int* bet, int* playerMoney){
    string decision;
    int playerTotal = cardAdd(*playerHand);
    cout << "You have: " << playerTotal<< " vs a dealer ";
    dealerCard.displayRank();
    cout << "hit(h), stay(s), or double(d)?" << endl;

    while(cin >> decision){
        if(decision == "s"){
            break;
        }
        else if (decision == "h"){
        Card dealtCard = deck->drawCard();
        dealtCard.displayCard();
        playerHand->push_back(dealtCard);
        playerTotal = cardAdd(*playerHand);

        if(playerTotal >= 21) break;

        cout << "You have: " << playerTotal<< " vs a dealer ";
        dealerCard.displayRank();
        cout << "hit(h), stay(s), or double(d)?" << endl;
        }
        else if (decision == "d" && (*playerMoney >= 2 * *bet)){

            *bet += *bet;
            Card dealtCard = deck->drawCard();
            playerHand->push_back(dealtCard);
            playerTotal = cardAdd(*playerHand);
            break;
        }else {
            cout << "invalid input. Enter \"h\" to hit or \"s\" to stay" << endl;
        }
    
    }
}


void DealerTurn(Deck* deck, hand* hand, int playerScore){

    int dealerTotal = cardAdd(*hand);

    while (playerScore < 21 && dealerTotal < 17 && dealerTotal < 21)
    {
        cout<< "Dealer draws a card: " << endl;
        Card dealtCard = deck->drawCard();
        dealtCard.displayCard();
        hand->push_back(dealtCard);
        dealerTotal = cardAdd(*hand);
    }

}

void Results(hand* playerHand, hand* dealerHand, int* playerMoney, int* bet){
    int playerTotal = cardAdd(*playerHand);
    int dealerTotal = cardAdd(*dealerHand);

    if(dealerTotal != 21){
        if (playerTotal != 21){
            if(playerTotal > 21){ // Player busts
                cout << "Player busts with " << endl << endl;
                for (auto i: *playerHand){
                    i.displayCard();
                }
                cout << playerTotal << endl;
                cout<< "You lose :(" <<endl << endl;
                *playerMoney -= *bet;   
            }else if (dealerTotal > 21){ //Dealer busts
                cout << "Dealer busts with " << endl << endl;
                for (auto i: *dealerHand){
                    i.displayCard();
                    }
                cout << dealerTotal << endl;
                cout<< "You win!"<< endl << endl;
                *playerMoney+=*bet;               
            }else if (playerTotal > dealerTotal){ //Player wins by score
                cout << "Player wins with " << endl << endl;
                for (auto i: *playerHand){
                    i.displayCard();
                    }
                cout << "player has " << playerTotal << " vs " << dealerTotal<< endl << endl;
                cout<< "You win!" << endl << endl;
                *playerMoney+=*bet;  
            }else if (dealerTotal > playerTotal){ //dealer wins by score
                cout << "Dealer wins with " << endl <<endl;
                for (auto i: *dealerHand){
                    i.displayCard();
                    }
                cout << "Dealer has " << dealerTotal << " vs " << playerTotal<< endl <<endl;
                cout<< "You lose :(" <<endl <<endl;
                *playerMoney -= *bet;                 
            }else{ // push (equal score)
                cout << "You push " << endl;
                cout << dealerTotal << " vs " << playerTotal<< endl; 
            }

        }else{ // Player blackjack
            cout << "Player has blackjack with: " << endl <<endl;
            for (auto i: *playerHand){
                i.displayCard();
            }
            cout<< "You win!" <<endl << endl;
            *playerMoney += (*bet * 1.5);
        }

    }else{ // Dealer blackjack
        cout << "Dealer has blackjack with: " << endl <<endl;
        for (auto i: *dealerHand){
            i.displayCard();
        }
        cout <<"You lose :(" << endl << endl;
        *playerMoney -= *bet;
    }


}







int main(){

    int playerMoney = 100;

    int * pPlayerMoney = &playerMoney;
    
    cout<< "You have $" << playerMoney<< endl;

    // bet integer and pointer

    int bet;

    int *pBet = &bet;  

    cout << "How Much Do You Bet?: " << endl;

    
    while(cin >> bet){
        
        if(bet <= 0){
            break;
        }

    
        Deck deck;

        Deck *pDeck = &deck; //pointer to deck
        
        deck.shuffleCards();



        // logic for player hands


        hand playerHand = dealPlayer(deck);

        hand *pPlayerHand = &playerHand; //pointer to player hand

        hand dealerHand = dealPlayer(deck);

        hand *pDealerHand = &dealerHand; //pointer to dealer hand


        
        cout << endl << "Your hand is:" << endl;

        for(auto& card: playerHand){
            card.displayCard();
        }
        cout << endl;


        if (cardAdd(dealerHand) != 21 && cardAdd(playerHand) != 21){
            cout << "dealer has a:" << endl;

            dealerHand.back().displayCard();
            cout<< endl;

            playerTurn(pDeck, pPlayerHand, dealerHand.back(), pBet, pPlayerMoney);

            DealerTurn(pDeck, pDealerHand, cardAdd(playerHand));
                
            Results(pPlayerHand, pDealerHand, pPlayerMoney, pBet);
        }else{
            Results(pPlayerHand, pDealerHand, pPlayerMoney, pBet);
        }
        if (playerMoney <= 0){
            break;
        }else{
            cout<< "You have $" << playerMoney<< endl;
            cout << "How Much Do You Bet?: " << endl;
        }
    }

    return 0;


}






