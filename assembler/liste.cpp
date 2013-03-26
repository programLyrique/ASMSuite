#include "liste.hpp"

Liste::Liste(unsigned int i, unsigned int l) : line(l), instr(i), suiv(0) {
  for (int i = 0; i < 3; i++) { // cette initialisation permet de savoir combien il y a d'opérandes.
    isReg[i] = false;
    imm[i] = 0;
  }
}
void Liste::SetReg(int index, unsigned int r) {
  isReg[index] = true;
  reg[index] = r;
}

void Liste::SetImm(int index, Arbre* a) {
  //isReg[index] = false; // vaut déjà false.
  imm[index] = a;
}
void Liste::SetSuiv(Liste* s) {
  suiv = s;
}

bool Liste::getType(int index) {
  return isReg[index];
}

unsigned int Liste::getReg(int index) {
  return reg[index];
}

Arbre* Liste::getImm(int index) {
  return imm[index];
}

Liste* Liste::GetSuiv() {
  return suiv;
}

Liste::~Liste() {
  delete suiv;
  for (int i = 0; i < 3; i++)
    if (Arbre[i]) delete Arbre[i];
}
