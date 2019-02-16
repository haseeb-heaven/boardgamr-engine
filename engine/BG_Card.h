#ifndef BG_CARD_H
#define BG_CARD_H

#define USE_MISC_MODULE
#include "BG_Misc.h"

/*Card public methods.*/

/*Draw deck methods.*/
void BG_DrawDeck(Card *);
void BG_DrawDeckSuit(Card *,int);
void BG_DrawDeckSuits(Card *,int*);
void BG_DrawCard(Card*,int);
void BG_DrawCards(Card*,int,int);

/*Get deck methods.*/
void BG_GetDeck(Card *);
void BG_GetHalfDeck(Card *);
void BG_GetFullDeck(Card *);
void BG_GetRandDeck(Card *,int);

/*Add cards methods.*/
bool BG_AddCard(Card *,Card,size_t);
bool BG_AddCards(Card *,Card *,size_t *);
bool BG_AddCardsAt(Card *in_cards,Card *,int,int);

/*Remove cards methods.*/
bool BG_RemoveCard(Card *,int);
bool BG_RemoveCards(Card *,int,size_t *);
bool BG_RemoveCardsFrom(Card *,int,int);

/*Copy/Move cards methods.*/
bool BG_CopyCards(Card*,Card*,int);
bool BG_MoveCards(Card*,Card*,int);

/*Shuffle deck method.*/
void BG_ShuffleDeck(Card *);

/*Misc cards method.*/
size_t BG_GetCardLen(Card *);

/*Card private methods.*/
void InitSuit(char *,int);
void InitDeck(char *,int *,char *,char *,int *,int *,size_t);
int IsValidDeck(Card*);
void CopyCardBuf(Card *,size_t,char *,int *,int);
void AllocDeck(char **,char*,int);
void DeAllocDeck(char **);
void DrawDeckLine(char *,int* ,int,Card*);
void DrawDeck(char *,int*,int,Card*);

#endif // BG_CARD_H
