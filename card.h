typedef struct card{
        char value[3];
        char suit[2];
} card;

void create_deck(card *deck);

void shuffle_deck(card *deck, int repetitions);

void to_string(card* deck, char* deck_string);

