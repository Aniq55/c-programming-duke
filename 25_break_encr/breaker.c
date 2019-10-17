#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  char * filename = argv[1];

  FILE *fptr = fopen(filename, "r");

  if (fptr == NULL){
    printf("File %s not found", filename);
    return EXIT_FAILURE;
  }

  char ch;

  int arr[26] = {0};
  while (ch != EOF){  
    ch = fgetc(fptr);
    arr[(int) (ch-'a')]++;
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
