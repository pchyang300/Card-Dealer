# Card-Dealer
This program was created for a school project that utilizes sockets and is written in C. It 
starts by creating a server named "Poker". The client can connect via socket to the server. Once
a connection is established, the server acts as the card dealer and the client can request 
a hand of 5 cards. When a hand is requested, the server deals 5 cards and sends this to the client.
When the client receives it, the poker hand is analyzed to see what ranking it has. If the player
gets a poker hand ranking, then they win a certain abount of chips plus their original bet back. 

To run the program, run the Makefile to compile server.c and card.c, then run the server. Then compile 
and run client.c to connect and play the poker game. 
