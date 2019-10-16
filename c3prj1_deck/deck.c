#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
#include "cards.h"

void print_hand(deck_t * hand){
  for(int i=0; i< hand->n_cards; i++){
    print_card(*hand->cards[i]);
    if(i< hand->n_cards -1)
      printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  for(int i=0; i< d->n_cards; i++){
    if(( d->cards[i]->suit == c.suit ) && (d->cards[i]->value == c.value))
      return 1;
  }
  return 0;
}

void shuffle(deck_t * d){
  int j,k;
  int n_shuffle = d->n_cards*d->n_cards;
  for(int i=0; i<n_shuffle; i++){
    j = (random()*random()) % d->n_cards;
    k = (random()*random()) % d->n_cards;
    
    card_t *temp=d->cards[j];
    d->cards[j]=d->cards[k];
    d->cards[k]=temp;
  }
}

void assert_full_deck(deck_t * d) {
  unsigned rep[52]={0};
  for(unsigned i=0;i<52;i++){
    if(deck_contains(d,card_from_num(i))){
      rep[i]++;
    }
  }
  for(unsigned i=0;i<52;i++){
    if(rep[i]>1){
      assert(rep[i]>1);
    }
  }
}
