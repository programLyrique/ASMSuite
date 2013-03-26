#ifndef SYNTAXE_HPP
#define SYNTAXE_HPP

#include "liste.hpp"

class Syntaxe {
private :
  Liste lCode; //liste d'instructions
  unsigned int cCode; // compteur d'instruction, sert à initialiser les labels d'instructions.
  unsigned int cData; // compteur de données, sert à initialiser les labels de données.

public :
  Syntaxe();

  int Read(Lecture *fichier); // fait l'analyse syntaxique du fichier.
};

#endif
