# Tema 2 - Structuri de Date si Algoritmi

## Structuri Utilizate

### 1. Structura Satelit
- Reprezinta informatia unui nod din arbore
- Contine frecventa si numele satelitului

### 2. Structura Arbore
- Reprezinta nodul din arborele binar
- Contine informatiile satelitului si pointeri catre copiii stang si drept

### 3. Structura Heap
- Implementeaza un min-heap
- nrMax: capacitatea maxima
- nrElem: numarul curent de elemente
- info: vector de pointeri la noduri de arbore
- comp: functie de comparare pentru heap

### 4. Structura Coada
- Folosita pentru parcurgerea pe nivele a arborelui
- Implementata ca lista simplu inlantuita

### Functii Heap
- AlocaHeap: aloca memorie pentru structura heap
- InsertHeap: insereaza un nou element in heap
- Extragere: extrage minimul din heap
- DistrugeHeap: elibereaza memoria alocata pentru heap

### Functii Arbore
- AlocaArbore: creeaza un nou nod de arbore
- AfiseazaArbore: afiseaza arborele pe niveluri
- DistrugeArbore: elibereaza memoria alocata pentru arbore

### Cerinta 1
    Cerinta 1 este implementata prin functia AfiseazaArbore. Aceasta realizeaza afisarea arborelui pe nivele, cu ajutorul unei cozi, folosind un algoritm de tip BFS(breadth first search).

### Cerinta 2
    Cerinta 2 este implementata prin functia c2 care primeste cate o codificare si parcurge graful pana se ajunge la nodurile cautate.

### Cerinta 3
    Cerinta 3 este implementata prin functia find_path. Aceasta retine codificarea drumului intr-un vector de caractere alocat dinamic. Functia realizeaza o parcurgere DFS(depth first search) prin metoda recursiva si salveaza calea in vector.

### Cerinta 4
    Cerinta 4 este implementata prin functia LCA. Aceasta implementeaza un algoritm de tip Lowest Common Ancestor care realizeaza cautarea primului nod comun al mai multor noduri primite ca parametru. Folosind functia de la cerinta anterioara find path se afla calea pentru fiecare nod si se compara 2 cate 2, pastrand mereu partea comuna.

Punctajul obtinut la teste este : 95p