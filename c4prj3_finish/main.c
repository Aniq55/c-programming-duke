#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

int get_best_hand_idx(deck_t ** decks, int n_hands){
  int tmp[n_hands+1];
  for(int i=0; i<n_hands+1; i++) tmp[i] = 0;
  int com;
  for(int i=0; i<n_hands-1; i++){
    for(int j=i+1; j<n_hands; j++){
      com = compare_hands(decks[i], decks[j]);
      if(com>0) tmp[i]++;
      else if (com<0) tmp[j]++;
      else tmp[n_hands]++;
    }
  }
  unsigned best = 0;
  for(int i=0; i<n_hands+1; i++){
    if(tmp[i] > tmp[best]) best = i;
  }
  int count = 0;
  if(tmp[n_hands]>0){
    for(int i=0; i<n_hands+1; i++){
      if(tmp[i]== tmp[best]) count++;
    }
  }
  if(count>1) return n_hands;
  return best;
}


int main(int argc, char ** argv) {

  //check cml argument
  if(argc < 2){
    fprintf(stderr, "Invalid arguement\n");
    return EXIT_FAILURE;
  }

  //Open and read file
  FILE * f = fopen(argv[1], "r");
  if(f==NULL){
    fprintf(stderr, "Could not open file\n");
    return EXIT_FAILURE;
  }

  deck_t ** decks = NULL;
  size_t n_hands = 0;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;
  decks = read_input(f, &n_hands, fc);

  //create a deck with the remaining cards
  deck_t * remains = build_remaining_deck(decks, n_hands);
  int win_hands[n_hands+1];
  for(int i=0; i<n_hands+1; i++) win_hands[i] = 0;

  int n_trials = 10000;

  if(argc==3) n_trials = atoi(argv[2]);
  for(int i=0; i<n_trials; i++){
    shuffle(remains);
    future_cards_from_deck(remains, fc);
    int win_idx = get_best_hand_idx(decks, n_hands);
    win_hands[win_idx]++;
  }

  //print result
  for(size_t i=0; i<n_hands; i++){
    printf("Hand %zu won %u / %u times (%.2f%%)\n",
	   i, win_hands[i], n_trials, (((float)win_hands[i])/n_trials)*100);
  }
  printf("And there were %u ties\n", win_hands[n_hands]);

  //free memories
  for(int i=0; i<n_hands; i++){
    free_deck(decks[i]);
  }
  free(decks);
  for(int i=fc->n_decks-1; i>=0;  i--){
    if(fc->decks[i].n_cards!=0) free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);
  free_deck(remains);


  //close file
  if(fclose(f)!=0){
    fprintf(stderr, "Could not close file");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
