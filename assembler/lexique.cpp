#include "lecture.hpp"
#include "lexique.hpp"
#include "symbole.hpp"

void Unilex::Read() {
  fichier->NewToken();
  line = fichier->GetLine();
  column = fichier->GetColumn();
  // automate...
  wchar_t c = fichier->GetNextChar();
  switch (c) {
  case L':':
    id = DEUX_POINTS;
    break;
  case L',':
    id = VIRGULE;
    break;
  case L'\n':
    id = FIN_LIGNE;
    break;
  case L'+':
    id = PLUS;
    break;
  case L'-':
    id = MOINS;
    break;
  case L'*':
    id = FOIS;
    break;
  case L'/':
    id = DIV;
    break;
  case L'^':
    id = EXP;
    break;
  case L'%':
    id = MODULO;
    break;
  case L'(':
    id = PGAUCHE;
    break;
  case L')':
    id = PDROITE;
    break;
  case L'\0':
    id = E_O_F;
    break;
  case L'.':
    // .DATA ou .CODE ou .BSS (ou UNDEFINED)
  default: // autres cas : INSTR, REGISTRE, NOMBRE, ID (ou UNDEFINED)
    if ((c >= L'0') && (c <= L'9')) {
      id = NOMBRE;
      idbis = c - L'0';
      this->Nbr();
    }
    else Automate(c);
  }
}
