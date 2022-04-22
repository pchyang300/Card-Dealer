//Paochoua Yang

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "card.h"

void create_deck(card* deck){
        for(int i = 0; i < 52; ++i){
                int mod = (i % 13) + 1;
                if(mod == 1){
			strcpy(deck[i].value, "A");
		}
		else if(mod == 11){
                        //deck[i]->value = "J";
			strcpy(deck[i].value, "J");
                }
                else if(mod == 12){
                        strcpy(deck[i].value, "Q");
                }
                else if(mod == 13){
                        strcpy(deck[i].value, "K");
                }
                else{
                        sprintf(deck[i].value, "%d", mod);
                }

                if(i >= 0 && i < 13){
                        strcpy(deck[i].suit, "C");
                }
                else if(i >= 13 && i < 26){
                        strcpy(deck[i].suit, "D");
                }
                else if(i >= 26 && i< 39){
                        strcpy(deck[i].suit, "H");
                }
                else{
                        strcpy(deck[i].suit, "S");
                }
        }
}

void shuffle_deck(card *deck, int repetitions){
	int pick_first;
	int pick_second;
	card tmp;

	for(int i = 0; i < repetitions; ++i){
		pick_first = rand() % 52;
		pick_second = rand() % 52;

		tmp = deck[pick_first];
		deck[pick_first] = deck[pick_second];
		deck[pick_second] = tmp;
	}

}

void to_string(card* deck, char* deck_string){
	for(int i = 0; i < 52; ++i){
		strcpy(deck_string, strcat(deck_string, deck[i].value));
		strcpy(deck_string, strcat(deck_string, deck[i].suit));
		strcpy(deck_string, strcat(deck_string, " "));
	}
}


