#ifndef SYNTAXE_HPP
#define SYNTAXE_HPP

#include "arbre.hpp"
#include "lexique.hpp"
#include "liste.hpp"
#include <fstream>

class Syntaxe {
private :
  Liste lCode; //liste d'instructions
  Liste *lCurrent; //fin de liste;
  unsigned int cCode; // compteur d'instruction, sert à initialiser les labels d'instructions.
  unsigned int cData; // compteur de données, sert à initialiser les labels de données.

  UniLex lex;
  bool isData; // pour savoir si les expressions acceptent des symboles ou pas.
  bool err; // true s'il y a eu une erreur.

  /*  Arbre *nb(); // fonctions intermédiaires
  Arbre *e();
  Arbre *d();
  Arbre *fm();
  Arbre *expression(); // transforme une expression en arbre*/

  Arbre* niv0();
  Arbre* nivn(int);
  Arbre* nivnbis(Arbre*, int);

  void lignecode();
  void lignesdonnees();
  void lignescode();
  void codesource();
  int UAL(int);
  int UALi(int);
  int CallJmp(int);
  int Jr(int);
public :
  Syntaxe() : lCode(0,0), lCurrent(&lCode), cCode(0), cData(0), err(false) {}

  int Read(FILE *fichier, std::ofstream *out); // fait l'analyse syntaxique du fichier.
};

#endif
