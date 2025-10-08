/* RICIU Andrei-Cristian - grupa */
#include "satelit.h"
int main(int argc, char *argv[]) {
  if (argc != 4)
    return -1;
  FILE *in = fopen(argv[2], "rt");
  if (!in) {
    printf("fisier prost\n");
    return 1;
  }
  FILE *out = fopen(argv[3], "wt");
  int n;
  THeap *h;
  fscanf(in, "%d\n", &n);
  h = AlocaHeap(n, comp);
  h->comp = comp;
  h->nrElem = 0;
  h->nrMax = n;
  for (int i = 0; i < n; i++) {
    int x;
    fscanf(in, "%d", &x);
    char nume[15];
    fscanf(in, "%s", nume);
    Tarbore arb = AlocaArbore(nume, x);
    InsertHeap(h, arb);
    // fprintf(out,"%d %s\n",arb->info->frecventa,arb->info->nume);
  }
  Tarbore radacina = NULL;
  while (h->nrElem >= 2) {
    Tarbore a = Extragere(h);
    Tarbore b = Extragere(h);
    char nume[1000];
    strcpy(nume, a->info->nume);
    strcat(nume, b->info->nume);
    nume[strlen(nume)] = 0;
    Tarbore legatura =
        AlocaArbore(nume, a->info->frecventa + b->info->frecventa);
    if (comp(a, b) == 1) {
      legatura->st = a;
      legatura->dr = b;
    } else {
      legatura->st = b;
      legatura->dr = a;
    }
    InsertHeap(h, legatura);
    radacina = legatura;
  }
  if (strcmp(argv[1], "-c1") == 0)
    AfiseazaArbore(radacina, out);
  else if (strcmp(argv[1], "-c2") == 0) {
    int n;
    fscanf(in, "%d", &n);
    for (int i = 0; i < n; i++) {
      char buffer[1000];
      fscanf(in, "%s", buffer);
      c2(out, radacina, buffer);
    }
  } else if (strcmp(argv[1], "-c3") == 0) {
    fscanf(in, "%d", &n);
    for (int i = 0; i < n; i++) {
      char buffer[256];
      fscanf(in, "%s", buffer);
      char *path = (char *)calloc(1, sizeof(char));
      int *count = (int *)calloc(1, sizeof(int));
      Tarbore aux = radacina;
      int x = find_path(aux, buffer, &path, count, '0');
      if (x) {
        for (int j = 1; j < *count; j++)
          fprintf(out, "%c", path[j]);
      }
      free(count);
      free(path);
    }
    fprintf(out, "\n");
  } else if (strcmp(argv[1], "-c4") == 0) {
    char buffer[100][100];
    fscanf(in, "%d", &n);
    for (int i = 0; i < n; i++)
      fscanf(in, "%s", buffer[i]);
    LCA(radacina, buffer, n, out);
  }
  DistrugeArbore(&radacina);
  DistrugeHeap(&h);
  fclose(in);
  fclose(out);
  return 0;
}