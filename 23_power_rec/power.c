#include <stdio.h>
#include <stdlib.h>

unsigned int  power(unsigned int x, unsigned int y){
  if(x==0){
    if(y==0)
      return 1;
    return 0;
  }

  if(y==0)
    return 1;
  
  if(y==1)
    return x;
  
  return x*power(x, y-1);

}
