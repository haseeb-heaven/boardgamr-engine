#define USE_CARD_MODULE

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#include "..\engine\BoardGamr.h"
#else
#include "../engine/BoardGamr.h"
#endif

int main(void)
{
    BG_EnableLogs();
    Card my_card = {'J',SPADES_SUIT};
    size_t my_card_pos = 2;

    Card my_cards[] = {{'A',SPADES_SUIT},{'2',SPADES_SUIT},{'Q',SPADES_SUIT},{'K',SPADES_SUIT},{'\0',0}};
    size_t my_cards_pos[] = {2,7,5,3};
    size_t rmv_cards_pos[] = {6,7,9,10};
    Card add_cards[] = {{'8',SPADES_SUIT},{'6',SPADES_SUIT},{'\0',0}};

    Card deck_1[FULL_DECK] = {'\0',NUL};
    Card deck_2[FULL_DECK] = {'\0',NUL};
    int suits[FULL_DECK] = {NUL};
    char in_cards[FULL_DECK+1] = {'\0'};

    BG_GetDeck(deck_1);
    BG_GetHalfDeck(deck_2);

    puts("Deck of cards-1");
    BG_DrawDeck(deck_1);

    puts("Deck of cards-2");
    BG_DrawDeck(deck_2);

    BG_AddCard(deck_1,my_card,my_card_pos);
    puts("After adding 1 card at 2nd pos to deck_1");
    BG_DrawDeck(deck_1);

    BG_AddCards(deck_1,my_cards,my_cards_pos);
    puts("After adding 4 cards at positions 2,3,5,7 to deck_1");
    BG_DrawDeck(deck_1);

    BG_AddCardsAt(deck_1,add_cards,NUL,FRONT_SIDE);
    puts("After adding 2 cards at front to deck_1");
    BG_DrawDeck(deck_1);

    BG_RemoveCardsFrom(deck_1,5,REAR_SIDE);
    puts("After removing 5 cards from rear to deck_1");
    BG_DrawDeck(deck_1);

    BG_RemoveCardsFrom(deck_1,2,FRONT_SIDE);
    puts("After removing first 2 cards from front to deck_1");
    BG_DrawDeck(deck_1);

    BG_RemoveCards(deck_1,4,rmv_cards_pos);
    puts("After removing 4 cards from positions 6,7,9,10 to deck_1");
    BG_DrawDeck(deck_1);

    BG_CopyCards(&my_card,deck_2,1);
    puts("After copying 1 card to deck_2");
    BG_DrawDeck(deck_2);

    BG_MoveCards(deck_1,deck_2,2);
    puts("After moving 2 cards from deck_1 to deck_2");
    BG_DrawDeck(deck_2);

    puts("Deck_1");
    BG_DrawDeck(deck_1);
    return 0;
}
