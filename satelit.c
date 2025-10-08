/* RICIU Andrei-Cristian - grupa */

#include "satelit.h"

THeap *AlocaHeap(int nrMax, TFCmp comp) { // functia de alocare memorie heap
  THeap *h = (THeap *)malloc(sizeof(struct Heap));
  if (!h) {
    return NULL;
  }

  h->info = (Tarbore *)malloc(nrMax * sizeof(Tarbore));
  if (!h->info) {
    free(h);
    return NULL;
  }
  h->nrMax = nrMax;
  h->nrElem = 0;
  h->comp = comp;

  return h;
}

void InsertHeap(THeap *h, Tarbore val) { // functia de inserare in min heap

  h->nrElem++;
  h->info[h->nrElem - 1] = val;
  int poz = h->nrElem - 1;
  while (poz > 0 && h->comp(h->info[poz], h->info[(poz - 1) / 2]) == 1) {
    Tarbore aux = h->info[poz];
    h->info[poz] = h->info[(poz - 1) / 2];
    h->info[(poz - 1) / 2] = aux;
    poz = (poz - 1) / 2;
  }
}

Tarbore Extragere(THeap *h) { // functia de extragere din min heap
  Tarbore copy = h->info[0];
  h->info[0] = h->info[h->nrElem - 1];
  h->nrElem--;
  int poz = 0;
  while (poz < h->nrElem - 1 &&
         ((2 * poz + 1 < h->nrElem &&
           h->comp(h->info[poz], h->info[2 * poz + 1]) == 0) ||
          (2 * poz + 2 < h->nrElem &&
           h->comp(h->info[poz], h->info[2 * poz + 2]) == 0))) {
    int new_poz = 2 * poz + 1;
    if (h->comp(h->info[2 * poz + 2], h->info[2 * poz + 1]) == 1) {
      new_poz = 2 * poz + 2;
    }
    Tarbore aux = h->info[new_poz];
    h->info[new_poz] = h->info[poz];
    h->info[poz] = aux;
    poz = new_poz;
  }
  return copy;
}
void DistrugeHeap(THeap **h) { // functia de elibare memorie heap
  free((*h)->info);
  free(*h);
  *h = NULL;
}

Tarbore AlocaArbore(char *nume,
                    int frecventa) { // functia de alocare memorie pentru arbore
  Tarbore arb = (Tarbore)malloc(sizeof(arbore));
  if (!arb)
    return NULL;
  arb->st = NULL;
  arb->dr = NULL;
  arb->info = (Tsatelit)malloc(sizeof(satelit));
  if (!arb->info) {
    free(arb);
    return NULL;
  }
  arb->info->nume = (char *)malloc((strlen(nume) + 1) * sizeof(char));
  if (!arb->info->nume) {
    free(arb->info);
    free(arb);
    return NULL;
  }
  strcpy(arb->info->nume, nume);
  arb->info->frecventa = frecventa;
  return arb;
}

void DistrugeArbore(
    Tarbore *radacina) { // functia de eliberare memorie pentru arbore
  Tarbore *aux = radacina;
  if ((*radacina)->dr)
    DistrugeArbore(&(*radacina)->dr);
  if ((*radacina)->st)
    DistrugeArbore(&(*radacina)->st);
  free((*aux)->info->nume);
  free((*aux)->info);
  free(*aux);
  *aux = NULL;
}

int comp(Tarbore a,
         Tarbore b) { // functia de comparatie pentru elementele din min heap
  if (a->info->frecventa == b->info->frecventa)
    return strcmp(a->info->nume, b->info->nume) < 0;
  return a->info->frecventa < b->info->frecventa;
}

Tcoada AlocaCoada() { // functia de alocare memorie pentru coada folosita
                      // ulterior in functia AfiseazaArbore
  Tcoada c = (Tcoada)malloc(sizeof(Coada));
  if (!c)
    return NULL;
  c->info = NULL;
  c->next = NULL;
  return c;
}
Tcoada InsertCoada(Tcoada c, Tarbore arb) { // functia de inserare in coada
  Tcoada aux = c;
  if (!c) {
    c = (Tcoada)malloc(sizeof(Coada));
    c->next = NULL;
    c->info = arb;
    return c;
  } else {
    while (c->next)
      c = c->next;
    Tcoada aux = (Tcoada)malloc(sizeof(Coada));
    aux->info = arb;
    aux->next = NULL;
    c->next = aux;
  }
  return aux;
}
Tarbore ExtrCoada(Tcoada *c) { // functia de extragere din coada
  if (!(*c)->info)
    return NULL;
  else {
    Tcoada aux = *c;
    *c = (*c)->next;
    Tarbore arb = aux->info;
    aux->info = NULL;
    aux->next = NULL;
    free(aux);
    return arb;
  }
}

void DistrugeCoada(Tcoada *coada) { // functia de eliberare memorie coada
  while (*coada) {
    Tcoada aux = *coada;
    (*coada) = (*coada)->next;
    free(aux);
  }
}

void AfiseazaArbore(Tarbore arb,
                    FILE *out) { // functia de afisare pe nivele a arborelui
  Tcoada queue = NULL;
  char s[15] = "delim\0";
  Tarbore delim = AlocaArbore(s, -1);
  queue = InsertCoada(queue, arb);
  queue = InsertCoada(queue, delim);
  while (queue) {
    Tarbore ex = ExtrCoada(&queue);
    if (ex->info->frecventa != delim->info->frecventa) {
      fprintf(out, "%d-%s", ex->info->frecventa, ex->info->nume);
      if (ex->st)
        queue = InsertCoada(queue, ex->st);
      if (ex->dr)
        queue = InsertCoada(queue, ex->dr);
      if (queue->info->info->frecventa != delim->info->frecventa)
        fprintf(out, " ");
    } else {
      fprintf(out, "\n");
      if (!queue)
        break;
      InsertCoada(queue, delim);
    }
  }
  free(delim->info->nume);
  free(delim->info);
  free(delim);
}

void c2(FILE *out, Tarbore radacina,
        char buffer[1000]) { // functia pentru cerinta 2

  Tarbore aux = radacina;
  size_t i = 0;

  while (i < strlen(buffer)) {
    if (buffer[i] == '0') {
      if (aux->st) {
        aux = aux->st;
        i++;
      } else {
        if (!aux->dr)
          fprintf(out, "%s ", aux->info->nume);
        aux = radacina;
      }
    } else {
      if (aux->dr) {
        aux = aux->dr;
        i++;
      } else {
        if (!aux->st)
          fprintf(out, "%s ", aux->info->nume);
        aux = radacina;
      }
    }
  }
  if (!aux->dr && !aux->st)
    fprintf(out, "%s", aux->info->nume);
  fprintf(out, "\n");
}
int find_path(Tarbore current, char *node, char **path, int *n,
              char direction) { // functia de codificare a path-ului
  if (!current)
    return 0;
  (*n)++;
  if ((*n) > 0)
    (*path) = (char *)realloc(*path, ((*n) + 1) * sizeof(int));
  if (!path)
    return 0;
  (*path)[(*n) - 1] = direction;
  (*path)[(*n)] = '\0';
  if (strcmp(current->info->nume, node) == 0)
    return 1;
  int st = find_path(current->st, node, path, n, '0');
  int dr = find_path(current->dr, node, path, n, '1');
  if (st || dr)
    return 1;
  (*n)--;
  return 0;
}
void LCA(Tarbore radacina, char buffer[100][100], int n,
         FILE *out) { // functia de gasire a lowest common ancestor

  char *path_a = (char *)malloc(sizeof(char));
  int *a = (int *)calloc(1, sizeof(int));
  int len = 0;
  find_path(radacina, buffer[0], &path_a, a, '0');
  for (int i = 1; i < n; i++) {
    char *path_b = (char *)malloc(sizeof(char));
    int *b = (int *)calloc(1, sizeof(int));
    find_path(radacina, buffer[i], &path_b, b, '0');
    for (int j = 1; j < *a && j < *b; j++)
      if (path_a[j] != path_b[j]) {
        len = j;
        break;
      }
    free(path_b);
    free(b);
    *a = len;
  }
  for (int i = 1; i < len; i++)
    if (path_a[i] == '0')
      radacina = radacina->st;
    else
      radacina = radacina->dr;
  fprintf(out, "%s\n", radacina->info->nume);
  free(path_a);
  free(a);
}
