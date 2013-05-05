#include <iostream>
#include <fstream>
#include "arbre.hpp"
#include "symbole.hpp"
#include "liste.hpp"
#include "syntaxe.hpp"

Arbre* Syntaxe::nb() {

  Arbre *a;
  switch (lex.GetId()) {
  case PGAUCHE :
    lex.Read();
    a = expression();
    if (lex.GetId() != PDROITE) {
      // ERREUR : PDROITE
      std::wcout << "Erreur : pdroite.\n" << std::endl;
    }
    lex.Read();
    break;

  case ID :
    if (isData) {
      // ERREUR
      std::wcout << "Erreur : id dans data.\n" << std::endl;
    }
    a = new Arbre(ID, 0, lex.GetLine(), lex.GetColumn());
    a->SetSymbole(lex.GetSymb());
    lex.Read();
    break;
  case NOMBRE :
    a = new Arbre(NOMBRE, lex.GetIdbis(), lex.GetLine(), lex.GetColumn());
    lex.Read();
    break;
    
  case MOINS:
    a = new Arbre(MOINS, 0, lex.GetLine(), lex.GetColumn());
    lex.Read();
    a->SetFilsGauche(fm());
    break;
  default :
    std::wcout << "Erreur : nb attendu.\n" << std::endl;    
  }
  return a;
}

Arbre* Syntaxe::e() {

  Arbre* fg = nb();
  Arbre* fd;
  Arbre* a;
  unsigned int l, c;
  switch (lex.GetId()) {
  case EXP:
    l = lex.GetLine();
    c = lex.GetColumn();
    lex.Read();
    fd = e();
    a = new Arbre(EXP, 0, l, c);
    a->SetFilsGauche(fg);
    a->SetFilsDroit(fd);
    break;

  default:
    // cas epsilon
    a = fg;
  }
  return a;
}

Arbre* Syntaxe::d() {

  Arbre* fg = e();
  Arbre* fd;
  Arbre* a;
  unsigned int l, c;
  switch (lex.GetId()) {
  case DIV :
    l = lex.GetLine();
    c = lex.GetColumn();
    lex.Read();
    fd = fm();
    a = new Arbre(DIV, 0, l, c);
    a->SetFilsGauche(fg);
    a->SetFilsDroit(fd);
    break;

  default:
    // cas epsilon
    a = fg;
  }
  return a;
}

Arbre* Syntaxe::fm() {

  Arbre* fg = d();
  Arbre* fd;
  Arbre* a;
  unsigned int i, l, c;
  switch (lex.GetId()) {
  case FOIS :
  case MODULO :
    i = lex.GetId();
    l = lex.GetLine();
    c = lex.GetColumn();
    lex.Read();
    fd = fm();
    a = new Arbre(i, 0, l, c);
    a->SetFilsGauche(fg);
    a->SetFilsDroit(fd);
    break;

  default:
    // cas epsilon
    a = fg;
  }
  return a;
}

Arbre* Syntaxe::expression() {
  // PLUS, MOINS > FOIS, DIV, MODULO > EXP
  Arbre* fg = fm();
  Arbre* fd;
  Arbre* a;
  unsigned int l, c;
  switch (lex.GetId()) {
  case PLUS :
    lex.Read();
  case MOINS :
    l = lex.GetLine();
    c = lex.GetColumn();
    fd = expression();
    a = new Arbre(PLUS, 0, l, c);
    a->SetFilsGauche(fg);
    a->SetFilsDroit(fd);
    break;

  default:
    // cas epsilon
    a = fg;
  }
  return a;
}

void Syntaxe::lignescode() {
  Liste *l;
  Symbole s;
  int i;
  unsigned int t;

  while (lex.GetId() == FIN_LIGNE) {
    lex.Read();
  }

  switch (lex.GetId()) {
  case ID :
    // initialisation de la valeur de l'ID
    s = lex.GetSymb();
    if (s.GetInit()) {
      // Erreur : symbole déjà rencontré
      std::wcout << "Erreur : symbole code : " << s.GetText() << " " << s.GetValue() << std::endl;
    } else s.SetValue(cCode);
    lex.Read();
    if (lex.GetId() != DEUX_POINTS) {
      // ERREUR : il faut :
      std::wcout << "Erreur : :.\n" << std::endl;
    }
    lex.Read();
    lignescode();
    break;
  
  case INSTR :

    // MAJ de la pile d'instructions.
    *lCurrent = Liste(lex.GetIdbis(), lex.GetLine());
    lex.Read();
    // lecture des opérandes et de finligne
    for (i = 0; i < 3; i++) {
      if ((lex.GetId() == VIRGULE) && (i == 0)) {
	// ERREUR
	std::wcout << "Erreur : virg en trop" << std::endl;
      }
      if (lex.GetId() == VIRGULE) lex.Read();
      t = lex.GetId();
      if (t == REGISTRE) {
	lCurrent->SetReg(i, lex.GetIdbis());
	lex.Read();
      } else if (t == PGAUCHE || t == ID || t == NOMBRE) {
	lCurrent->SetImm(i, expression());
      } else if (t == FIN_LIGNE) break;
    }
    l = new Liste(0,0);
    lCurrent->SetSuiv(l);
    lCurrent = l;
    cCode++;
    if (lex.GetId() != FIN_LIGNE) {
      // ERREUR
      std::wcout << L"Erreur Finligne" << std::endl;
    }
    lex.Read();
    lignescode();
    break;

  default:
    // cas epsilon
    break;
  }
}

void Syntaxe::lignesdonnees() {
  Symbole s;
  Arbre *a;
  while (lex.GetId() == FIN_LIGNE) {
    lex.Read();
  }

  switch (lex.GetId()) {
  case ID :
    // initialisation de la valeur de l'ID
    s = lex.GetSymb();
    if (s.GetInit()) {
      // Erreur : symbole déjà rencontré
      std::wcout << "Erreur : symbole data.\n" << std::endl;
    } else s.SetValue(cData);
    lex.Read();
    if (lex.GetId() != DEUX_POINTS) {
      // ERREUR : il faut :
      std::wcout << "Erreur : :.\n" << std::endl;
    }
    lex.Read();
    lignesdonnees();
    break;

  case NOMBRE :
  case PGAUCHE :
    a = expression();
    a->Evaluate();
    if (a->GetType() != UNDEFINED) 
      cData += a->GetValue(); // met à jour le compteur de données.
    delete a;
    if (lex.GetId() != FIN_LIGNE) {
      // ERREUR : il faut un saut de ligne
      std::wcout << "Erreur : saut de ligne.\n" << std::endl;
    }
    lex.Read();
    lignesdonnees();
    break;

  default :
    // cas epsilon
    break;
  }
}

void Syntaxe::codesource() {

  while (lex.GetId() == FIN_LIGNE) {
    lex.Read();
  }

  switch (lex.GetId()) {
  case DATA :
    isData = true;
    lex.Read();
    if (lex.GetId() != FIN_LIGNE)
      { // ERREUR : il faut sauter une ligne
	std::wcout << "Erreur : saut de ligne.\n" << std::endl;
      }
    lex.Read();
    lignesdonnees();
    codesource();
    break;

  case CODE :
    isData = false;
    lex.Read();
    if (lex.GetId() != FIN_LIGNE)
      { // ERREUR : il faut sauter une ligne
	std::wcout << "Erreur : saut de ligne.\n" << std::endl;
      }
    lex.Read();
    lignescode();
    codesource();
    break;

  case E_O_F :
    break;

  default: // ERREUR
    std::wcout << "Erreur critique.\n" << std::endl;
  }
}

int Syntaxe::UAL(int instr) {
  if (!(lCurrent->GetType(0))) {
    // ERREUR
	std::wcout << L"Erreur" << std::endl;
  }
  if (!(lCurrent->GetType(1))) {
    // ERREUR
	std::wcout << L"Erreur" << std::endl;
  }
  if (!(lCurrent->GetType(2))) {
    // WARNING
    instr += 1 << 26;
    return UALi(instr);
  }
  instr += lCurrent->GetReg(0) << 21;
  instr += lCurrent->GetReg(1) << 16;
  instr += lCurrent->GetReg(2) << 11;
  return instr;
}

int Syntaxe::UALi(int instr) {
  if (!(lCurrent->GetType(0))) {
    // ERREUR
	std::wcout << L"Erreur" << std::endl;
  }
  if (!(lCurrent->GetType(1))) {
    // ERREUR
	std::wcout << L"Erreur" << std::endl;
  }
  if (lCurrent->GetType(2)) {
    // WARNING
    instr -= 1 << 26;
    return UAL(instr);
  }
  if (lCurrent->GetImm(2)->GetType() == UNDEFINED) {
    // ERREUR
    std::cout << "ERREUR" << std::endl;
  }
  instr += lCurrent->GetReg(0) << 21;
  instr += lCurrent->GetReg(1) << 16;
  instr += lCurrent->GetImm(2)->GetValue() & 0xFFFF;
  return instr;
}

int Syntaxe::CallJmp(int instr) {
  if (lCurrent->GetType(0)) {
    // ERREUR
	std::wcout << L"Erreur" << std::endl;
  }
  if (lCurrent->GetImm(0)->GetType() == UNDEFINED) {
    // ERREUR
    std::cout << "ERREUR" << std::endl;
  }
  instr += lCurrent->GetImm(0)->GetValue() & 0x7FFFFFF;
  return instr;
}

int Syntaxe::Jr(int instr) {
  if (!(lCurrent->GetType(0))) {
    // ERREUR
	std::wcout << L"Erreur" << std::endl;
  }
  if (!(lCurrent->GetType(1))) {
    // ERREUR
	std::wcout << L"Erreur" << std::endl;
  }
  if (lCurrent->GetType(2)) {
    // ERREUR
	std::wcout << L"Erreur" << std::endl;
  }
  if (lCurrent->GetImm(2)->GetType() == UNDEFINED) {
    // ERREUR
    std::cout << "ERREUR" << std::endl;
  }
  instr += lCurrent->GetReg(0) << 16;
  instr += lCurrent->GetReg(1) << 11;
  instr += lCurrent->GetImm(2)->GetValue() & 0x7FF;
  return instr;  
}

// in, jmr, load, out, store sont implémentés en direct.

int Syntaxe::Read(FILE *in, std::ofstream *out) {

  Liste* l;
  UniLex::SetFichier(in);
  lex.Read();
  int instr;
  int nb_op;
  int i;

  codesource();

  // analyse sémantique
  lCurrent = &lCode;
  while (lCurrent->GetSuiv() != 0) {
    nb_op = 3;
    for (i = 0; i < 3; i++) {
      if (!(lCurrent->GetType(i)) && lCurrent->GetImm(i)) { // si la ième opérande est un arbre non vide
	lCurrent->GetImm(i)->Evaluate();
      }
      if (!(lCurrent->GetType(i) || lCurrent->GetImm(i))) {
	nb_op = i;
	break;
      }
    }
    instr = 0;
    switch (lCurrent->GetInstr()) {
    case ADD:
      if (nb_op != 3) {
	// ERREUR
	std::wcout << L"Erreur : ADD a 3 opérandes" << std::endl;
      }
      instr = UAL(0);
      break;
    case ADDI:
      if (nb_op != 3) {
	// ERREUR
	std::wcout << L"Erreur : ADDi a 3 opérandes" << std::endl;
      }
      instr = UALi(1 << 26);
      break;
    case AND:
      if (nb_op != 3) {
	// ERREUR
	std::wcout << L"Erreur : AND a 3 opérandes" << std::endl;
      }
      instr = UAL(4 << 26);
      break;
    case ANDI:
      if (nb_op != 3) {
	// ERREUR
	std::wcout << L"Erreur : ANDi a 3 opérandes" << std::endl;
      }
      instr = UALi(5 << 26);
      break;
    case CALL:
      if (nb_op != 1) {
	// ERREUR
	std::wcout << L"Erreur : CALL a 1 opérande" << std::endl;
      }
      instr = CallJmp(52 << 26);
      break;
    case IN:
      if (nb_op != 2) {
	// ERREUR
	std::wcout << L"Erreur : IN a 2 opérandes" << std::endl;
      }
      if (!(lCurrent->GetType(0))) {
	// ERREUR
	std::wcout << L"Erreur 0" << std::endl;
      }
      if (lCurrent->GetType(1)) {
	// ERREUR
	std::wcout << L"Erreur 1" << std::endl;
      }
      if (lCurrent->GetImm(1)->GetType() == UNDEFINED) {
	// ERREUR
	std::wcout << L"Erreur calcul 1 : " << std::endl;
      }
      instr = 32 << 26;
      instr += lCurrent->GetReg(0) << 21;
      instr += lCurrent->GetImm(1)->GetValue() & 0xFFFF;
      break;
    case JMP:
      if (nb_op != 1) {
	// ERREUR
	std::wcout << L"Erreur : JMP a une opérande" << std::endl;
      }
      instr = CallJmp(48 << 26);
      break;
    case JMR:
      if (nb_op != 1) {
	// ERREUR
	std::wcout << L"Erreur : JMR a une opérande" << std::endl;
      }
      if (!lCurrent->GetType(0)) {
	// ERREUR
	std::wcout << L"Erreur 0" << std::endl;
      }
      instr = 58 << 26;
      instr += lCurrent->GetReg(0) << 16;
      break;
    case JRE:
      if (nb_op != 3) {
	// ERREUR
	std::wcout << L"Erreur : JRE a une opérande" << std::endl;
      }
      instr = Jr(57 << 26);
      break;
    case JRS:
      if (nb_op != 3) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      instr = Jr(59 << 26);
      break;
    case LOAD:
      if (nb_op != 2) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      if (!lCurrent->GetType(0)) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      if (!lCurrent->GetType(1)) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      instr = 16 << 26;
      instr += lCurrent->GetReg(0) << 21;
      instr += lCurrent->GetReg(1) << 11;
      break;
    case OR:
      if (nb_op != 3) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      instr = UAL(6 << 26);
      break;
    case ORI:
      if (nb_op != 3) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      instr = UALi(7 << 26);
      break;
    case OUT:
      if (nb_op != 2) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      if (lCurrent->GetType(0)) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      if (!lCurrent->GetType(1)) {
	std::wcout << L"Erreur" << std::endl;
	// ERREUR
      }
      if (lCurrent->GetImm(0)->GetType() == UNDEFINED) {
	std::wcout << L"Erreur" << std::endl;
	// ERREUR
      }
      instr = 34 << 26;
      instr += lCurrent->GetImm(0)->GetValue();
      instr += lCurrent->GetReg(1) << 16;
      break;
    case RET:
      if (nb_op != 0) {
	std::wcout << L"Erreur" << std::endl;
	// ERREUR
      }
      instr = 54 << 26;
      break;
    case SL:
      if (nb_op != 3) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      instr = UAL(12 << 26);
      break;
    case SLI:
      if (nb_op != 3) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      instr = UALi(13 << 26);
      break;
    case SR:
      if (nb_op != 3) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      instr = UAL(10 << 26);
      break;
    case SRI:
      if (nb_op != 3) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      instr = UALi(11 << 26);
      break;
    case STORE:
      if (nb_op != 2) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      if (!lCurrent->GetType(0)) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      if (!lCurrent->GetType(1)) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      instr = 17 << 26;
      instr += lCurrent->GetReg(0) << 11;
      instr += lCurrent->GetReg(1) << 16;
      break;
    case SUB:
      if (nb_op != 3) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      instr = UAL(2 << 26);
      break;
    case SUBI:
      if (nb_op != 3) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      instr = UALi(3 << 26);
      break;
    case XOR:
      if (nb_op != 3) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      instr = UAL(8 << 26);
      break;
    case XORI:
      if (nb_op != 3) {
	// ERREUR
	std::wcout << L"Erreur" << std::endl;
      }
      instr = UALi(9 << 26);
      break;
    }

    out->write((const char*) &instr, 4);
    l = lCurrent;
    lCurrent = l->GetSuiv();
    // délétion automatique des éléments de la liste, on ne s'en soucie pas.
  }
  return 0;
}
