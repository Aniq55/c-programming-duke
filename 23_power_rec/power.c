#include <stdio.h>
#include <stdlib.h>

uint32_t power(uint32_t x, uint32_t y){
  if(x==0)
    return 0;

  if(y==0)
    return 1;
  
  if(y==1)
    return x;
  
  return x*power(x, y-1);

}
