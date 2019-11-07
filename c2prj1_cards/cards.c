#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(c.value>=2 && c.value<=VALUE_ACE);
  assert(c.suit>=SPADES && c.suit<=CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  switch(r){
  case STRAIGHT_FLUSH: return "STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND";
  case FULL_HOUSE: return "FULL_HOUSE";
  case FLUSH: return "FLUSH";
  case STRAIGHT: return "STRAIGHT";
  case THREE_OF_A_KIND: return "THREE_OF_A_KIND";
  case TWO_PAIR: return "TWO_PAIR";
  case PAIR: return "PAIR";
  default: return "NOTHING";
  }
}

char value_letter(card_t c) {

  char x = '?';
  if((c.value>=2)&&(c.value<=9)){
    x = '0'+c.value;
  }
  else{
    switch(c.value){
    case 10: {x='0'; break;}
    case VALUE_JACK: {x='J'; break;}
    case VALUE_QUEEN:{x='Q'; break;}
    case VALUE_KING: {x='K'; break;}
    case VALUE_ACE:  {x='A'; break;}
    default: break;
    }
  }

  return x;
}


char suit_letter(card_t c) {

  char x = '?';
  switch(c.suit){
  case SPADES: {x='s'; break;}
  case HEARTS: {x='h'; break;}
  case DIAMONDS: {x='d'; break;}
  case CLUBS: {x='c'; break;}
  default: {x='N'; break;}
  }
  return x;
}

void print_card(card_t c) {
  printf("%c%c", value_letter(c), suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t ans;

  //card value assignment
  switch(value_let){
  case 'A': {ans.value=14; break;}
  case 'K': {ans.value=13; break;}
  case 'Q': {ans.value=12; break;}
  case 'J': {ans.value=11; break;}
  case '0': {ans.value=10; break;}
  default:  {ans.value=value_let-'0'; break;}
  }

  //card suit assignment
  switch(suit_let){
  case 's': {ans.suit = SPADES; break;}
  case 'h': {ans.suit = HEARTS; break;}
  case 'd': {ans.suit = DIAMONDS; break;}
  case 'c': {ans.suit = CLUBS; break;}
  }

  return ans;
}

card_t card_from_num(unsigned c) {
  card_t ans;
  unsigned value = c%13+2;
  unsigned suit = c/13;

  ans.value = value;

  //assignment suit
  switch(suit){
  case 0: {ans.suit = SPADES; break;}
  case 1: {ans.suit = HEARTS; break;}
  case 2: {ans.suit = DIAMONDS; break;}
  case 3: {ans.suit = CLUBS; break;}
  default: {ans.suit = NUM_SUITS; break;}
  }

  return ans;
}
