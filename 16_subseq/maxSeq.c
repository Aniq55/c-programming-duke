#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n){
  size_t len = 0;
  for(size_t i=0; i<n; i++){
    size_t temp_size = 0;
    for(size_t j = i; j<n-1; j++){
      if(array[j]<array[j+1])
	temp_size++;
      else{
	if(temp_size > len)
	  len = temp_size;
	i = j+1;
	break;
      }
    }
  }

  return len;
}
