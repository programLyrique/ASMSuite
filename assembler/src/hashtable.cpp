#include "hashtable.hpp"
#include <cstdlib>
#include <fstream>
#include <cwchar>
//#define NULL 0

inline bool neq(wchar_t *a, wchar_t *b) { // = (a != b) dans l'ordre lexicographique.
  int i = 0;

  while ((a[i] == b[i]) && (a[i] != 0)) i++;

  return (a[i] != b[i]);
}

inline bool inf(wchar_t *a, wchar_t *b) { // = (a < b) dans l'ordre lexicographique.
  int i = 0;

  while ((a[i] == b[i]) && (a[i] != 0)) i++;

  return (a[i] < b[i]);
}

elem* Hashtable::Add(wchar_t *n) {
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
    delete[] g->name;
    delete g; // cas où l'élément existe déjà.
    g = f;
  }

  return g;
}

Hashtable::~Hashtable() {
  int i;
  elem *e,*f;
  
  File("a.log");
  for (i = 0; i < 26*2; i++) {
    e = tab[i];
    while (e != NULL) {
      f = e->suiv;
      delete[] e->name;
      delete e;
      e = f;
    }
  }
}

void Hashtable::File(const char* file) {
  std::ofstream out;
  elem *e, *f;
  char* c;

  out.open(file, std::ios::out);
  for (int i = 0; i < 26*2; i++) {
    e = tab[i];
    f = NULL;
    while (e != NULL) {
      if (e->init) { // e a une valeur.
	c = new char[wcslen(e->name)+1];
	wcstombs(c, e->name, wcslen(e->name)+1);
	out << c << " " << (e->value) << std::endl;
	delete[] c;
      }
      f = e;
      e = f->suiv;
    }
  }
  out.close();
}
