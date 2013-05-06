#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

struct elem {
  wchar_t *name;
  unsigned int value;
  bool init;
  elem* suiv;
};

class Hashtable {
private :
  elem* tab[26*2];

public :
  Hashtable() { int i; for(i = 0; i < 26*2; i++) tab[i] = 0; } // initialise la table de hachage.
  
  elem* Add(wchar_t *n); // IMPORTANT : la chaine mise en entrée est supposée non "volatile" : seul Hashtable peut la détruire.

  void File(const char* filename);
  
  ~Hashtable(); // détruit toutes les chaines de caractères et tous les symboles.
};

#endif
