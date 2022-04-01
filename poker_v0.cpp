#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;


/* void shuffle(){
    int n,m,temp;
    for (n=0; n<52; n++){
        m=rand()%52;
        temp = deck[n];
        deck[n] = deck[m];
        deck[m] = temp;
    }
} */
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
        //vector<string> deck;
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

            return deck; // returns shuffled deck

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
        // selects the next 2 cards from the deck, based on the randomized deck
        vector<string> get_player_hand(){  
            int k = 0;
            while(k < 2){
                player_hand.push_back(deck[deck.size()-1]);
                deck.pop_back();
                k+=1;
            }
            return player_hand;
        }
        //allows you to choose the 2 cards given preflop
        // if (std::find(v.begin(), v.end(), key) != v.end()) {
        //     std::cout << "Element found";
        // }
        // else {
        //     std::cout << "Element not found";
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


        float card_equity(){
            float num_outs;
            cout << "\nNumber of Outs: ";
            cin >> num_outs;
            float card_eq = (num_outs*2) + 1;
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
    float cef = deck.card_equity();
    cout << "Pot Odds: " << pof << "%    " << "Card Equity: " << cef << "%";
    char move_on;
    int n=0;
    while (n < 1){
        cout << "\nMove On? (y/n)" << endl;
        cin >> move_on;
        if (move_on == 'y'){
            n=1;
        }
        else{
            pof = deck.pot_odds();
            cout << "Pot Odds: " << pof << "    " << "Card Equity: " << cef << "%";
        }

    }
    //another check for when someone re-raises

    //deck.print_deck();
    deck.choose_turn();
    deck.print_phand();
    deck.print_turn();

    float pot = deck.pot_odds(); // pot = pot odds turn, nothing to do with pot size
    float cet = deck.card_equity();
    cout << "Pot Odds: " << pot << "%   " << "Card Equity: " << cet << "%";
    char move_on1;
    int n1=0;
    while (n1 < 1){
        cout << "\nMove On? (y/n)" << endl;
        cin >> move_on1;
        if (move_on1 == 'y'){
            n1=1;
        }
        else{
            pot = deck.pot_odds();
            cout << "Pot Odds: " << pot << "    " << "Card Equity: " << cet << "%";
        }

    }

    deck.choose_river();
    deck.print_phand();
    deck.print_river();

    float por = deck.pot_odds();
    float cer = deck.card_equity();
    cout << "Pot Odds: " << por << "%   " << "Card Equity: " << cer << "%";
    char move_on2;
    int n2=0;
    while (n2 < 1){
        cout << "\nMove On? (y/n)    ";
        cin >> move_on2;
        if (move_on2 == 'y'){
            n2=1;
        }
        else{
            por = deck.pot_odds();
            cout << "Pot Odds: " << por << "    " << "Card Equity: " << cer << "%";
        }

    }



    //printf('%d\n', deck);
    
    return 0;
}