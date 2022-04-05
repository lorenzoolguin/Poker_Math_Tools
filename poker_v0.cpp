#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

vector<string> deck;
vector<string> player_hand;
vector<string> flop;
vector<string> turn;
vector<string> river;


class Poker{
    public:

        vector<string> build_deck(){
            string suit[] = {"S", "D", "C", "H"};
            char rank[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
            for (int j =0; j<4; j++){
                for (int i=0; i<13; i++){
                    deck.push_back(rank[i] + suit[j]);
                }
            }
        //returns shuffled deck
        // Shuffle the deck
        //random_shuffle(deck.begin(),deck.end());
        // One of these 2 ways to shuffle
            // int n,m;
            // string temp;
            // for (n=0; n<52; n++){
            //     m=rand()%52;
            //     temp = deck[n];
            //     deck[n] = deck[m];
            //     deck[m] = temp;
            // }
            return deck; 
        }


        void print_deck(){
            cout << "Deck Size: " << deck.size() << endl;
            for (int i=0; i<deck.size(); i++){
                if (i == 51){
                    cout << deck[i] << endl;
                }
                else{
                cout << deck[i] << ", ";
                }
                
            }
        }

    
        // selects the next 2 cards from the deck, not used
        // vector<string> get_player_hand(){  
        //     int k = 0;
        //     while(k < 2){
        //         player_hand.push_back(deck[deck.size()-1]);
        //         deck.pop_back();
        //         k+=1;
        //     }
        //     return player_hand;
        // }

        vector<string> choose_player_hand(){  
            int k = 0;
            while(k < 2){
                string card;
                cout << "Enter card: " << endl;
                cin >> card;
                if (find(deck.begin(), deck.end(), card) != deck.end()){
                    player_hand.push_back(card);
                    auto it = find(deck.begin(), deck.end(), card);
                    deck.erase(it);
                    k+=1;
                }
                else{cout << "Try Again"<< endl;};
                
            }
            return player_hand;
        }

        void print_phand(){
            cout << "Hand Size: " << player_hand.size() << endl;
            for (int i=0; i<2; i++){
                if (i==1){cout << player_hand[i] << endl;}
                else cout << player_hand[i] << ", ";
                }
            }
        

        void print_flop(){
            cout << "Flop: ";
            for (int i=0; i<3; i++){
                if (i==2){
                    cout << flop[i] << endl;
                }
                else cout << flop[i] << ", ";
                }
            }
            

        vector<string> choose_flop(){
            cout << "\nFlop:" << endl;
            int k = 0;
            while(k < 3){
                string card;
                cout << "Enter cards: " << endl;
                cin >> card;
                if (find(deck.begin(), deck.end(), card) != deck.end()){
                    flop.push_back(card);
                    auto it = find(deck.begin(), deck.end(), card);
                    deck.erase(it);
                    k+=1;
                }
                else{cout << "Try Again"<< endl;};
            }
            return flop;
        }


        vector<string> choose_turn(){
            cout << "\nTurn:" << endl;
            int k = 0;
            while(k < 1){
                string card;
                cout << "Enter cards: " << endl;
                cin >> card;
                if (find(deck.begin(), deck.end(), card) != deck.end()){
                    turn.push_back(card);
                    auto it = find(deck.begin(), deck.end(), card);
                    deck.erase(it);
                    k+=1;
                }
                else{cout << "Try Again"<< endl;};
            }
            return turn;
        }

        void print_turn(){
            cout << "Turn: ";
            cout << flop[0]<< ", " << flop[1] << ", " << flop[2] << ", " << turn[0] << endl;
            }
        

        float pot_odds(){
            float pot_size;
            float call_size;
            float pot_odds;

            cout << "Pot Size: ";
            cin >> pot_size;
            cout << "\nCall Amount: ";
            cin >> call_size;
            pot_odds = call_size / (pot_size + call_size);
            cout << "\nPot Odds: " << pot_odds << "%";
            return pot_odds;
        }


        float card_equity(char hand_location){
            // (outs * 2) + 1 if more than 5 outs; + 2 if more than 13 outs
            // flop->river (outs*4) - (outs-8) if more than 9 outs
            float num_outs;
            float card_eq;
            cout << "\nNumber of Outs: ";
            cin >> num_outs;
            if (hand_location = 'f'){
                card_eq = (num_outs/47);
            }
            if (hand_location='t'){
                card_eq = (num_outs/46);
            }
            
            return card_eq;
        }

        vector<string> choose_river(){
            cout << "\nRiver:" << endl;
            int k = 0;
            while(k < 1){
                string card;
                cout << "Enter cards: " << endl;
                cin >> card;
                if (find(deck.begin(), deck.end(), card) != deck.end()){
                    river.push_back(card);
                    auto it = find(deck.begin(), deck.end(), card);
                    deck.erase(it);
                    k+=1;
                }
                else{cout << "Try Again"<< endl;};
            }
            return river;

            
        }

        void print_river(){
            cout << "River: ";
            cout << flop[0]<< ", " << flop[1] << ", " << flop[2] << ", " << turn[0] << ", " << river[0] << endl;
            }


        void move_on(float potodds, const float cardequity){
            cout << "Pot Odds: " << setprecision(2) << potodds << "   " << setprecision(2) << "Card Equity: " << cardequity;
            char move_on;
            int n=0;
            while (n < 1){
                cout << "\nMove On? (y/n)    ";
                cin >> move_on;
                if (move_on == 'y'){n=1;
                }
                else{
                    potodds = pot_odds();
                    cout << "\nPot Odds: " << setprecision(2) << potodds << "    " << "Card Equity: " << setprecision(2) << cardequity;
                }
            }
        }
};
 

int main()
{
    
    // Instantiate the deck
    //cout << ("######################################") << endl;
    Poker deck;
    deck.build_deck();
    deck.print_deck();
    deck.choose_player_hand();
    deck.print_phand();
    //deck.print_deck();
    deck.choose_flop();
    deck.print_flop();
    deck.print_phand();
    
    float pof = deck.pot_odds();
    float cef = deck.card_equity('f');
    deck.move_on(pof, cef);
    //another check for when someone re-raises

    //deck.print_deck();
    deck.choose_turn();
    deck.print_phand();
    deck.print_turn();

    float pot = deck.pot_odds(); // pot = pot odds turn, nothing to do with pot size
    float cet = deck.card_equity('t');
    deck.move_on(pot, cet);

    deck.choose_river();
    deck.print_phand();
    deck.print_river();

    float por = deck.pot_odds();
    float cer = deck.card_equity('r');
    deck.move_on(por, cer);

    //printf('%d\n', deck);
    
    return 0;
}