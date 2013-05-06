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
      std::wcerr << L"Erreur ligne " << lex.GetLine() << L" colonne " << lex.GetColumn() << L"\u00a0: " << L"')' attendu." << std::endl;
      err = true;
    } else lex.Read();
    break;

  case ID :
    if (isData) {
      // ERREUR
      std::wcerr << L"Erreur ligne " << lex.GetLine() << L" colonne " << lex.GetColumn() << L"\u00a0: " << L"la taille des zones de données ne doivent pas dépendre de labels." << std::endl;
      err = true;
      if (lex.GetSymb().GetInit())
	a = new Arbre(NOMBRE, lex.GetSymb().GetValue(), lex.GetLine(), lex.GetColumn());
      else 
	a = new Arbre(UNDEFINED, 0, lex.GetLine(), lex.GetColumn());
      break;
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
    err = true;
    std::wcerr << L"Erreur ligne " << lex.GetLine() << L" colonne " << lex.GetColumn() << L"\u00a0: " << L"nombre attendu." << std::endl;
    a = new Arbre(UNDEFINED, 0, lex.GetLine(), lex.GetColumn());
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
      std::wcerr << L"Erreur ligne " << lex.GetLine() << L" colonne " << lex.GetColumn() << L"\u00a0: " << L"le label " << s.GetText() << " est déjà déclaré." << std::endl;
      err = true;
    } else s.SetValue(cCode);
    lex.Read();
    if (lex.GetId() != DEUX_POINTS) {
      // ERREUR : il faut :
      std::wcerr << L"Erreur ligne " << lex.GetLine() << L" colonne " << lex.GetColumn() << L"\u00a0: " << L"':' attendu." << std::endl;
      err = true;
    } else lex.Read();
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
      std::wcerr << L"Erreur ligne " << lex.GetLine() << L" colonne " << lex.GetColumn() << L"\u00a0: " << L"',' en trop." << std::endl;
      err = true;
      lex.Read();
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
      std::wcerr << L"Erreur ligne " << lex.GetLine() << L" colonne " << lex.GetColumn() << L"\u00a0: " << L"une instruction doit être suivi d'un saut de ligne." << std::endl;
      err = true;
      while(lex.GetId() != FIN_LIGNE) lex.Read(); 
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
      std::wcerr << L"Erreur ligne " << lex.GetLine() << L" colonne " << lex.GetColumn() << L"\u00a0: " << L"le label " << s.GetText() << " est déjà déclaré." << std::endl;
      err = true;
    } else s.SetValue(cData);
    lex.Read();
    if (lex.GetId() != DEUX_POINTS) {
      // ERREUR : il faut :
      std::wcerr << L"Erreur ligne " << lex.GetLine() << L" colonne " << lex.GetColumn() << L"\u00a0: " << L"':' attendu." << std::endl;
      err = true;
    } else lex.Read();
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
      std::wcerr << L"Erreur ligne " << lex.GetLine() << L" colonne " << lex.GetColumn() << L"\u00a0: " << L"la déclaration d'une zone de données doit être suivie d'un saut de ligne." << std::endl;
      err = true;
      while (lex.GetId() != FIN_LIGNE) lex.Read();
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
      std::wcerr << L"Erreur ligne " << lex.GetLine() << L" colonne " << lex.GetColumn() << L"\u00a0: " << L".DATA doit être suivi d'un saut de ligne." << std::endl;
      err = true;
      while (lex.GetId() != FIN_LIGNE) lex.Read();
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
      std::wcerr << L"Erreur ligne " << lex.GetLine() << L" colonne " << lex.GetColumn() << L"\u00a0: " << L".CODE doit être suivi d'un saut de ligne." << std::endl;
      err = true;
      while (lex.GetId() != FIN_LIGNE) lex.Read();
      }
    lex.Read();
    lignescode();
    codesource();
    break;

  case E_O_F :
    break;

  default: // ERREUR
    if (err == false) {
      std::wcerr << L"Erreur ligne " << lex.GetLine() << L" colonne " << lex.GetColumn() << L"\u00a0: " << L"le programme doit commencer par .DATA ou .CODE." << std::endl;
      err = true;
    }
    lex.Read();
    codesource();
  }
}

int Syntaxe::UAL(int instr) {
  if (!(lCurrent->GetType(0))) {
    // ERREUR
    std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la première opérande doit être un registre." << std::endl;
      err = true;
  }
  if (!(lCurrent->GetType(1))) {
    // ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la deuxième opérande doit être un registre." << std::endl;
      err = true;
  }
  if (!(lCurrent->GetType(2))) {
    // WARNING
      std::wcout << L"Attention ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la troisième opérande devrait être un registre." << std::endl;

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
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la première opérande doit être un registre." << std::endl;
      err = true;
  }
  if (!(lCurrent->GetType(1))) {
    // ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la deuxième opérande doit être un registre." << std::endl;
      err = true;
  }
  if (lCurrent->GetType(2)) {
    // WARNING
    std::wcout << L"Attention ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la troisième  opérande devrait être une valeur immédiate." << std::endl;
    instr -= 1 << 26;
    return UAL(instr);
  }
  if (lCurrent->GetImm(2)->GetType() == UNDEFINED) {
    // ERREUR
    err = true;
  }
  instr += lCurrent->GetReg(0) << 21;
  instr += lCurrent->GetReg(1) << 16;
  instr += lCurrent->GetImm(2)->GetValue() & 0xFFFF;
  return instr;
}

int Syntaxe::CallJmp(int instr) {
  if (lCurrent->GetType(0)) {
    // ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la première opérande doit être une valeur immédiate." << std::endl;
      err = true;
      return instr;
  }
  if (lCurrent->GetImm(0)->GetType() == UNDEFINED) {
    // ERREUR
    err = true;
  }
  instr += lCurrent->GetImm(0)->GetValue() & 0x7FFFFFF;
  return instr;
}

int Syntaxe::Jr(int instr) {
  if (!(lCurrent->GetType(0))) {
    // ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la première opérande doit être un registre." << std::endl;
      err = true;
  }
  if (!(lCurrent->GetType(1))) {
    // ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la deuxième opérande doit être un registre." << std::endl;
      err = true;
  }
  if (lCurrent->GetType(2)) {
    // ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la troisième opérande doit être une valeur immédiate." << std::endl;
      err = true;
      return instr;
  }
  if (lCurrent->GetImm(2)->GetType() == UNDEFINED) {
    // ERREUR
    err = true;
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
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction ADD doit avoir trois opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = UAL(0);
      break;
    case ADDI:
      if (nb_op != 3) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction ADDi doit avoir trois opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = UALi(1 << 26);
      break;
    case AND:
      if (nb_op != 3) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction AND doit avoir trois opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = UAL(4 << 26);
      break;
    case ANDI:
      if (nb_op != 3) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction ANDi doit avoir trois opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = UALi(5 << 26);
      break;
    case CALL:
      if (nb_op != 1) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction CALL doit avoir une opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = CallJmp(52 << 26);
      break;
    case IN:
      if (nb_op != 2) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction IN doit avoir deux opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      if (!(lCurrent->GetType(0))) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la première opérande doit être un registre." << std::endl;
      err = true;
      }
      if (lCurrent->GetType(1)) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la deuxième opérande doit être une valeur immédiate." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      if (lCurrent->GetImm(1)->GetType() == UNDEFINED) {
	// ERREUR
	err = true;
      }
      instr = 32 << 26;
      instr += lCurrent->GetReg(0) << 21;
      instr += lCurrent->GetImm(1)->GetValue() & 0xFFFF;
      break;
    case JMP:
      if (nb_op != 1) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction JMP doit avoir une opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = CallJmp(48 << 26);
      break;
    case JMR:
      if (nb_op != 1) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction JMR doit avoir une opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      if (!lCurrent->GetType(0)) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la première opérande doit être un registre." << std::endl;
      err = true;
      }
      instr = 58 << 26;
      instr += lCurrent->GetReg(0) << 16;
      break;
    case JRE:
      if (nb_op != 3) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction JRE doit avoir trois opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = Jr(57 << 26);
      break;
    case JRS:
      if (nb_op != 3) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction JRS doit avoir trois opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = Jr(59 << 26);
      break;
    case LOAD:
      if (nb_op != 2) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction LOAD doit avoir deux opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      if (!lCurrent->GetType(0)) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la première opérande doit être un registre." << std::endl;
      err = true;
      }
      if (!lCurrent->GetType(1)) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la deuxième opérande doit être un registre." << std::endl;
      err = true;
      }
      instr = 16 << 26;
      instr += lCurrent->GetReg(0) << 21;
      instr += lCurrent->GetReg(1) << 11;
      break;
    case OR:
      if (nb_op != 3) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction OR doit avoir trois opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = UAL(6 << 26);
      break;
    case ORI:
      if (nb_op != 3) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction ORi doit avoir trois opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = UALi(7 << 26);
      break;
    case OUT:
      if (nb_op != 2) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction OUT doit avoir deux opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      if (lCurrent->GetType(0)) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la première opérande doit être une valeur immédiate." << std::endl;
      err = true;
      }
      if (!lCurrent->GetType(1)) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la deuxième opérande doit être un registre." << std::endl;
      err = true;
      }
      if (lCurrent->GetImm(0)->GetType() == UNDEFINED) {
	// ERREUR
	err = true;
      }
      if (err) {instr = 0; break;}
      instr = 34 << 26;
      instr += lCurrent->GetImm(0)->GetValue();
      instr += lCurrent->GetReg(1) << 16;
      break;
    case RET:
      if (nb_op != 0) {
	// ERREUR
	std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction RET ne prend aucune opérande." << std::endl;
	err = true;
      }
      instr = 54 << 26;
      break;
    case SL:
      if (nb_op != 3) {
	// ERREUR
	std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction SL doit avoir trois opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = UAL(12 << 26);
      break;
    case SLI:
      if (nb_op != 3) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction SLi doit avoir trois opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = UALi(13 << 26);
      break;
    case SR:
      if (nb_op != 3) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction SR doit avoir trois opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = UAL(10 << 26);
      break;
    case SRI:
      if (nb_op != 3) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction SRi doit avoir trois opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = UALi(11 << 26);
      break;
    case STORE:
      if (nb_op != 2) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction STORE doit avoir deux opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      if (!lCurrent->GetType(0)) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la première opérande doit être un registre." << std::endl;
      err = true;
      }
      if (!lCurrent->GetType(1)) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"la deuxième opérande doit être un registre." << std::endl;
      err = true;
      }
      instr = 18 << 26;
      instr += lCurrent->GetReg(0) << 11;
      instr += lCurrent->GetReg(1) << 16;
      break;
    case SUB:
      if (nb_op != 3) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction SUB doit avoir trois opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = UAL(2 << 26);
      break;
    case SUBI:
      if (nb_op != 3) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction SUBi doit avoir trois opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = UALi(3 << 26);
      break;
    case XOR:
      if (nb_op != 3) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction XOR doit avoir trois opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = UAL(8 << 26);
      break;
    case XORI:
      if (nb_op != 3) {
	// ERREUR
      std::wcerr << L"Erreur ligne " << lCurrent->GetLine() << L"\u00a0: " << L"l'instruction XORi doit avoir trois opérandes." << std::endl;
      err = true;
      instr = 0;
      break;
      }
      instr = UALi(9 << 26);
      break;
    }

    /*
    std::wcout << lCurrent->GetInstr() << " : ";
    for (int i = 31; i >= 0; i--) {
      std::wcout << ((instr >> i) & 1);
      if (i == 26) std::wcout << " "; 
      if (i == 21) std::wcout << " ";
      if (i == 16) std::wcout << " ";
    }
    std::wcout << std::endl;
    */
    if (!err) out->write((const char*) &instr, 4);
    l = lCurrent;
    lCurrent = l->GetSuiv();
    // délétion automatique des éléments de la liste, on ne s'en soucie pas.
  }
  return 0;
}
