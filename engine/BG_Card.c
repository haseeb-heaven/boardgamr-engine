#include "BG_Card.h"

/******************************************************************
******************PUBLIC-METHODS*****************************
*******************************************************************/

/**
 * @description - Draw the given cards deck with suit.
 * @param - in_cards : Deck of cards to draw on screen.
 */

void BG_DrawDeck(Card *in_cards)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tin_cards : %p\n",BG_FUNC,in_cards);
    }

    int in_suits[FULL_DECK] = {0};
    char in_faces[FULL_DECK+1] = {'\0'};
    CopyCardBuf(in_cards,FULL_DECK,in_faces,in_suits,COPY_TO);

    DrawDeck(in_faces,in_suits,FULL_DECK,in_cards);

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}

/**
 * @description - Draw the given cards deck with provided suit.
 * @param -
 * in_cards : Deck of cards to draw on screen.
 * in_suits : Suit for input deck.
 */

void BG_DrawDeckSuit(Card *in_cards,int in_suit)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        char *in_suit_str = (in_suit == CLUB_SUIT) ? "CLUB_SUIT" : (in_suit == DIAMOND_SUIT) ? "DIAMOND_SUIT" :  (in_suit == HEARTS_SUIT) ? "HEARTS_SUIT" : (in_suit == SPADES_SUIT) ? "SPADES_SUIT" : "UNKNOWN_SUIT";
        AddLog("%s -> called with arguments\tin_cards : %p\tin_suit : %s\n",BG_FUNC,in_cards,in_suit_str);
    }

    char in_faces[FULL_DECK+1] = {'\0'};
    CopyCardBuf(in_cards,FULL_DECK,in_faces,NULL,COPY_TO);
    size_t in_faces_len = (in_faces != NULL) ? strlen(in_faces) : NUL;

    if(in_faces_len > DECK_FACES)
    {
        ShowError("%s -> ERROR : \"Only pair of 13 cards of same suit must be provided to draw. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return;
    }
    DrawDeck(in_faces,&in_suit,1,in_cards);

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}

/**
 * @description - Draw the given cards deck with provided suits (multiple suit).
 * @param -
 * in_cards : Deck of cards to draw on screen.
 * in_suits : Suits for input deck.(Must provide same suit for every 13 card)
 * and (Length of  in_cards == Length of in_suits) should be True.
 */

void BG_DrawDeckSuits(Card *in_cards,int* in_suits)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tin_cards : %p\tin_suits : %p\n",BG_FUNC,in_cards,in_suits);
    }

    char in_faces[FULL_DECK+1] = {'\0'};
    CopyCardBuf(in_cards,FULL_DECK,in_faces,NULL,COPY_TO);
    size_t in_faces_len = (in_faces != NULL) ? strlen(in_faces) : NUL;

    DrawDeck(in_faces,in_suits,in_faces_len,in_cards);

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}

/**
 * @description - Draw card from position.
 * @param -
 * in_cards : Deck of cards.
 * card_pos : Position of card.
 * draw_cards : Number of cards to draw from given deck.
 */

void BG_DrawCard(Card* in_cards,int card_pos)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tin_cards : %p\tcard_pos : %p\n",BG_FUNC,in_cards,card_pos);
    }

    Card tmp_card[2] = {{'\0',0}};
    int in_cards_len = BG_GetCardLen(in_cards);
    SetPrivateAccess(TRUE);

    if(card_pos <= in_cards_len)
    {
        tmp_card[0].face = in_cards[card_pos].face;
        tmp_card[0].suit = in_cards[card_pos].suit;
        BG_DrawDeck(tmp_card);
        SetPrivateAccess(TRUE);
    }

    else
    {
        ShowError("%s -> ERROR : \"Trying to draw card from '%d' position from deck of '%d' cards. Occurred at line no : %d\"\n",BG_FUNC,card_pos,in_cards_len,BG_LINE);
    }
    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}

/**
 * @description - Draw number of cards from deck.
 * @param -
 * in_cards : Deck of cards.
 * card_pos : Position of card.
 * draw_cards : Number of cards to draw from given deck.
 */

void BG_DrawCards(Card* in_cards,int card_pos,int draw_cards)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tin_cards : %p\tcard_pos : %d\tdraw_cards : %d\n",BG_FUNC,in_cards,card_pos,draw_cards);
    }

    Card tmp_card[draw_cards+1];
    int nul = NUL,in_cards_len = BG_GetCardLen(in_cards);
    SetPrivateAccess(TRUE);
    BG_FillArray(tmp_card,draw_cards+1,sizeof(Card),&nul,STRUCT_TYPE);
    SetPrivateAccess(TRUE);

    if(draw_cards <= in_cards_len)
    {
        memcpy(tmp_card,&in_cards[card_pos],draw_cards*sizeof(Card));
        BG_DrawDeck(tmp_card);
        SetPrivateAccess(TRUE);
    }

    else
    {
        ShowError("%s -> ERROR : \"Trying to draw '%d' cards from deck of '%d' cards. Occurred at line no : %d\"\n",BG_FUNC,draw_cards,in_cards_len,BG_LINE);
    }

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}

/**
 * @description - Get Full deck of cards with all suits.
* @param - in_cards : Buffer to receive deck of cards.
* Must be of length 'FULL_DECK' with one extra space for NULL.
 */

void BG_GetFullDeck(Card *in_cards)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tin_cards : %p\n",BG_FUNC,in_cards);
    }

    char in_faces[FULL_DECK+1]= {'\0'};
    int in_suits[FULL_DECK] = {0};

    int index,deck_counter = 0;
    char deck_1[HALF_DECK] = {'\0'};
    char deck_2[HALF_DECK] = {'\0'};

    int suits_1[HALF_DECK] = {0};
    int suits_2[HALF_DECK] = {0};

    CopyCardBuf(in_cards,FULL_DECK,in_faces,in_suits,COPY_TO);
    InitDeck(in_faces,in_suits,deck_1,deck_2,suits_1,suits_2,HALF_DECK);
    CopyCardBuf(in_cards,FULL_DECK,in_faces,in_suits,COPY_FROM);

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}


/**
 * @description - Get Half deck of cards with half suits.
 * @param - in_cards : Buffer to receive deck of cards.
 * Must be of length 'HALF_DECK' with one extra space for NULL.
 */

void BG_GetHalfDeck(Card *in_cards)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tin_cards : %p\n",BG_FUNC,in_cards);
    }

    int deck_counter = 0;

    char in_faces[HALF_DECK+1]= {'\0'};
    int in_suits[HALF_DECK] = {0};

    char deck_1[QUARTER_DECK] = {'\0'};
    char deck_2[QUARTER_DECK] = {'\0'};

    int suits_1[QUARTER_DECK] = {0};
    int suits_2[QUARTER_DECK] = {0};

    CopyCardBuf(in_cards,HALF_DECK,in_faces,in_suits,COPY_TO);
    InitDeck(in_faces,in_suits,deck_1,deck_2,suits_1,suits_2,QUARTER_DECK);
    CopyCardBuf(in_cards,HALF_DECK,in_faces,in_suits,COPY_FROM);

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}


/**
 * @description - Get a deck of cards with suits.
 * @param - in_cards : Buffer to receive deck of cards.
 * Must be of length 'QUARTER_DECK' with one extra space for NULL.
 */

void BG_GetDeck(Card *in_cards)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tin_cards : %p\n",BG_FUNC,in_cards);
    }

    static int deck_count = 0;

    /*Error checking for method invoking limit.*/
    if(deck_count >= DECK_SUITS)
    {
        ShowError("%s -> ERROR : \"%s method must not be invoked more than %d times in single session. Occurred at line no : %d\"\n",BG_FUNC,BG_FUNC,DECK_SUITS,BG_LINE);
        return;
    }

    /*Error checking for in_cards/suit.*/
    else if(in_cards == NULL)
    {
        ShowError("%s -> ERROR : \"Input cards or suit is empty. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return;
    }

    int index = 0;
    if(in_cards != NULL)
    {
        for(index = 0; index < DECK_FACES; ++index)
        {
            in_cards[index].face = card_face[index];
            in_cards[index].suit = card_suit[deck_count];
        }
    }

    deck_count++;

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with deck_count : %d\n",BG_FUNC,deck_count);
    }
    SetPrivateAccess(FALSE);
}

/**
* @description - Get random cards deck with same suit for all cards.
* @param -
* in_cards : Buffer to receive random deck of cards. Must be of length 'deck_type' selected with one extra space for NULL.
* deck_type : Type of deck . Use Enum DECK_TYPE to provide value.
*/

void BG_GetRandDeck(Card *in_cards,int deck_type)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tin_cards : %p\tdeck_type : %d\n",BG_FUNC,in_cards,deck_type);
    }

    switch(deck_type)
    {
    case QUARTER_DECK :
        BG_GetDeck(in_cards);
        break;

    case HALF_DECK :
        BG_GetHalfDeck(in_cards);
        break;

    case FULL_DECK :
        BG_GetFullDeck(in_cards);
        break;

    default :
        ShowError("%s -> ERROR : \"Invalid deck type selected. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return;
    }
    SetPrivateAccess(TRUE);
    BG_ShuffleDeck(in_cards);

    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}


/**
 * @description - Shuffle the cards deck.
 * @param - deck : Cards deck to shuffle.
 */
void BG_ShuffleDeck(Card *in_cards)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tin_cards : %p\n",BG_FUNC,in_cards);
    }

    size_t in_faces_len = BG_GetCardLen(in_cards);
    SetPrivateAccess(TRUE);

    int index, deck_rand,suit_temp;
    char face_temp;

    if(in_cards == NULL)
    {
        ShowError("%s -> ERROR : \"Input cards is empty. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return;
    }

    for (index = in_faces_len-1; index > 0; index--)
    {
        deck_rand = rand()%(index+1);
        face_temp = in_cards[deck_rand].face;
        suit_temp = in_cards[deck_rand].suit;

        in_cards[deck_rand].face = in_cards[index].face;
        in_cards[deck_rand].suit = in_cards[index].suit;

        in_cards[index].face = face_temp;
        in_cards[index].suit = suit_temp;
    }

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}

/**
 * @description - Add single card to deck.
 * @param -
 * in_cards : Deck of cards.
 * in_card :   Card to add on deck.
 * card_pos : Position where to add card.
  * @return - TRUE if card was added otherwise FALSE.
 */

bool BG_AddCard(Card *in_cards,Card in_card,size_t card_pos)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tin_cards : %p\tin_card : %p\tcard_pos : %u\n",BG_FUNC,in_cards,in_card,card_pos);
    }

    int in_suits[FULL_DECK] = {0};
    char in_faces[FULL_DECK+1] = {'\0'};
    CopyCardBuf(in_cards,FULL_DECK,in_faces,in_suits,COPY_TO);

    bool add_status = FALSE;
    size_t index,in_faces_len = (in_faces != NULL) ? strlen(in_faces) : NUL,move_size = in_faces_len-card_pos;

    /*Convert card to upper case before adding to deck.*/
    in_card.face = toupper(in_card.face);
    Card tmp_card[2] = {in_card,{'\0',0}};

    if(in_cards == NULL)
    {
        ShowError("%s -> ERROR : \"Input deck is empty. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        add_status = FALSE;
    }
    else if (card_pos < 0 || card_pos > in_faces_len)
    {
        ShowError("%s -> ERROR : \"Invalid position '%d' encountered. Occurred at line no : %d\"\n",BG_FUNC,card_pos,BG_LINE);
        add_status = FALSE;
    }
    else if(IsValidDeck(tmp_card) != VALID_DECK)
    {
        ShowError("%s -> ERROR : \"Invalid card '%c' provide to add. Occurred at line no : %d\"\n",BG_FUNC,in_card.face,BG_LINE);
        add_status = FALSE;
    }
    else
    {
        memmove(&in_suits[card_pos+1],&in_suits[card_pos],move_size*sizeof(int));
        memmove(&in_faces[card_pos+1],&in_faces[card_pos],move_size);
        in_faces[card_pos] = in_card.face;
        in_suits[card_pos] = in_card.suit;

        CopyCardBuf(in_cards,FULL_DECK,in_faces,in_suits,COPY_FROM);
        add_status = TRUE;
    }

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,add_status);
    }
    SetPrivateAccess(FALSE);
    return add_status;
}

/**
 * @description - Add multiple cards to deck.
 * @param -
 * in_cards : Deck of cards.
 * in_card :   Cards to add on deck. (Must have one extra space for Null terminating}.
 * card_pos : Positions where to add cards.
  * @return - TRUE if card was added otherwise FALSE.
 */

bool BG_AddCards(Card *in_cards,Card *in_card,size_t *card_pos)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tin_cards : %p\tin_card : %p\tcard_pos : %p\n",BG_FUNC,in_cards,in_card,card_pos);
    }

    bool add_status = FALSE;

    int updated_pos,index,in_faces_len = BG_GetCardLen(in_cards);
    SetPrivateAccess(TRUE);

    int add_cards = BG_GetCardLen(in_card);
    SetPrivateAccess(TRUE);

    if(in_card == NULL || card_pos == NULL)
    {
        ShowError("%s -> ERROR : \"Input cards or position are invalid. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        add_status = FALSE;
    }

    else
    {
        for(index = 0; index < add_cards; ++index)
        {
            if(add_cards <= in_faces_len)
            {
                updated_pos = (index > 0) ? card_pos[index] + 1 : card_pos[index];
                add_status = BG_AddCard(in_cards,in_card[index],updated_pos);
                if(add_status == FALSE)
                    break;
            }
            else
            {
                ShowError("%s -> ERROR : \"Trying to add '%d' cards to deck of '%d' cards. Occurred at line no : %d\"\n",BG_FUNC,add_cards,in_faces_len,BG_LINE);
                add_status = FALSE;
                break;
            }
        }
        SetPrivateAccess(TRUE);
    }

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,add_status);
    }
    SetPrivateAccess(FALSE);
    return add_status;
}

/**
 * @description - Add multiple cards to deck at side.
 * @param -
 * in_cards : Deck of cards.
 * in_card :   Cards to add on deck. (Must have one extra space for Null terminating}.
 * add_cards : Total number of cards to add. (Optional provide NULL if you want to copy all cards).
 * add_side : Side where to add cards at. Use Enum SIDES to provide value.
  * @return - TRUE if card was added otherwise FALSE.
 */

bool BG_AddCardsAt(Card *in_cards,Card *in_card,int add_cards,int add_side)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tin_cards : %p\tin_card : %p\tadd_cards : %d\tadd_side : %d\n",BG_FUNC,in_cards,in_card,add_cards,add_side);
    }

    bool add_status = FALSE;
    size_t add_pos,index,card_pos,in_faces_len = BG_GetCardLen(in_cards);
    SetPrivateAccess(TRUE);

    add_cards = (add_cards == NUL) ? BG_GetCardLen(in_card) : add_cards;
    card_pos = add_cards-1;
    SetPrivateAccess(TRUE);

    for(index = 1; index <= add_cards; ++index)
    {
        if(add_cards <= in_faces_len)
        {
            add_pos = (add_side == FRONT_SIDE) ? 0 : (add_side == REAR_SIDE) ? in_faces_len : BG_ERROR;
            if((add_status = BG_AddCard(in_cards,in_card[card_pos--],add_pos)) == FALSE)
                break;
        }
        else
        {
            ShowError("%s -> ERROR : \"Trying to add '%d' cards to deck of '%d' cards. Occurred at line no : %d\"\n",BG_FUNC,add_cards,in_faces_len,BG_LINE);
            add_status = FALSE;
            break;
        }
    }

    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,add_status);
    }
    SetPrivateAccess(FALSE);
    return add_status;
}

/**
 * @description - Remove single card from deck.
 * @param -
 * in_cards : Deck of cards.
 * card_pos : Position of card to remove from deck.
  * @return - TRUE if card was removed otherwise FALSE.
 */

bool BG_RemoveCard(Card *in_cards,int card_pos)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tin_cards : %p\tcard_pos : %d\n",BG_FUNC,in_cards,card_pos);
    }

    bool rmv_status = FALSE;
    int in_suits[FULL_DECK] = {0};
    char in_faces[FULL_DECK+1] = {'\0'};
    CopyCardBuf(in_cards,FULL_DECK,in_faces,in_suits,COPY_TO);
    int in_faces_len = (in_faces != NULL) ? strlen(in_faces) : NUL,move_size = in_faces_len - card_pos;

    if(in_cards == NULL || in_faces == NULL)
    {
        ShowError("%s -> ERROR : \"Input deck is empty. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        rmv_status = FALSE;
    }
    else if (card_pos < 0 || card_pos > in_faces_len)
    {
        ShowError("%s -> ERROR : \"Invalid position '%d' encountered. Occurred at line no : %d\"\n",BG_FUNC,card_pos,BG_LINE);
        rmv_status = FALSE;
    }
    else
    {
        memmove(&in_faces[card_pos], &in_faces[card_pos + 1],move_size);
        memmove(&in_suits[card_pos], &in_suits[card_pos + 1],move_size * sizeof(int));
        CopyCardBuf(in_cards,FULL_DECK,in_faces,in_suits,COPY_FROM);
        rmv_status = TRUE;
    }

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,rmv_status);
    }
    SetPrivateAccess(FALSE);
    return rmv_status;
}

/**
 * @description - Remove multiple cards from deck positions.
 * @param -
 * in_cards : Deck of cards.
 * rmv_cards : Total number of cards to remove.
 * cards_pos : Positions from where to remove cards.
  * @return - TRUE if card was added otherwise FALSE.
 */

bool BG_RemoveCards(Card *in_cards,int rmv_cards,size_t *cards_pos)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tin_cards : %p\trmv_cards : %d\tcards_pos : %p\n",BG_FUNC,in_cards,rmv_cards,cards_pos);
    }

    bool rmv_status = FALSE;
    int updated_pos,index;
    size_t in_faces_len = BG_GetCardLen(in_cards);
    SetPrivateAccess(TRUE);

    if(in_cards == NULL || cards_pos == NULL)
    {
        ShowError("%s -> ERROR : \"Input cards or position are invalid. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        rmv_status = FALSE;
    }

    else
    {
        for(index = 0; index < rmv_cards; ++index)
        {
            if(rmv_cards <= in_faces_len)
            {
                updated_pos = (index > 0) ? cards_pos[index] - 1 : cards_pos[index];
                rmv_status = BG_RemoveCard(in_cards,updated_pos);
                if(rmv_status == FALSE)
                    break;
            }
            else
            {
                ShowError("%s -> ERROR : \"Trying to remove '%d' cards from deck of '%d' cards. Occurred at line no : %d\"\n",BG_FUNC,rmv_cards,in_faces_len,BG_LINE);
                rmv_status = FALSE;
                break;
            }
        }
        SetPrivateAccess(TRUE);
    }
    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,rmv_status);
    }
    SetPrivateAccess(FALSE);
    return rmv_status;
}

/**
 * @description - Remove multiple cards from deck sides.
 * @param -
 * in_cards : Deck of cards.
 * rmv_cards : Total number of cards to remove from deck.
 * rmv_side : Side from where to remove cards from. Use Enum SIDES to provide value.
  * @return - TRUE if all cards were removed otherwise FALSE.
 */

bool BG_RemoveCardsFrom(Card *in_cards,int rmv_cards,int rmv_side)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tin_cards : %p\trmv_cards : %d\trmv_side : %d\n",BG_FUNC,in_cards,rmv_cards,rmv_side);
    }

    bool rmv_status = FALSE;
    size_t rmv_pos,index,in_faces_len = BG_GetCardLen(in_cards);
    SetPrivateAccess(TRUE);

    for(index = 1; index <= rmv_cards; ++index)
    {
        if(rmv_cards <= in_faces_len)
        {
            rmv_pos = (rmv_side == FRONT_SIDE) ? 0 : (rmv_side == REAR_SIDE) ? (in_faces_len - index) : BG_ERROR;
            if((rmv_status = BG_RemoveCard(in_cards,rmv_pos)) == FALSE)
                break;
        }
        else
        {
            ShowError("%s -> ERROR : \"Trying to remove '%d' cards from deck of '%d' cards. Occurred at line no : %d\"\n",BG_FUNC,rmv_cards,in_faces_len,BG_LINE);
            rmv_status = FALSE;
            break;
        }
    }

    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,rmv_status);
    }
    SetPrivateAccess(FALSE);
    return rmv_status;
}

/**
 * @description - Copy cards from source to destination.
 * @param -
 * src_cards : Deck of cards (Input Source).
 * dest_cards : Deck of cards (Output Destination).
 * copy_cards : Total number of cards to copy from source deck.
  * @return - TRUE if cards were copied otherwise FALSE.
 */

bool BG_CopyCards(Card* src_cards,Card* dest_cards,int copy_cards)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tsrc_cards : %p\tdest_cards : %p\tcopy_cards : %d\n",BG_FUNC,src_cards,dest_cards,copy_cards);
    }

    bool copy_status = FALSE;
    size_t src_len = BG_GetCardLen(src_cards);
    SetPrivateAccess(TRUE);

    if(copy_cards <= src_len)
    {
        BG_AddCardsAt(dest_cards,src_cards,copy_cards,REAR_SIDE);
    }

    else
    {
        ShowError("%s -> ERROR : \"Trying to copy '%d' cards to deck of '%d' cards. Occurred at line no : %d\"\n",BG_FUNC,copy_cards,src_len,BG_LINE);
        copy_status = FALSE;
    }

    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,copy_status);
    }
    SetPrivateAccess(FALSE);
    return copy_status;
}

/**
 * @description - Move cards from source to destination.
 * @param -
 * src_cards : Deck of cards (Input Source).
 * dest_cards : Deck of cards (Output Destination).
 * move_cards : Total number of cards to move from source deck.
  * @return - TRUE if cards were copied otherwise FALSE.
 */

bool BG_MoveCards(Card* src_cards,Card* dest_cards,int move_cards)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tsrc_cards : %p\tdest_cards : %p\tmove_cards : %d\n",BG_FUNC,src_cards,dest_cards,move_cards);
    }

    bool move_status = FALSE;
    size_t src_len = BG_GetCardLen(src_cards);
    SetPrivateAccess(TRUE);

    if(move_cards <= src_len)
    {
        BG_AddCardsAt(dest_cards,src_cards,move_cards,REAR_SIDE);
        SetPrivateAccess(TRUE);

        BG_RemoveCardsFrom(src_cards,move_cards,FRONT_SIDE);
        SetPrivateAccess(TRUE);
    }

    else
    {
        ShowError("%s -> ERROR : \"Trying to move '%d' cards to deck of '%d' cards. Occurred at line no : %d\"\n",BG_FUNC,move_cards,src_len,BG_LINE);
        move_status = FALSE;
    }
    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,move_status);
    }
    SetPrivateAccess(FALSE);
    return move_status;
}

/**
 * @description - Get length of card buffer
 * @param -
 * in_cards : Deck of cards.
  * @return - Length of cards on valid deck otherwise return NUL.
 */
size_t BG_GetCardLen(Card * in_cards)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tin_cards : %p\n",BG_FUNC,in_cards);
    }

    int in_suits[FULL_DECK] = {0};
    char in_faces[FULL_DECK+1] = {'\0'};
    CopyCardBuf(in_cards,FULL_DECK,in_faces,in_suits,COPY_TO);

    size_t card_len = (in_faces != NULL) ? strlen(in_faces) : NUL;

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,card_len);
    }
    SetPrivateAccess(FALSE);
    return card_len;
}

/******************************************************************
******************PRIVATE-METHODS****************************
*******************************************************************/


/*Initialize deck with half or full deck.*/
void InitDeck(char *in_faces,int *in_suits,char *deck_1,char *deck_2,int *suit_1,int *suit_2,size_t deck_sz)
{
    int index,deck_counter = 0;

    /*Error checking for deck/suit.*/
    if(in_faces == NULL || in_suits == NULL)
    {
        ShowError("%s -> ERROR : \"Input deck or suit is empty. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return;
    }

    for(index = 1; index <= 2; ++index)
    {
        char *ptr_face = (index == 1) ? deck_1 : deck_2;
        int *ptr_suit = (index == 1) ? suit_1 : suit_2;

        Card half_cards[HALF_DECK] = {'\0',NUL};
        Card qrtr_cards[QUARTER_DECK] = {'\0',NUL};

        if(deck_sz == HALF_DECK)
        {
            BG_GetHalfDeck(half_cards);
            SetPrivateAccess(TRUE);

            CopyCardBuf(half_cards,HALF_DECK,ptr_face,ptr_suit,COPY_TO);
        }
        else if(deck_sz == QUARTER_DECK)
        {
            BG_GetDeck(qrtr_cards);
            SetPrivateAccess(TRUE);

            CopyCardBuf(qrtr_cards,QUARTER_DECK,ptr_face,ptr_suit,COPY_TO);
        }

        strcpy(in_faces+deck_counter,ptr_face);
        memcpy(in_suits + deck_counter,ptr_suit,deck_sz * sizeof(int));

        deck_counter += deck_sz;
    }
}


/*Draw the deck. it just splits bigger decks and call DrawDeckLine for new lines to fit on screen.*/
void DrawDeck(char *in_faces,int* in_suits,int suit_size,Card *in_cards)
{
    char split_face[DECK_LEN] = {'\0'};
    int split_suit[DECK_LEN] = {NUL};
    size_t in_faces_len = (in_faces != NULL) ? strlen(in_faces) : NUL;
    int split_begin = 0;

    if(in_faces_len > DECK_SPLIT)
    {
        do
        {
            strncpy(split_face,&in_faces[split_begin], DECK_SPLIT);
            memcpy(split_suit,&in_suits[split_begin],DECK_SPLIT*sizeof(int));

            DrawDeckLine(split_face,split_suit,suit_size,in_cards);
            split_begin += DECK_SPLIT;
        }
        while(split_begin <= in_faces_len);
    }
    else
    {
        DrawDeckLine(in_faces,in_suits,suit_size,in_cards);
    }
}

/*Draw deck line. doesn't split the deck.*/
void DrawDeckLine(char *in_faces,int* in_suits,int suit_size,Card *in_cards)
{
    char *deck_buf[BUF_LEN] = {'\0'};
    char suit_buf[DECK_LEN] = {'\0'};
    int row = 0,index = 0,i = 0,col = 0,nul = NUL,in_faces_row;
    bool deck_allocated = FALSE,deck_deallocated = FALSE;
    suit_size *= (suit_size > 1) ? 3 : 1;

    /*Error checking for deck/suit.*/
    if(in_faces == NULL || in_suits == NULL)
    {
        ShowError("%s -> ERROR : \"Input deck or suit is empty. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return;
    }
    size_t in_faces_len = strlen(in_faces);
    int index_arr[in_faces_len];
    BG_FillArray(index_arr,in_faces_len,NUL,&nul,INT_TYPE);
    SetPrivateAccess(TRUE);

    /*Checking for valid deck.*/
    int valid_status = IsValidDeck(in_cards);

    /*Allocate memory for deck suit(s).*/
    if(!deck_allocated)
    {
        AllocDeck(deck_buf,suit_buf,in_suits[0]);
        deck_allocated = TRUE;
    }

    /*Main loop for printing card from template.*/
    if(valid_status == VALID_DECK)
    {
        for(col = 1; col <= CARD_HEIGHT; col++)
        {
            for(row = 0; row < in_faces_len; row++)
            {
                if((row+1) <= suit_size && (col >=3 && col <= 5))
                {
                    /*Deallocate previous deck suits.*/
                    if(deck_allocated && !deck_deallocated && suit_size > 1)
                    {
                        DeAllocDeck(deck_buf);
                        deck_deallocated = TRUE;
                    }

                    /*Allocate new memory for deck suits.*/
                    if(deck_deallocated)
                    {
                        if(col == 5 && row >= 1); /*Only allocate once for col 5 and 6 because they are same for every suit .*/
                        else
                            AllocDeck(deck_buf,suit_buf,in_suits[row]);
                    }
                }
                in_faces_row = in_faces[row];
                for(index =  index_arr[i]; index < strlen(deck_buf[in_faces_row]); index++)
                {
                    if(deck_buf[in_faces_row][index] == CARD_LEN)
                    {
                        index_arr[i++] = index+1;
                        break;
                    }
                    /*Print card on screen using horizontal/row-wise split trick.*/
                    putchar(deck_buf[in_faces_row][index]);
                }
                /*Deallocate new memory deck suits.*/
                if((row+1) <= suit_size && (col >= 3 && col <= 4) && suit_size > 1 )
                {
                    DeAllocDeck(deck_buf);
                }
            }
            i = 0;
            printf("\n");
        }
        /*Deallocate memory for deck suit(s).*/
        if(deck_allocated)
        {
            DeAllocDeck(deck_buf);
        }
    }

    /*Print error messages for invalid deck/suit.*/
    else if(valid_status == INVALID_DECK)
        ShowError("%s -> ERROR : \"Invalid deck '%s' encountered, Check valid deck string. Occurred at line no : %d\"\n",BG_FUNC,in_faces,BG_LINE);

    else if(valid_status == INVALID_SUIT_RANGE)
        ShowError("%s -> ERROR : \"Deck '%s' contains some suits out of range [CLUB_SUIT to SPADES_SUIT]. Occurred at line no : %d\"\n",BG_FUNC,in_faces,BG_LINE);

    else if(valid_status == INVALID_CARD_DUP)
        ShowError("%s -> ERROR : \"Deck '%s' contains some duplicate cards. Occurred at line no : %d\"\n",BG_FUNC,in_faces,BG_LINE);
}

/*Contains templates of all suits with initialization to suit_buf.*/
void InitSuit(char *suit_buf,int in_suit)
{
    if(IsPrivateMethod(BG_FUNC,BG_LINE))
    {
        if(IsLogEnabled())
        {
            char *in_suit_str = (in_suit == CLUB_SUIT) ? "CLUB_SUIT" : (in_suit == DIAMOND_SUIT) ? "DIAMOND_SUIT" :  (in_suit == HEARTS_SUIT) ? "HEARTS_SUIT" : (in_suit == SPADES_SUIT) ? "SPADES_SUIT" : "UNKNOWN_SUIT";
            AddLog("%s -> called with arguments\tsuit_buf : %p\tsuit : %s\n",BG_FUNC,suit_buf,in_suit_str);
        }

        switch(in_suit)
        {
        case CLUB_SUIT : /*CLUB-SUIT TEMPLATE.*/
            strcpy(suit_buf,
                   ".------.\
|%c.--. |\
| :(): |\
| ()() |\
| '--'%c|\
`------'");
            break;

        case DIAMOND_SUIT : /*DIAMOND-SUIT TEMPLATE.*/
            strcpy(suit_buf,
                   ".------.\
|%c.--. |\
| :/\\: |\
| :\\/: |\
| '--'%c|\
`------'");
            break;

        case HEARTS_SUIT : /*HEARTS-SUIT TEMPLATE.*/
            strcpy(suit_buf,
                   ".------.\
|%c.--. |\
| (\\/) |\
| :\\/: |\
| '--'%c|\
`------'");
            break;

        case SPADES_SUIT : /*SPADES-SUIT TEMPLATE.*/
            strcpy(suit_buf,
                   ".------.\
|%c.--. |\
| :/\\: |\
| (__) |\
| '--'%c|\
`------'");
            break;
        }
        if(IsLogEnabled())
        {
            AddLog("%s -> ended successfully\n",BG_FUNC);
        }
    }
}

/*Check for valid deck with duplicates/invalid string/suit range etc */
int IsValidDeck(Card *in_cards)
{
    int valid_status = INVALID_DECK;
    if(IsPrivateMethod(BG_FUNC,BG_LINE))
    {
        if(IsLogEnabled())
        {
            AddLog("%s -> called with arguments\tin_cards : %p\n",BG_FUNC,in_cards);
        }

        char in_face[FULL_DECK+1] = {'\0'};
        CopyCardBuf(in_cards,FULL_DECK,in_face,NULL,COPY_TO);

        int i,j,card_len = (in_face != NULL) ? strlen(in_face) : NUL;
        int card_count = 0;

        /*Check for valid deck string.*/
        if (in_face[strspn(in_face, card_face)] == NUL)
        {
            valid_status = VALID_DECK;

            /*Check for card duplicates/range.*/
            for(i = 0; i < card_len; ++i)
            {
                /*Check for suit range .*/
                if(in_cards[i].suit < CLUB_SUIT || in_cards[i].suit > SPADES_SUIT)
                {
                    valid_status = INVALID_SUIT_RANGE;
                    break;
                }

                for(j = 0; j < card_len; ++j)
                {
                    if(toupper(in_cards[i].face) == toupper(in_cards[j].face)
                            && in_cards[i].suit == in_cards[j].suit)
                    {
                        card_count++;
                    }
                }

                /*Check for card duplicates*/
                if(card_count > 1)
                {
                    valid_status = INVALID_CARD_DUP;
                    break;
                }
                card_count = 0;
            }
        }

        if(IsLogEnabled())
        {
            AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,valid_status);
        }
    }

    return valid_status;
}

/*Copy Cards FROM/TO given buffers.*/
void CopyCardBuf(Card *in_cards,size_t in_cards_len,char *in_faces,int *in_suits,int copy_type)
{
    if(IsPrivateMethod(BG_FUNC,BG_LINE))
    {
        if(IsLogEnabled())
        {
            AddLog("%s -> called with arguments\tin_cards : %p\tin_cards_len : %d\tin_faces : %p\tin_suits : %p\tcopy_type : %d\n",BG_FUNC,in_cards,in_cards_len,in_faces,in_suits,copy_type);
        }

        int index;
        if(in_cards != NULL)
        {
            for(index = 0; index < in_cards_len; ++index)
            {
                if(in_faces != NULL)
                {
                    (copy_type == COPY_TO) ?
                    (in_faces[index] = in_cards[index].face) : (COPY_FROM) ?  (in_cards[index].face = in_faces[index]) : NUL;
                }
                if(in_suits != NULL)
                {
                    (copy_type == COPY_TO) ?
                    (in_suits[index] = in_cards[index].suit) : (COPY_FROM) ?  (in_cards[index].suit = in_suits[index]) : NUL;
                }
            }
        }
        if(IsLogEnabled())
        {
            AddLog("%s -> ended successfully\n",BG_FUNC);
        }
    }
}

/*Allocates memory for deck.*/
void AllocDeck(char **deck_buf,char* suit_buf,int in_suit)
{
    if(IsPrivateMethod(BG_FUNC,BG_LINE))
    {
        if(IsLogEnabled())
        {
            char *in_suit_str = (in_suit == CLUB_SUIT) ? "CLUB_SUIT" : (in_suit == DIAMOND_SUIT) ? "DIAMOND_SUIT" :  (in_suit == HEARTS_SUIT) ? "HEARTS_SUIT" : (in_suit == SPADES_SUIT) ? "SPADES_SUIT" : "UNKNOWN_SUIT";
            AddLog("%s -> called with arguments\tdeck_buf : %p\tsuit_buf : %p\tsuit : %s\n",BG_FUNC,deck_buf,suit_buf,in_suit_str);
        }
        int index,ch;
        InitSuit(suit_buf,in_suit);
        for(index = 0; index < strlen(card_face); ++index)
        {
            ch = card_face[index];
            deck_buf[ch] = malloc(CARD_SIZE);
            sprintf(deck_buf[ch],suit_buf,ch,ch);
        }
        if(IsLogEnabled())
        {
            AddLog("%s -> ended successfully\n",BG_FUNC);
        }
    }
}

/*Deallocates memory for deck.*/
void DeAllocDeck(char **deck_buf)
{
    if(IsPrivateMethod(BG_FUNC,BG_LINE))
    {
        if(IsLogEnabled())
        {
            AddLog("%s -> called with arguments\tdeck_buf : %p\n",BG_FUNC,deck_buf);
        }
        int index,ch;
        for(index = 0; index < strlen(card_face); ++index)
        {
            ch = card_face[index];
            free(deck_buf[ch]);
        }
        if(IsLogEnabled())
        {
            AddLog("%s -> ended successfully\n",BG_FUNC);
        }
    }
}
