#ifndef ARBRE_HPP
#define ARBRE_HPP

#include "symbole.hpp"
#include "enum.hpp"

class Arbre {
private :
  unsigned int type_noeud; // NOMBRE, ID, PLUS, MOINS, FOIS, DIV, MODULO, EXP, UNDEFINED (en cas d'erreur)
  unsigned int val_noeud; // valeur du nombre
  Symbole symb; // symbole
  unsigned int line;
  unsigned int column;
  Arbre* fils[2];

public :
  Arbre(unsigned int type_noeud, unsigned int val_noeud, unsigned int line, unsigned int column) : type_noeud(type_noeud), val_noeud(val_noeud), line(line), column(column) {fils[0] = 0; fils[1] = 0;}

  void SetFilsGauche(Arbre* a) { fils[0] = a; }
  void SetFilsDroit(Arbre* b) { fils[1] = b; }
  void SetSymbole(Symbole s) { symb = s; }

  unsigned int GetType() { return type_noeud; }
  unsigned int GetValue() {return val_noeud; }

  void Evaluate(); // évalue l'expression arithmétique, et réduit l'arbre à un unique noeud, s'il y a une erreur, ce noeud est UNDEFINED (et fait un rapport d'erreur, sauf si c'est une propagation d'erreur (mais si on peut trouver plusieurs erreurs (du genre (2/0)/0), fait plusieurs rapports)).

  ~Arbre() { if(fils[0]) delete fils[0]; if(fils[1]) delete fils[1]; }

};

#endif
