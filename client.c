//Paochoua Yang
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#define BUFFER_SIZE 1024

typedef struct card{ 
	char value[3]; 
	char suit[2];
} card;

void sort(card* input, int size){ 
	int i, j; 
	card key;
	int key_int; 
	int j_int; 
	for(i = 1; i < size; ++i){ 
		key = input[i]; 
		j = i - 1; 
		
		//determine key_int
		if(strcmp(key.value, "A") == 0){
                	key_int = 14;
            	}
           	else if(strcmp(key.value, "K") == 0){ 
			key_int = 13;
            	}
            	else if(strcmp(key.value, "Q") == 0){ 
			key_int = 12;
            	}
            	else if(strcmp(key.value, "J") == 0){ 
			key_int = 11;
		}
             	else{ 
			key_int = atoi(key.value);
            	}
		
		//determine j_int
		if(strcmp(input[j].value, "A")== 0){
                        j_int = 14;
                }
                else if(strcmp(input[j].value, "K") == 0){
                        j_int = 13;
                }
                else if(strcmp(input[j].value, "Q") == 0){
                        j_int = 12;
                }
                else if(strcmp(input[j].value, "J") == 0){
                        j_int = 11;
                }
                else{
                        j_int = atoi(input[j].value);
                }
		
		 
		while (j >= 0 && j_int > key_int){ 
			input[j + 1] = input[j];
			j = j - 1;
			//determine new j_int
			if(strcmp(input[j].value, "A")== 0){
        	                j_int = 14;
	                }
                	else if(strcmp(input[j].value, "K") == 0){
                	        j_int = 13;
                	}
                	else if(strcmp(input[j].value, "Q") == 0){
                	        j_int = 12;
                	}
                	else if(strcmp(input[j].value, "J") == 0){
                	        j_int = 11;
                	}
                	else{
                	        j_int = atoi(input[j].value);
                	}

		}
                	
		input[j + 1] = key;
	}
}

int value_to_int(const char* value){
	if(strcmp(value, "A") == 0){
		return 14;
        }
        else if(strcmp(value, "K") == 0){
        	return 13;
        }
        else if(strcmp(value, "Q") == 0){
                return 12;
        }
        else if(strcmp(value, "J") == 0){
                return 11;
        }
        else{
                return atoi(value);
        }

}

int main(int args, char* argv[]){
//	char buffer[BUFFER_SIZE];
	card* deck = malloc(52 * sizeof(card)); 
	char answer[5] = "yes"; 
	int player_chips = 100; 
	card* player_hand = malloc(4 * sizeof(card)); 
	int bet;
	int hands_played = 0;
	int won = 0;
	int lost = 0;
	int final_amount; 
	while((strcmp("yes", answer) == 0 || strcmp("y", answer) == 0) && player_chips > 0){
		int s0 = socket(AF_UNIX, SOCK_STREAM, 0); 
		if(s0 == -1){ 
			printf("Socket creation failed\n"); 
			exit(1);
		}
		struct sockaddr name0 = {AF_UNIX, "Player"}; 
		socklen_t namelen0 = sizeof(struct sockaddr) + 7; 
		bind(s0, &name0, namelen0);
	
		struct sockaddr server_name = {AF_UNIX, "Poker"}; 
		socklen_t server_len = sizeof(struct sockaddr) + 6;
	
	
		if(connect(s0, &server_name, server_len) == -1){ 
			printf("connection failed\n"); exit(1);
		}
	
		read(s0, deck, 52*sizeof(card));

//-------------------------Poker Game --------------------------------------
		int top_card_ind = 51; 
		while(top_card_ind >= 3 && (strcmp("yes", answer) == 0 || strcmp("y", answer) == 0) &&
				player_chips > 0){
			do{
                                printf("\nPlace your bet (you have %d chips): ", player_chips);
                                scanf("%d", &bet);
                        } while(!(bet <= player_chips && bet > 0));


			//Deal hand
			for(int i = 0; i < 4; ++i){ 
				player_hand[i] = deck[top_card_ind]; 
				--top_card_ind;
			}
			++hands_played;
			printf("\n");

			//Sort Hand
			sort(player_hand, 4);
			
			//Hand after sorted
			printf("\n\nYour hand: ");
			
			for(int i = 0; i < 4; ++i){
                                printf("%s", player_hand[i].value);
                                printf("%s ", player_hand[i].suit);
                        }
			printf("\n");
			
			//Using hashmap to find triples
			int hash_map[20];
                        int triples = -1;
			int pairs = -1;
			int single_pair = -1;
			

			for(int i = 0; i < 20; ++i){
				hash_map[i] = 0;
			}
                        for(int i = 0; i < 4; ++i){
				int int_value = value_to_int(player_hand[i].value);
                                int hash_index = int_value % 20;
				hash_map[hash_index] = hash_map[hash_index] + 1;
                        }
                        for(int i = 0; i < 20; ++i){
                                if(hash_map[i] == 3){
                                        triples = 0;
                        	}
			}
			//Find two pairs
			for(int i = 0; i < 20; ++i){
				if(hash_map[i] == 2 && i < 3){
					for(int j = i + 1; j < 20; ++j){
						if(hash_map[j] == 2){
							pairs = 0;
						}
					}
				}
			}
			//Find one pair
			for(int i = 0; i < 20; ++i){
				if(hash_map[i] == 2){
					single_pair = 0;
				}
			}

			printf("\n");


			//Four of a kind
			if(strcmp(player_hand[0].value, player_hand[1].value) == 0 && 
				strcmp(player_hand[1].value, player_hand[2].value)== 0 && 
				strcmp(player_hand[2].value, player_hand[3].value) == 0)
			{ 
				printf("\n4 of a Kind!! You win: %d chips!\n", 20825 * bet + bet);
				player_chips = player_chips + 20825 * bet + bet;
				++won;
			}
			//Straight flush
			else if(strcmp(player_hand[0].suit, player_hand[1].suit) == 0 &&
				strcmp(player_hand[1].suit, player_hand[2].suit) == 0 &&
				strcmp(player_hand[2].suit, player_hand[3].suit) == 0 &&
				value_to_int(player_hand[0].value) + 1 == value_to_int(player_hand[1].value) &&
				value_to_int(player_hand[1].value) + 1 == value_to_int(player_hand[2].value) &&
				value_to_int(player_hand[2].value) + 1 == value_to_int(player_hand[3].value))
			{
				//win 6153x
				printf("\nStraight Flush!! You win: %d chips!\n", 6152 * bet + bet);
				player_chips = player_chips + 6152 * bet + bet;
				++won;
			}
			//Three of a kind
			else if(triples == 0){
				//win 108x
				printf("\nThree of a kind!! You win: %d chips!\n", 108 * bet + bet);
				player_chips = player_chips + 108 * bet + bet;
				++won;
			}
			//Straight
			else if(value_to_int(player_hand[0].value) + 1 == value_to_int(player_hand[1].value) &&
                                value_to_int(player_hand[1].value) + 1 == value_to_int(player_hand[2].value) &&
                                value_to_int(player_hand[2].value) + 1 == value_to_int(player_hand[3].value))
			{
				//win 98
				printf("\nYou got a Straight! You win: %d chips!\n", 98 * bet + bet);
				player_chips = player_chips + 98 * bet + bet;
				++won;
			}
			//Two Pairs
			else if(pairs == 0){
				//win 96x
				printf("\nTwo Pairs!! You win %d chips!\n", 96 * bet + bet);
				player_chips = player_chips + 96 * bet + bet;
				++won;
			}
			//Flush
			else if(strcmp(player_hand[0].suit, player_hand[1].suit) == 0 &&
                                strcmp(player_hand[1].suit, player_hand[2].suit) == 0 &&
                                strcmp(player_hand[2].suit, player_hand[3].suit) == 0)
			{
				//win 96x
				printf("\nFlush!! You win %d chips!\n", 96 * bet + bet);
                                player_chips = player_chips + 96 * bet + bet;
				++won;

			}
			//One Pair
			else if(single_pair == 0){
				//win 3x
				printf("\nOne Pair!! You win %d chips!\n", 3 * bet + bet);
                                player_chips = player_chips + 3 * bet + bet;
				++won;
			}
			else{
				//lose bet
				printf("\nSorry, you got nothing\n");
				player_chips = player_chips - bet;
				++lost; 
			}
			if(player_chips <= 0){
				printf("\n\nYou are out of chips. Game Over.\n\n");
				break;
			}
			do{
				printf("\nrequest another game? (yes/no): ");
        	                scanf("%s", &answer);
	                        printf("\n");

			}while(!(strcmp("yes", answer) == 0 || strcmp("no", answer) == 0 ||
					strcmp("y", answer) == 0 || strcmp("n", answer) == 0));
		}
		
//--------------------------------------------------------------------------
	}
	printf("\n\nThanks for playing.\n");
	printf("\nYou played %d hands, won %d, and lost %d.\n", hands_played, won, lost);
	printf("Your final bank roll is: %d chips\n\n\n\n", player_chips);
	unlink("Player"); 
	unlink("Poker"); 
	return 0;
}

