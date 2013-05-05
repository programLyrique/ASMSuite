#ifndef SYMBOLE_HPP
#define SYMBOLE_HPP

#include "hashtable.hpp"

class Symbole {
private :

  static Hashtable hash;
  elem* e;

public :
  Symbole() : e(0) {} // renvoit un symbole vide.
  Symbole(const wchar_t *name); // crée un nouveau symbole, ou renvoie celui pré-existant. name ne DOIT pas être volatile.
  void SetValue(unsigned int n);
  unsigned int GetValue();
  const wchar_t* GetText();
  bool GetInit();

};

#endif
