#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv){
  if(argc!=2){
    printf("Not enough arguments");
    return EXIT_FAILURE;
  }
  
  char * filename = argv[1];

  FILE *fptr = fopen(filename, "r");

  if (fptr == NULL){
    printf("File not found");
    return EXIT_FAILURE;
  }

  char ch;

  int arr[26] = {0};
  while((ch=fgetc(fptr))!=EOF){  
    if(isalpha(ch))
      arr[(int)(ch-'a')]++;
  }

  fclose(fptr);

  // find the character with highest frequency
  int max_pos = 0;
  for(int i=1; i<26; i++){
    if(arr[i]> arr[max_pos])
      max_pos = i;
  }

  int val =  max_pos + 'a' - 'e';

  if(val<0)
    val *= -1;

  printf("%d\n", val);
  
  return 0;
}
