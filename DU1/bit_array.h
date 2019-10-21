#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#ifndef bit_array_h
  #define bit_array_h
  typedef unsigned long bit_array_t[];
  #define bit_array_create(jmeno_pole,velikost)\
    _Static_assert(velikost>0,"Velikost musi byt vetsi nez 0.");\
    unsigned long jmeno_pole[1+velikost/(sizeof(unsigned long)*__CHAR_BIT__)+(velikost%(sizeof(unsigned long)*__CHAR_BIT__)>0 ? 1 : 0)] = {velikost, 0}

  #define bit_array_alloc(jmeno_pole,velikost)\
    _Static_assert(velikost>0,"Velikost musi byt vetsi nez 0.");\
    unsigned long *jmeno_pole = (unsigned long *)malloc((velikost%(__CHAR_BIT__*sizeof(unsigned long))==0)?((velikost/(__CHAR_BIT__*sizeof(unsigned long)))+1)*sizeof(unsigned long):((velikost/(__CHAR_BIT__*sizeof(unsigned long)))+2)*sizeof(unsigned long));\
    if (jmeno_pole == NULL) fprintf(stderr,"%s","bit_array_alloc: Chyba alokace paměti");\
    memset(jmeno_pole,0,(velikost%(sizeof(unsigned long)*__CHAR_BIT__)==0)?((velikost/(sizeof(unsigned long)*__CHAR_BIT__))+1)*sizeof(unsigned long):((velikost/(sizeof(unsigned long)*__CHAR_BIT__))+2)*sizeof(unsigned long));\
    jmeno_pole[0] = velikost


  #ifdef USE_INLINE
    inline void bit_array_free(unsigned long* jmeno_pole){
      if(!jmeno_pole)fprintf(stderr,"%s","Pole neexistuje.");
      free(jmeno_pole);
    }

  #else
    #define bit_array_free(jmeno_pole)\
      free(jmeno_pole);
  #endif


  #ifdef USE_INLINE
    inline unsigned long bit_array_size(unsigned long *jmeno_pole){
      if(!jmeno_pole) fprintf(stderr,"%s","Pole neexistuje.");
      return jmeno_pole[0];
    }

  #else
    #define bit_array_size(jmeno_pole)\
      (unsigned long)(jmeno_pole[0] ? jmeno_pole[0] : 0)
  #endif


  #ifdef USE_INLINE
    inline void bit_array_setbit(unsigned long *jmeno_pole,unsigned long index,unsigned long vyraz){
      if(!jmeno_pole) fprintf(stderr,"%s","Pole neexistuje.");
      if(index>=bit_array_size(jmeno_pole)) fprintf(stderr,"%s","Index neni v ramci pole.");
      if(vyraz) jmeno_pole[1 + index/ (sizeof(unsigned long) * __CHAR_BIT__) ] |= 1UL << (index % (sizeof(unsigned long)*__CHAR_BIT__));
      else jmeno_pole[1 + index/ (sizeof(unsigned long) * __CHAR_BIT__) ] &= ~(1UL << (index % (sizeof(unsigned long)*__CHAR_BIT__)));
    }

  #else
    #define bit_array_setbit(jmeno_pole,index,vyraz)\
    if(index>=bit_array_size(jmeno_pole)) fprintf(stderr,"%s","Index neni v ramci pole.");\
    do\
    {\
        if(vyraz) jmeno_pole[1+index/(sizeof(unsigned long)*__CHAR_BIT__)] |= 1UL<<(index%(sizeof(unsigned long)*__CHAR_BIT__));\
        else jmeno_pole[1+index/(sizeof(unsigned long)*__CHAR_BIT__)] &= ~(1UL<<(index % (sizeof(unsigned long)*__CHAR_BIT__)));\
    }\
    while(0)
  #endif


  #ifdef USE_INLINE
    inline unsigned long bit_array_getbit(unsigned long *jmeno_pole, unsigned long index){
      if(!jmeno_pole)fprintf(stderr,"%s","Pole neexistuje.");
      if(index>jmeno_pole[0])fprintf(stderr,"%s","Index neni v ramci pole.");
      return (unsigned long)((jmeno_pole[index/(sizeof(*jmeno_pole)*__CHAR_BIT__) + 1] & ((unsigned long)1 << (index%(sizeof(*jmeno_pole)*__CHAR_BIT__))) ) > 0);
    }

  #else
    #define bit_array_getbit(jmeno_pole,index)\
    (unsigned long)((jmeno_pole[index/(sizeof(*jmeno_pole)*__CHAR_BIT__) + 1] & ((unsigned long)1 << (index%(sizeof(*jmeno_pole)*__CHAR_BIT__))) ) > 0)

  #endif
#endif
