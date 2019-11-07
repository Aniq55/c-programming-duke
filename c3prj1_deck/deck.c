#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void print_hand(deck_t * hand){
  for(size_t i=0; i<hand->n_cards; i++){
    card_t card = **(hand->cards+i);
    print_card(card);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  for(size_t i=0; i<d->n_cards; i++){
    card_t card = **((d->cards)+i);
    if(card.value==c.value && card.suit==c.suit){
      return 1;
    }
  }

  return 0;
}

void shuffle(deck_t * d){
  card_t ** cards = d->cards;
  card_t *temp;
  size_t n = d->n_cards;
  int rand;
  for(size_t i=0; i<n/2; i++){
    rand = random()%(n);
    temp = cards[i];
    cards[i] = cards[rand];
    cards[rand] = temp;
  }
}

void assert_full_deck(deck_t * d) {
  card_t ** card = d->cards;
  int cnt;
  card_t c;
  for(size_t i=0; i<d->n_cards; i++){
    c = **(card+i);
    cnt = 0;
    for(size_t j=0; j<d->n_cards; j++){
      if(c.value==(**(card+j)).value && c.suit == (**(card+j)).suit) cnt++;
    }
    assert(cnt==1);
  }
}

void add_card_to(deck_t * deck, card_t c){
  //allocate memory
  card_t * c1 = malloc(sizeof(*c1));
  //assign value and suit
  c1->value = c.value;
  c1->suit = c.suit;
  //realloc
  deck->cards = realloc(deck->cards, (deck->n_cards+1)*sizeof(*deck->cards));
  //assign last pointer
  deck->cards[deck->n_cards] = c1;
  //increase n_cards by 1
  deck->n_cards++;
}

card_t * add_empty_card(deck_t * deck){
  card_t * c = malloc(sizeof(*c));
  c->value = 0;
  c->suit = 0;

  //add the empty and assign pointer
  deck->cards = realloc(deck->cards, (deck->n_cards+1)*sizeof(*deck->cards));
  deck->cards[deck->n_cards] = c;
  deck->n_cards++;
  return c;
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  deck_t * deck = malloc(sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards = 0;
  for(unsigned i=0; i<52; i++){
    card_t c = card_from_num(i);
    if(!deck_contains(excluded_cards,c)) add_card_to(deck, c);
  }
  return deck;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
  //deck on the table
  deck_t * deck = malloc(sizeof(*deck));
  deck->n_cards = 0;
  deck->cards = NULL;

  //get all hands
  for(size_t i=0; i<n_hands; i++){
    for(int x=0; x<hands[i]->n_cards; x++){
      deck->cards = realloc(deck->cards, (deck->n_cards+1)*sizeof(*deck->cards));
      deck->cards[deck->n_cards] = hands[i]->cards[x];
      deck->n_cards++;
    }
  }

  //build deck from remaining cards
  deck_t * deck2 = make_deck_exclude(deck);
  free(deck->cards);
  free(deck);
  return deck2;
}

void free_deck(deck_t * deck){
  for(int i=0; i<deck->n_cards;i++){
    free(deck->cards[i]);
  }
  //free cards and deck
  free(deck->cards);
  free(deck);
}
