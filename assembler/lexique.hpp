#ifndef LEXIQUE_HPP
#define LEXIQUE_HPP

#include "enum.hpp"
#include "lecture.hpp"
#include "symbole.hpp"

class UniLex {
private :
  static Lecture *fichier;

  unsigned int line;
  unsigned int column;
  unsigned int id;
  unsigned int idbis;
  Symbole symb; // symbole;

  void Point(); // lit .DATA, .BSS ou .CODE
  void Automate(wchar_t c); // lit INSTR, REGISTRE, ID
  void Nbr(); // lit un nombre

public :
  Unilex() {} // crée une unité lexicale vide.

  void Read(); // lit l'unité lexicale suivante.

  unsigned int getLine() { return line; }
  unsigned int getColumn() { return column; }
  unsigned int getId() { return id; }
  unsigned int getIdbis() { return idbis; }
  Symbole GetSymb() { return symb; }

  static void SetFichier(Lecture *f) { fichier = f; }
};

#endif
