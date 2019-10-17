#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv){
  if(argc!=2){
    fprintf(stderr,"Not enough arguments\n");
    return EXIT_FAILURE;
  }
  
  char * filename = argv[1];
  FILE *fptr = fopen(filename, "r");

  if (fptr == NULL){
    fprintf(stderr,"File not found\n");
    return EXIT_FAILURE;
  }

  char ch;

  int arr[26] = {0};
  while((ch=fgetc(fptr))!=EOF){  
    if(isalpha(ch))
      arr[(int)(ch-'a')]++;
  }

  // find the character with highest frequency
  int max_pos = 0;
  for(int i=1; i<26; i++){
    if(arr[i]> arr[max_pos])
      max_pos = i;
  }

  int val =  max_pos + 'a' - 'e';

  if(val<0)
    val+= 26;

  fprintf(stdout, "%d\n", val);

  if(fclose(fptr)!=0)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
