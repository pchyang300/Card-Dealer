//Paochoua Yang

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <string.h>
#include "card.h"
#define BUFFER_SIZE 1024

void ctrlc();


int main(int args, char* argv[]){
	int j = 0;
	card* deck = malloc(52 * sizeof(card));	
	char buffer[BUFFER_SIZE];

	int s1 = socket(AF_UNIX, SOCK_STREAM, 0);
	int s2;
	if(s1 == -1){
		printf("create socket failed\n");
		exit(1);
	}

	struct sockaddr name1 = {AF_UNIX, "Poker"};
        socklen_t namelen1 = sizeof(struct sockaddr) + 6;
        bind(s1, &name1, namelen1);

	void ctrlc()
                {
                        close(s1);
			close(s2);
			unlink("Poker");
                        unlink("Game");
                        printf("\nProgram stopped\n");
			exit(0);
                }
                //Variables inside ctrlc() must not be declared beyond this$
                struct sigaction close;
                close.sa_handler = ctrlc;
                close.sa_flags = 0;
                sigaction(SIGINT, &close, NULL);


                struct sockaddr name1_0;
                socklen_t namelen1_0;

	
	while (j == 0){
		if(listen(s1, 1) == -1){
        	        printf("listen() failed\n");
			exit(1);
        	}
		printf("listening... \n");

		struct sockaddr name1_0;  
		socklen_t namelen1_0; 
	
		
		if((s2 = accept(s1, &name1_0, &namelen1_0)) == -1){
			printf("accept fail\n");
			exit(1);
		}
		else{
		
			printf("request accepted\n");
//			memset(buffer, 0, sizeof(buffer));

			create_deck(deck);
			shuffle_deck(deck, 100);
		//	to_string(deck, buffer);

		//	write(s2, buffer, strlen(buffer) + 1);
			write(s2, deck, 52 * sizeof(card));
		}	
	}
	
	return 0;
}
