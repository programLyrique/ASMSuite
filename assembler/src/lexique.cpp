#include <iostream>
#include "lecture.hpp"
#include "lexique.hpp"
#include "symbole.hpp"

static Lecture* fichier;

void UniLex::SetFichier(FILE *f) {
  fichier = new Lecture(f);
}

void UniLex::DeleteFichier() {
  delete fichier;
}

bool UniLex::CaracId(wchar_t c) {
  if (c == L'_') return true;
  else if ((c >= L'0') && (c <= L'9')) return true;
  else if ((c >= L'A') && (c <= L'Z')) return true;
  else if ((c >= L'a') && (c <= L'z')) return true;
  else return false;
}

bool UniLex::CaracFin(wchar_t c) {
  switch (c) {
  case L' ':
  case L'\t':
  case L',':
  case L'+':
  case L'*':
  case L'-':
  case L'/':
  case L'(':
  case L')':
  case L'^':
  case L':':
  case L'\n':
  case L'%':
  case L'~':
  case L'&':
  case L'|':
  case L'<':
  case L'>':
    return true;
    break;
  default:
    return false;
  }
}

void UniLex::Read() {
  fichier->newToken();
  line = fichier->GetLine();
  column = fichier->GetColumn();
  // automate...
  wchar_t c = fichier->GetChar();
  switch (c) {
  case L':':
    id = DEUX_POINTS;
    c = fichier->GetNextChar();
    break;
  case L',':
    id = VIRGULE;
    c = fichier->GetNextChar();
    break;
  case L'\n':
    id = FIN_LIGNE;
    c = fichier->GetNextChar();
    break;
  case L'+':
    id = PLUS;
    c = fichier->GetNextChar();
    break;
  case L'-':
    id = MOINS;
    c = fichier->GetNextChar();
    break;
  case L'*':
    id = FOIS;
    c = fichier->GetNextChar();
    if (c == L'*') {
      id = EXP;
      c = fichier->GetNextChar();
    }
    break;
  case L'/':
    id = DIV;
    c = fichier->GetNextChar();
    break;
  case L'^':
    id = OUX;
    c = fichier->GetNextChar();
    break;
  case L'~':
    id = NON;
    c = fichier->GetNextChar();
    break;
  case L'|':
    id = OU;
    c = fichier->GetNextChar();
    break;
  case L'&':
    id = ET;
    c = fichier->GetNextChar();
    break;
  case L'%':
    id = MODULO;
    c = fichier->GetNextChar();
    break;
  case L'<':
    id = UNDEFINED;
    c = fichier->GetNextChar();
    if (c == L'<') {
      id = DECG;
      c = fichier->GetNextChar();
    }
    break;
  case L'>':
    id = UNDEFINED;
    c = fichier->GetNextChar();
    if (c == L'>') {
      id = DECD;
      c = fichier->GetNextChar();
    }
    break;
  case L'(':
    id = PGAUCHE;
    c = fichier->GetNextChar();
    break;
  case L')':
    id = PDROITE;
    c = fichier->GetNextChar();
    break;
  case L'\0':
    id = E_O_F;
    c = fichier->GetNextChar();
    break;
  case L'.':
    this->Point(); // cas .DATA, .BSS, .CODE ou UNDEFINED
    break;
  default: // autres cas : INSTR, REGISTRE, NOMBRE, ID (ou UNDEFINED)
    if ((c >= L'0') && (c <= L'9')) {
      id = NOMBRE;
      idbis = c - L'0';
      this->Nbr();
    }
    else if (CaracId(c)) Automate(c);
    else {
      id = UNDEFINED;
      c = fichier->GetNextChar();
    }
  }
  if (id == ID || id == UNDEFINED) {
    c = fichier->GetChar();
    if (!CaracFin(c)) {
      id = UNDEFINED;
      while (!CaracFin(c)) {
	c = fichier->GetNextChar();
      }
    }
    symb = Symbole(fichier->GetString());
  }
}

void UniLex::Point() {
  wchar_t c;
  int etat = 0; // 0=début, 1=D, 2=DA, 3=DAT, 4=B, 5=BS, 6=C, 7=CO, 8=COD, 999=DATA ou CODE ou BSS
  id = UNDEFINED;
  while (etat != -1) {
    c = fichier->GetNextChar();
    if (c >= L'a') c += L'A' - L'a'; // met c en majuscule (ne marche que pour les lettres a-z et A-Z);
    switch (c) {
    case L'A':
      switch (etat) {
      case 1: // D
	etat = 2;
	break;
      case 3: // DAT
	etat = 999;
	id = DATA;
	break;
      default:
	etat = -1;
      }
      break;

    case L'B':
      switch (etat) {
      case 0: // début
	etat = 4;
	break;
      default:
	etat = -1;
      }
      break;

    case L'C':
      switch (etat) {
      case 0:
	etat = 6;
	break;
      default:
	etat = -1;
      }
      break;

    case L'D':
      switch (etat) {
      case 0: // début
	etat = 1;
	break;
      case 7: // CO
	etat = 8;
	break;
      default:
	etat = -1;
      }
      break;

    case L'E':
      switch (etat) {
      case 8: // COD
	etat = 999;
	id = CODE;
	break;
      default:
	etat = -1;
      }
      break;

    case L'O':
      switch (etat) {
      case 6: // C
	etat = 7;
	break;
      default:
	etat = -1;
      }
      break;

    case L'S':
      switch (etat) {
      case 4: // B
	etat = 5;
	break;
      case 5: // BS
	etat = 999;
	id = DATA;
	break;
      default:
	etat = -1;
      }
      break;

    case L'T':
      switch (etat) {
      case 2: // DA
	etat = 3;
	break;
      default:
	etat = -1;
      }
      break;

    default:
      etat = -1;
    }
  }
}

void UniLex::Nbr() {
  unsigned int base = 10;
  unsigned int chiffre;

  wchar_t c = fichier->GetNextChar();
  if (idbis == 0) { // gère les bases 16 (0x) et 2 (Ob).
    if (c == L'x') {
      c = fichier->GetNextChar();
      base = 16;
    }
    else if (c == L'b') {
      c = fichier->GetNextChar();
      base = 2;
    }
  }
  while(true) { // convertit la chaîne de caractère en nombre.
    if (c < L'0' || c > L'f' || (c > L'9' && c < L'A') || (c > L'F' && c < L'a')) break;
    if ((c >= L'0') && (c <= L'9')) chiffre = c-L'0';
    else if ((c >= L'A') && (c <= L'F')) chiffre = 10+c-L'A';
    else if ((c >= L'a') && (c <= L'f')) chiffre = 10+c-L'a';
    else break;
    if (chiffre >= base) break;
    idbis *= base;
    idbis += chiffre;
    c = fichier->GetNextChar();
  }
}

void UniLex::Automate(wchar_t c) {
  unsigned int etat = 0;
  // 0=début, 1=A, 2=AD, 3=ADD, 4=AN, 5=AND, 6=C, 7=CA, 8=CAL, 9=I, 10=J, 11=JM, 12=JR, 13=L, 14=LO, 15=LOA, 16=O, 17=OR, 18=OU, 19=R, 20=RE, 21=S, 22=SL, 23=SR, 24=ST, 25=STO, 26=STOR, 27=SU, 28=SUB, 29=X, 30=XO, 31=XOR, 32=R[1,2], 33=R3, 999=ADDI ou ANDI ou...

  id = INSTR;
  idbis = -1; // ne correspond à aucune instruction.

  // gère les instructions.
  while (etat != (unsigned int) -1) {
    if ((c >= L'a') && (c <= L'z')) c += L'A' - L'a'; // si c est en majuscule, le met en minuscule.
    switch (c) {
    case L'A':
      switch (etat) {
      case 0: // début
	etat = 1;
	break;
      case 6: // C
	etat = 7;
	break;
      case 14: // LO
	etat = 15;
	break;
      default:
	etat = -1;
      }
      break;
    case L'B':
      switch (etat) {
      case 27: //SU
	etat = 28;
	idbis = SUB;
	break;
      default:
	etat = -1;
      }
      break;
    case L'C':
      switch (etat) {
      case 0: // début
	etat = 6;
	break;
      default:
	etat = -1;
      }
      break;
    case L'D':
      switch (etat) {
      case 1: // A
	etat = 2;
	break;
      case 2: // AD
	etat = 3;
	idbis = ADD;
	break;
      case 4: // AN
	etat = 5;
	idbis = AND;
	break;
      case 15: // LOA
	etat = 999;
	idbis = LOAD;
	break;
      default:
	etat = -1;
      }
      break;
    case L'E':
      switch (etat) {
      case 12: // JR
	etat = 999;
	idbis = JRE;
      case 19: // R
	etat = 20;
	break;
      case 26: //STOR
	etat = 999;
	idbis = STORE;
	break;
      default:
	etat = -1;
      }
      break;
    case L'I':
      switch(etat) {
      case 0: // début
	etat = 9;
	break;
      case 3: // ADD
	etat = 999;
	idbis = ADDI;
	break;
      case 5: // AND
	etat = 999;
	idbis = ANDI;
	break;
      case 17: // OR
	etat = 999;
	idbis = ORI;
	break;
      case 22: // SL
	etat = 999;
	idbis = SLI;
	break;
      case 23: // SR
	etat = 999;
	idbis = SRI;
	break;
      case 28: // SUB
	etat = 999;
	idbis = SUBI;
	break;
      case 31: // XOR
	etat = 999;
	idbis = XORI;
	break;
      default:
	etat = -1;
      }
      break;
    case L'J':
      switch (etat) {
      case 0: // début
	etat = 10;
	break;
      default:
	etat = -1;
      }
      break;
    case L'L':
      switch (etat) {
      case 0: // début
	etat = 13;
	break;
      case 7: // CA
	etat = 8;
	break;
      case 8: // CAL
	etat = 999;
	idbis = CALL;
	break;
      case 21: // S
	etat = 22;
	idbis = SL;
	break;
      default:
	etat = -1;
      }
      break;
    case L'M':
      switch (etat) {
      case 10: // J
	etat = 11;
	break;
      default:
	etat = -1;
      }
      break;
    case L'N':
      switch(etat) {
      case 1: // A
	etat = 4;
	break;
      case 9: // I
	etat = 999;
	idbis = IN;
	break;
      default:
	etat = -1;
      }
      break;
    case L'O':
      switch (etat) {
      case 0: // debut
	etat = 16;
	break;
      case 13: // L
	etat = 14;
	break;
      case 24: // ST
	etat = 25;
	break;
      case 29: // X
	etat = 30;
	break;
      default:
	etat = -1;
      }
      break;
    case L'P':
      switch (etat) {
      case 11: // JM
	etat = 999;
	idbis = JMP;
	break;
      default:
	etat = -1;
      }
      break;
    case L'R':
      switch (etat) {
      case 0: // début
	etat = 19;
	break;
      case 10: // J
	etat = 12;
	break;
      case 11: // JM
	etat = 999;
	idbis = JMR;
	break;
      case 16: // O
	etat = 17;
	idbis = OR;
	break;
      case 21: // S
	etat = 23;
	idbis = SR;
	break;
      case 25: // STO
	etat = 26;
	break;
      case 30: // XO
	etat = 31;
	idbis = XOR;
	break;
      default:
	etat = -1;
      }
      break;
    case L'S':
      switch (etat) {
      case 0: // début
	etat = 21;
	break;
      case 12: // JR
	etat = 999;
	idbis = JRS;
	break;
      default:
	etat = -1;
      }
      break;
    case L'T':
      switch (etat) {
      case 18: // OU
	etat = 999;
	idbis = OUT;
	break;
      case 20: // RE
	etat = 999;
	idbis = RET;
	break;
      case 21: // S
	etat = 24;
	break;
      default:
	etat = -1;
      }
      break;
    case L'U':
      switch (etat) {
      case 16: // O
	etat = 18;
	break;
      case 21: // S
	etat = 27;
	break;
      default:
	etat = -1;
      }
      break;
    case L'X':
      switch (etat) {
      case 0: // debut
	etat = 29;
	break;
      default:
	etat = -1;
      }
      break;
    default:
      switch (etat) {
	case 19: // R
	  id = REGISTRE;
	  if (c == L'0') {
	    idbis = 0;
	    etat = 999;
	  }
	  else if ((c == L'1') || (c == L'2')) {
	    idbis = c-L'0';
	    etat = 32;
	  }
	  else if (c == L'3') {
	    idbis = 3;
	    etat = 33;
	  }
	  else if ((c >= L'4') && (c <= L'9')) {
	    idbis = c-L'0';
	    etat = 999;
	  }
	  else etat = -1;
	  break;
	case 32: // R1 ou R2
	  if ((c >= L'0') && (c <= L'9')) {
	    idbis = 10*idbis+c-L'0';
	    etat = 999;
	  } else etat = -1;
	  break;
	case 33: // R3
	  if ((c == L'0') || (c == L'1')) {
	    idbis = 30+c-L'0';
	    etat = 999;
	  } else etat = -1;
	  break;
	default:
	  etat=-1;
	}
    }
    if (etat != (unsigned int) -1) c = fichier->GetNextChar();
  }

  // on lit jusqu'à atteindre un caractère final.
  if (idbis == (unsigned int) -1) id = ID;
  if (CaracId(c)) id = ID;
  while (CaracId(c)) c = fichier->GetNextChar();
}
