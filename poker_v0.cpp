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
        

};
 

int main()
{
    
    // Instantiate the deck
    cout << ("######################################") << endl;
    Poker deck;
    deck.build_deck();
    deck.print_deck();
    deck.choose_player_hand();
    deck.print_phand();
    deck.print_deck();
    //printf('%d\n', deck);
    
    return 0;
}