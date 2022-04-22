# Card-Dealer
This program was created for a school project that utilizes sockets and is written in C. It 
starts by creating a connection via socket between server (dealer) and client (player). Once
connected, the server acts as the card dealer for which the client can request a poker hand. 
When a hand is requested, the server deals 5 cards and sends this to the client via socket. 
When the client receives it, the poker hand is analyzed to see what ranking it has. If the player
gets a poker hand ranking, then the win a certain abount of chips plus their original bet back. 
