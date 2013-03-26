#include <iostream>
#include <cwchar>

// debug de arbre.
#include "arbre.hpp"

//ID dix=10
//2^((1+dix)*3-dix/4) % 20) = 2^((33-2) % 20) = 2^11 = 2048
int main(int argc, char* argv[]) {
  setlocale(LC_ALL, ""); // pour ne pas avoir de problème avec les accents.

  wchar_t *d = new wchar_t[10]; wcscpy(d, L"dix");
  Symbole dix(d);
  //dix.SetValue(10);
  
  Arbre* deux = new Arbre(NOMBRE, 2, 1, 1);
  Arbre* exp = new Arbre(EXP, 0, 1, 2);
  Arbre* un = new Arbre(NOMBRE, 1, 1, 5);
  Arbre* plus = new Arbre(PLUS, 0, 1, 6);
  Arbre* s1 = new Arbre(ID, 0, 1, 7);
  Arbre* fois = new Arbre(FOIS, 0, 1, 11);
  Arbre* trois = new Arbre(NOMBRE, 3, 1, 12);
  Arbre* moins = new Arbre(MOINS, 0, 1, 13);
  Arbre* s2 = new Arbre(ID, 0, 1, 14);
  Arbre* div = new Arbre(DIV, 0, 1, 17);
  Arbre* quatre = new Arbre(NOMBRE, 0, 1, 18);
  Arbre* mod = new Arbre(MODULO, 0, 1, 21);
  Arbre* vingt = new Arbre(NOMBRE, 0, 1, 23);

  s1->SetSymbole(dix);
  s2->SetSymbole(dix);
  exp->SetFilsGauche(deux);
  exp->SetFilsDroit(mod);
  plus->SetFilsGauche(un);
  plus->SetFilsDroit(s1);
  fois->SetFilsGauche(plus);
  fois->SetFilsDroit(trois);
  moins->SetFilsGauche(fois);
  moins->SetFilsDroit(div);
  div->SetFilsGauche(s2);
  div->SetFilsDroit(quatre);
  mod->SetFilsGauche(moins);
  mod->SetFilsDroit(vingt);

  exp->Evaluate();
  std::cout << exp->GetValue() << std::endl;
  delete exp;
  return 0;
}
