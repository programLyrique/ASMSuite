#ifndef LEXIQUE_HPP
#define LEXIQUE_HPP

#include <iostream>
#include "enum.hpp"
#include "lecture.hpp"
#include "symbole.hpp"

class UniLex {
private :

  unsigned int line;
  unsigned int column;
  unsigned int id;
  unsigned int idbis;
  Symbole symb; // symbole;

  bool CaracId(wchar_t c); // renvoit true si c est dans A-Z, a-z, 0-9 ou _
  bool CaracFin(wchar_t c);
  void Point(); // lit .DATA, .BSS ou .CODE
  void Nbr(); // lit un nombre
  void Automate(wchar_t c); // lit INSTR, REGISTRE, ID

public :
  UniLex() {} // crée une unité lexicale vide.

  void Read(); // lit l'unité lexicale suivante.

  unsigned int GetLine() { return line; }
  unsigned int GetColumn() { return column; }
  unsigned int GetId() { return id; }
  unsigned int GetIdbis() { return idbis; }
  Symbole GetSymb() { return symb; }

  static void SetFichier(FILE *f);

};

#endif
