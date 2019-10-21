// tail2.cc
// Řešení IJC-DU2, příklad 1)b), 25.4.2019
// Autor: Ludek Burda, FIT
// Přeloženo: g++ 7.4.0

#include <iostream>
#include <queue>
#include <iterator>
#include <string>
#include <cstring>
#include <cassert>

using namespace std;

#define DEFAULT 10 // implicitni pocet poslednich radku k tisknuti
#define OCERROR 1 // error pripady
#define ARGERROR 2 //

int ERROR(int code){
  switch(code){
    case OCERROR:
      fprintf(stderr,"Nepodarilo se otevrit/zavrit soubor.\n");
      return 0;

    case ARGERROR:
      fprintf(stderr,"Nespravne zadany argument.\n");
      return 0;
  }
  return 0;
}

int main(int argc, char* argv[]){
  //ios::sync_with_stdio(false);
  argc++; // ffs
  string s; // promena pro nacitani radku
  queue<string> text; // promenna pro nacteni celeho textu
  int ln = 0; // pocitadlo radku v promenne text
  int n = DEFAULT;
  int i = 0;

  if(argv[1]){
    if(!strcmp(argv[1],"-n")){  // spousteni s argumentem -n
      assert(argv[2]);
      if (argv[2][0] != '+' && !isdigit(argv[2][0])) exit(ERROR(ARGERROR)); // kontrola spravnosti argumentu
      for (unsigned int j = 1; j < strlen(argv[2]); j++) assert(isdigit(argv[2][j])); //
      n = atoi(argv[2]);

      if (argv[3]) // pripad kdy je potreba otevrit
        if ((freopen(argv[3],"r",stdin)) == NULL) exit(ERROR(OCERROR));
    }
    else // spousteni bez argumentu -n
      if ((freopen(argv[1],"r",stdin)) == NULL) exit(ERROR(OCERROR));
  }

  while (getline(cin,s)){ // nacteni textu do promenne typu queue
    text.push(s);
    ln++;
  }

  if (argv[1]){
    if(!strcmp(argv[1],"-n")){ // uprava prommene text
      if(argv[2][0] == '+'){ if (ln<=n) exit(ERROR(ARGERROR));} // varianta -n +N
      else if (ln<10) n = 0;
      else if (ln>n) n = ln-n;
    }
    else if (ln<10) n = 0;
    else if (ln>n) n = ln-n;
  }
  else {
    if (ln>n) n = ln-n;
    if (ln<=10) n = 0;
  }
  for (; i < n; i++) text.pop(); // uprava promenne text k tisku

  while (!text.empty()){ // tisk
    cout << text.front() << endl;
    text.pop();
  }
}
