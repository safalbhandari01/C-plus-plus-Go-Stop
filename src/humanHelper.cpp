//***************************THIS CLASS IS NOT IN USE. PLEASE IGNORE THIS CLASS*********************************

#include "humanHelper.h"

#include<string>
#include<vector>
#include<map>

using namespace std;

//implementation of the virtual function for human class
void HUMANHELPER::play(vector< vector<Card*> > &cardsOnLayout,vector<Card*> &cardsOnStockPile){
    cout<<"\tBot Play\n";

    int stackedPairIndex = -1;  //No need for stackedPairIndex in this class remove it later on 
    
    //NOTE::here the value of 1 is also assigned as 2 because how many cards are matched is not checked in the event of stacked pair
    //i.e, 1 or 2 as this would make no difference in the logic of the function playcardfromstockpile
    playCardFromHand(cardsOnLayout,stackedPairIndex);

   

}


void HUMANHELPER::playCardFromHand(vector<vector< Card*> > &cardsOnLayout, int &stackedPairIndex){
    //ALGORITHM FOR COMPUTER  (HOW TO PLAY FROM HAND)

    //stores num of card matched and returns in the end 
    int numCardsMatchedOnLayout;

    //create a hash map of vectors that contains the face value and the number of cards with that face value on the layout 
    map<string, int> layoutCardFrequencyMapper;

    //iterate through the layout and store frequency on the map 
    for(vector<Card*> i : cardsOnLayout) {
        //need to check with the first card on each vector inside the outer vector
        //because all the cards on vector of cards is going to be of the same face
        //Matches only with single cards ( does not contain stack pair and triple stack )
        if(i.size() == 1){
            Card* cardOnLayoutToMatch = i.at(0);
            auto result = layoutCardFrequencyMapper.insert(std::pair<std::string, int>(cardOnLayoutToMatch->getFace(),1));
            if(result.second == false){
                result.first->second++;
            }
        
        }
    }   

    

    //get each card from the hand and match it with the key of the hash map
            //if match check if the value is 3 
            //if the value is three capture that card and you are done with play from hand

            //if does not match check another card

    //stores index of card to be played
    int cardToPlayIndex = -1;

    string faceCardHand;
    int frequencyCard= 0;
    for(int i=0; i<cardsOnHand.size();i++){
        faceCardHand = cardsOnHand.at(i)->getFace();

        //if map contains the card
        if(layoutCardFrequencyMapper.count(faceCardHand) == 1){
            //get the value of that card and check if it is 3
            frequencyCard = layoutCardFrequencyMapper.at(faceCardHand);

            //if three then return 
            if(frequencyCard >= 3){
                cardToPlayIndex = i;
                break;
            }

        }
        


    }//end of for loop

    

    vector<int> matches;
    string faceCardChosen;
    int numCardsMatched = 0;
    int numErasedCards ;
    string faceValue;
    vector<Card*> capturePileVector;
    int vectorIndexLayout;
    vector<Card*> innerVector;



    //check if cardToPlayIndex is -1 or sth else. if it is something else then we have a card 
    //matched from hand with 3 cards from the layout
    if(cardToPlayIndex!= -1){


        //HELPER BOT MESSAGE PRINT HERE WITH IF STATEMENT FOR CAPTURING THREE CARD WITH THE SUGGESTION ***********************************
        cout<<"I recommend you play "<<cardsOnHand.at(cardToPlayIndex)->getFace()<<" of "<<cardsOnHand.at(cardToPlayIndex)->getSuit()<<
        "from you hand to capture a triple stack or 3 cards from the layout"<<endl;
                

    }else{
                //create a hash map of capture value and the number of cards on it as a key //the value of each key can be either 2 or 4
            //if the value of num of cards is 4 ignore
            //else if it is 2 then check if you have any card on your hand with that value
                //if you do check that value on the layout. if it exist create a stack pair with that value 
                //if there are no face card with the keys of hash map of capture value then continue


            //create a hash map of vectors that contains the face value and the number of cards with that face value on the layout 
            map<string, int> capturePileCardFrequencyMapper;
            //INDEX VECTOR CONTAINS POSSIBLE CARD TO BE PLAYED FROM HAND THAT HAS A CORRESPONDING CARD WITH SAME FACE VALUE AND FREQUENCY 2 ON CAPTURE PILE
            vector<int> indexVectorHand;
            //iterate over computer capture pile and store the frequency of occurences of the card faces value
            for (Card* eachCard : cardsOnCapturePile)
            {
                auto result = capturePileCardFrequencyMapper.insert(std::pair<std::string, int>(eachCard->getFace(), 1));
                if (result.second == false)
                    result.first->second++;
            }


            for(int i=0; i<cardsOnHand.size();i++){
                faceCardHand = cardsOnHand.at(i)->getFace();

                //if map contains the card
                if(capturePileCardFrequencyMapper.count(faceCardHand) == 1){
                    //get the value of that card and check if it is 2
                    frequencyCard = capturePileCardFrequencyMapper.at(faceCardHand);

                    //if frequence is 4 do nothing

                    //if frequency is 2 then capture that card
                    if(frequencyCard == 2){
                        indexVectorHand.push_back(i);
                        
                    }

                }
                
            }//end of for loop

            //loop through the layout vector
                //loop through the indexVectorHand if there is a match 
                //set the value of variable cardToPlayIndex to that index
                //break
            for( int i=0; i<cardsOnLayout.size();i++) {
                
                if(cardsOnLayout.at(i).size() == 1){
                    Card* cardOnLayoutToMatch = cardsOnLayout.at(i).at(0);
                    for(int j=0;j<indexVectorHand.size();j++){
                        if(cardOnLayoutToMatch->getFace() == cardsOnHand.at(indexVectorHand.at(j))->getFace()){
                            cardToPlayIndex = indexVectorHand.at(j);
                            vectorIndexLayout = i;
                            //break if you get a match
                            break;
                        }
                    }
                
                
                }
            }   
            cout<<"\tThe card To Play Index from indexVectorHand given is "<<cardToPlayIndex<<endl;


            //check if cardToPlay index is != -1 then play that card and set pairedindex card value as well
            if(cardToPlayIndex != -1){  


                //HELPER BOT MESSAGE PRINT HERE WITH IF STATEMENT FOR CREATING STACK PAIR OF CARD WITH A PAIR ON CAPTURE PILE***********************************
                cout<<"I recommend you play "<<cardsOnHand.at(cardToPlayIndex)->getFace()<<" of "<<cardsOnHand.at(cardToPlayIndex)->getSuit()<<
                "from you hand to create a stack pair that matches with a pair of cards on your capture pile"<<endl;

                


            }else{
                //handle another case here
                //check if any card on the layout matches any card on hand 
                    //loop through cards on layout and card on hand and if there is a match then store it in a vector
                    //display the cards that computer can choose from
                    //choose one of the cards
                vector<int> optionToChoseIndex;
                //if it does create a stack pair 
                for(int i=0; i<cardsOnLayout.size();i++){
                    
                    if(cardsOnLayout.at(i).size() == 1){
                        //inner for loop for cards on hand
                        for(int j=0; j<cardsOnHand.size();j++){

                           
                            if(cardsOnLayout.at(i).at(0)->getFace() == cardsOnHand.at(j)->getFace()){
                                //face card on layout at index i is same as on hand at index j
                                cardToPlayIndex = j;
                                vectorIndexLayout = i;
                                //break if you get a match on cards 
                                break;
                            }
                        }

                    }//end of if statement

                    
                }//end of for loop

                if(cardToPlayIndex != -1){

                   cout<<"I recommend you play "<<cardsOnHand.at(cardToPlayIndex)->getFace()<<" of "<<cardsOnHand.at(cardToPlayIndex)->getSuit()<<
                "from you hand to create a stack pair. You do not have any card on the capture pile matches with the stack pair that is recommended"<<endl;
                    //HELPER BOT MESSAGE PRINT HERE WITH IF STATEMENT FOR CREATING STACK PAIR BUT NO MATCH IN CAPTURE PILE***********************************



                }else {

                    //HELPER BOT MESSAGE PRINT HERE WITH IF STATEMENT FOR ADDING CARD ON LAYOUT BECAUSE THERE IS NO MATCH ***********************************
                    cout<<"You can play any card from your hand. There is no card that matches on your hand and on the layout"<<endl;
                    
                }

            }
                
    }


    //return the number of card matched
    return;


    
}

