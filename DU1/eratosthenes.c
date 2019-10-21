#include <stdio.h>
#include <math.h>
#include "bit_array.h"
#include "eratosthenes.h"

void Eratosthenes(bit_array_t pole){
  //nulovani
  bit_array_setbit(pole,0,1);
  bit_array_setbit(pole,1,1);
  unsigned long N = bit_array_size(pole);
  unsigned long i = 2;
  while (i<=sqrt(N)){
    if(bit_array_getbit(pole,i)==0){
      for(unsigned long n = 2; n*i<N; n++){
        bit_array_setbit(pole,n*i,1);
      }
    }
    i++;
  }
}
