#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bit_array.h"
#include "eratosthenes.h"

void Print(bit_array_t pole) {
    unsigned int NotPrimes = 10;
    unsigned long N = bit_array_size(pole);

    unsigned long i = N-1;
    while (i > 0 && NotPrimes > 0) {
        if (bit_array_getbit(pole, i) == 0 )
                NotPrimes--;
        i--;
    }
    while (i< N) {
        if (bit_array_getbit(pole, i) == 0 )
            printf("%lu\n", i);
	      i++;
    }

}

int main(){
  bit_array_create(pole,123000000);
  Eratosthenes(pole);
  Print(pole);
  return 0;
}
/*if (jmeno_pole[index/(__CHAR_BIT__*sizeof(unsigned long))+1] & (1 << (index%(__CHAR_BIT__*sizeof(unsigned long))))) return 1;
else return 0;*/
