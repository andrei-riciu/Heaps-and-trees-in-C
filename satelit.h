/* RICIU Andrei-Cristian - grupa */

#ifndef SATELIT_H
#define SATELIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct satelit {
  int frecventa;
  char *nume;
} satelit, *Tsatelit;
typedef struct arbore {
  Tsatelit info;
  struct arbore *st, *dr;
} arbore, *Tarbore;
typedef int (*TFCmp)(Tarbore a, Tarbore b);

typedef struct Heap {
  int nrMax, nrElem;
  Tarbore *info;
  TFCmp comp;
} THeap;

typedef struct coada {
  Tarbore info;
  struct coada *next;
} Coada, *Tcoada;

typedef struct lista {
  int *info;
  struct lista *next;
} cel, *Tlista;

THeap *AlocaHeap(int nrMax, TFCmp comp);
void DistrugeHeap(THeap **h);
void InsertHeap(THeap *h, Tarbore val);
Tarbore Extragere(THeap *h);
int comp(Tarbore a, Tarbore b);
Tarbore AlocaArbore(char *nume, int frecventa);
void AfiseazaArbore(Tarbore arb, FILE *out);
Tcoada AlocaCoada();
Tcoada InsertCoada(Tcoada c, Tarbore arb);
Tarbore ExtrCoada(Tcoada *c);
void DistrugeCoada(Tcoada *coada);
void DistrugeArbore(Tarbore *radacina);
void DistrugeHeap(THeap **h);
void c2(FILE *out, Tarbore radacina, char buffer[1000]);
int find_path(Tarbore current, char *node, char **path, int *n, char direction);
void LCA(Tarbore radacina, char buffer[100][100], int n, FILE *out);
#endif