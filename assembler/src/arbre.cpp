#include <iostream>
#include "arbre.hpp"
#include "symbole.hpp"

unsigned int exp(unsigned int a, unsigned int b) {
  if (b == 0) {
    return 1;
  }
  else if (b % 2) {
    return a*exp(a*a,b/2);
  }
  else return exp(a*a,b/2);
}

void Arbre::Evaluate() {
  if (fils[0]) fils[0]->Evaluate();
  if (fils[1]) fils[1]->Evaluate();

  switch(type_noeud) {
    //case NOMBRE : // rien à évaluer
    //break;
  case ID :
    if (symb.GetInit()) {
      val_noeud = symb.GetValue();
    }
    else {
      std::wcerr << L"Erreur ligne " << line << L" colonne " << column << L"\u00a0: " << symb.GetText() << L" n'est pas déclaré." << std::endl;
      type_noeud = UNDEFINED;
    }
    break;

  case PLUS :
    if (fils[0]->type_noeud == UNDEFINED || fils[1]->type_noeud == UNDEFINED) {
      type_noeud = UNDEFINED;
    }
    else {
      val_noeud = fils[0]->val_noeud+fils[1]->val_noeud;
    }
    break;

  case MOINS :
    if (fils[0]->type_noeud == UNDEFINED) {
      type_noeud = UNDEFINED;
    }
    else {
      val_noeud = -fils[0]->val_noeud;
    }
    break;

  case FOIS :
    if (fils[0]->type_noeud == UNDEFINED || fils[1]->type_noeud == UNDEFINED) {
      type_noeud = UNDEFINED;
    }
    else {
      val_noeud = fils[0]->val_noeud*fils[1]->val_noeud;
    }
    break;

  case DIV :
    if (fils[1]->val_noeud == 0) {
      std::wcerr << L"Erreur ligne " << line << L" colonne " << column << L"\u00a0: division par zéro." << std::endl;
      type_noeud = UNDEFINED;
    }
    else if (fils[0]->type_noeud == UNDEFINED || fils[1]->type_noeud == UNDEFINED) {
      type_noeud = UNDEFINED;
    }
    else {
      val_noeud = fils[0]->val_noeud/fils[1]->val_noeud;
    }
    break;

  case MODULO :
    if (fils[1]->val_noeud == 0) {
      std::wcerr << L"Erreur ligne " << line << L" colonne " << column << L"\u00a0: modulo par zéro." << std::endl;
      type_noeud = UNDEFINED;
    }
    else if (fils[0]->type_noeud == UNDEFINED || fils[1]->type_noeud == UNDEFINED) {
      type_noeud = UNDEFINED;
    }
    else {
      val_noeud = fils[0]->val_noeud % fils[1]->val_noeud;
    }
    break;

  case EXP :
    if (fils[0]->type_noeud == UNDEFINED || fils[1]->type_noeud == UNDEFINED) {
      type_noeud = UNDEFINED;
    }
    else {
      val_noeud = exp(fils[0]->val_noeud, fils[1]->val_noeud);
    }
    break;
  }

  if (fils[0]) delete fils[0];
  if (fils[1]) delete fils[1];
  fils[0] = 0; fils[1] = 0;
}
