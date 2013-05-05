#include "hashtable.hpp"
#define NULL 0

inline bool neq(const wchar_t *a, const wchar_t *b) { // = (a != b) dans l'ordre lexicographique.
  int i = 0;

  while ((a[i] == b[i]) && (a[i] != 0)) i++;

  return (a[i] != b[i]);
}

inline bool inf(const wchar_t *a, const wchar_t *b) { // = (a < b) dans l'ordre lexicographique.
  int i = 0;

  while ((a[i] == b[i]) && (a[i] != 0)) i++;

  return (a[i] < b[i]);
}

elem* Hashtable::Add(const wchar_t *n) {
  int t = n[0];
  elem *e,*f,*g;

  if (t > L'Z') t += 26-L'a'; else t -= L'A';

  e = tab[t];
  f = NULL;
  while (e != NULL) {
    if (inf(n, e->name)) break;
    f = e;
    e = f->suiv;
  }

  g = new elem;
  g->name = n;
  g->value = 0;
  g->init = false;
  g->suiv = e;
  
  if (f == NULL) {
    tab[t] = g; // cas où la pile est vide
  }
  else if (neq(f->name, n)) { // cas standard
    f->suiv = g;
  }
  else {
    //delete[] g->name;
    delete g; // cas où l'élément existe déjà.
    g = f;
  }

  return g;
}

Hashtable::~Hashtable() {
  int i;
  elem *e,*f;
  
  for (i = 0; i < 26*2; i++) {
    e = tab[i];
    while (e != NULL) {
      f = e->suiv;
      //delete[] e->name;
      delete e;
      e = f;
    }
  }
}