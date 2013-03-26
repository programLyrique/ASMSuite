#ifndef LISTE_HPP
#define LISTE_HPP

#include "arbre.hpp"

class Liste {
private :
  unsigned int line;
  unsigned int instr; // instruction
  bool isReg[3]; // indique si les opérandes sont des registres ou des immédiats (ou rien).
  unsigned int reg[3]; // valeur des registres
  Arbre* imm[3]; //valeur des entiers (par des arbres).
  Liste* suiv;

public :
  Liste(unsigned int instr, unsigned int line); // crée une instruction (sans opérandes)

  void SetReg(int index, unsigned int reg); // la index-ième opérande est un registre de valeur reg.
  void SetImm(int index, Arbre* imm); // la index-ième opérande est un immédiat de valeur imm.
  void SetSuiv(Liste* suiv);

  bool getType(int index);
  unsigned int getReg(int index);
  Arbre* getImm(int index);
  Liste* GetSuiv();

  ~Liste() { delete suiv; }

};

#endif
