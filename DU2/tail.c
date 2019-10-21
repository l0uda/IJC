  // tail.c
  // Řešení IJC-DU2, příklad 1)a), 25.4.2019
  // Autor: Ludek Burda, FIT
  // Přeloženo: gcc 7.4.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <ctype.h>

#define LIMIT 1025 // limit znaku na radek
#define DEFAULT 10 // implicitni pocet poslednich radku k tisknuti
#define OCERROR 1 // error pripady
#define ARGERROR 2 //
#define ALLERROR 3 //
// zkontrolovat chovani pro prekroceni limitu u radku

int ERROR(int code,int ks,FILE *s){
  switch(code){
    case OCERROR:
      fprintf(stderr,"Nepodarilo se otevrit/zavrit soubor.\n");
      return 0;

    case ARGERROR:
      fprintf(stderr,"Nespravne zadany argument.\n");
      return 0;

    case ALLERROR:
      fprintf(stderr,"Alokace se nezdarila.\n");
      return 0;
  }
  if (ks) if(fclose(s)==EOF) exit(ERROR(OCERROR,0,0));
  return 0;
}

int main(int argc, char* argv[]){
  argc++; // ffs
  char **text; // promenna pro nacteni textoveho souboru
  char temp[LIMIT] = ""; // pomocna promena pro nacteni radku
  FILE *soubor;
  int n = DEFAULT; // implicitni pocet poslednich radku k tisknuti
  int ln = 0; // pocitadlo pro pocet radku
  int i = 0; //
  int j = 0;
  int ks = 0; // boolean zda je prilozen soubor
  int ps = 1; // boolean pro prekroceni delky radku

  if(argv[1]){
    if(!strcmp(argv[1],"-n")){  // spousteni s argumentem -n
      assert(argv[2]);
      if (argv[2][0] != '+' && !isdigit(argv[2][0])) exit(ERROR(ARGERROR,ks,0)); // kontrola spravnosti argumentu
      for (unsigned int j = 1; j < strlen(argv[2]); j++) assert(isdigit(argv[2][j])); //
      n = atoi(argv[2]);

      if (argv[3]){ // pripad kdy je potreba otevrit
        if ((soubor = fopen(argv[3],"r")) == NULL) exit(ERROR(OCERROR,ks,0));
        ks = 1;
      }
    }
    else { // spousteni bez argumentu -n
      if ((soubor = fopen(argv[1],"r")) == NULL) exit(ERROR(OCERROR,ks,0));
      ks = 1;
    }
  }
  if (ks) { // nacitani textu pokud je prilozen soubor
    for (char c = getc(soubor); c != EOF; c = getc(soubor)) if (c == '\n') ln++; // zjisteni poctu radku
    rewind(soubor);

    if((text = calloc(ln,sizeof(char *))) == NULL) exit(ERROR(ALLERROR,ks,soubor));

    while(fgets(temp,LIMIT,soubor) != NULL){
      if((text[i] = calloc(LIMIT,sizeof(char))) == NULL) exit(ERROR(ALLERROR,ks,soubor));
      strcpy(text[i],temp);
      if(text[i][LIMIT-2] != '\0' && text[i][LIMIT-2] != '\n') {
        while (fgetc(soubor) != '\n');
        if (ps) {
          fprintf(stderr, "%s\n\n", "Prekroceni limitu znaku na radek.");
          ps = 0;
        }
        text[i][LIMIT-2] = '\n';
        text[i][LIMIT-1] = '\0';
      }
      i++;
    }
  }
  else {
    if ((text = malloc(LIMIT*sizeof(char*))) == NULL) exit(ERROR(ALLERROR,ks,0));
    while (fgets(temp,LIMIT,stdin) != NULL){
      if((text[i] = calloc(LIMIT,sizeof(char))) == NULL) exit(ERROR(OCERROR,ks,soubor));
      strcpy(text[i],temp);
      if(text[i][LIMIT-2] != '\0' && text[i][LIMIT-2] != '\n') {
        while (fgetc(stdin) != '\n');
        if (ps) {
          fprintf(stderr, "%s\n\n", "Prekroceni limitu znaku na radek.");
          ps = 0;
        }
        text[i][LIMIT-2] = '\n';
        text[i][LIMIT-1] = '\0';
      }
    i++;
    }
  }

  if (argv[1]){
    if(!strcmp(argv[1],"-n")) { // varianta vypisu s argumenty -n N
      if (n>i) exit(ERROR(ARGERROR,ks,soubor));
      if(argv[2][0] == '+') j = n; // varianta -n +N
      else j = i-n;
    }
    else goto smrcka;
  }
  else{ // uprava promenne pomocne k tisku
    smrcka:
    if(i>9) j = i-10;
    else j = 0;
  }

  for (; j < i; j++) printf("%s",text[j]); // vypisovani

  if (ks){ // uvolneni alokovane pameti, uzavreni souboru
    for (i = 0; i < ln; i++) free(text[i]);
    free(text);
    if(fclose(soubor)==EOF) exit(ERROR(OCERROR,0,0));
  }
  else { // uvloneni alokovane pameti
    for (ln = 0; ln < i; ln++) free(text[ln]);
    free(text);
  }
  return 0;
}

// printf("debug\n");
