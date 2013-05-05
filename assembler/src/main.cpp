#include <iostream>
#include <fstream>
#include <cwchar>

// debug de lexique.
#include "lexique.hpp"

int main(int argc, char* argv[]) {
  setlocale(LC_ALL, ""); // pour ne pas avoir de problème avec les accents.
  if (argc != 3) {
    std::wcout << L"Erreur critique : deux noms de fichiers requis !" << std::endl;
    return 1;
  }

  //std::locale old_locale;
  //  std::locale utf8_locale(old_locale,std::codecvt_utf8);
  
  FILE* in = fopen(argv[1], "r");
		   /*in.open(argv[1], std::ios::in | std::ios::binary);
  //in.imbue(std::locale(utf8_locale));
  if (!in.is_open()) {
    std::wcout << argv[0] << " n'existe pas." << std::endl;
    return 1;
    }*/
  FILE* out = fopen(argv[2], "w");
  UniLex::SetFichier(in);
  UniLex x;
  x.Read();
  while (x.GetId() != E_O_F) {
    switch (x.GetId()) {
    case UNDEFINED:
      fwprintf(out, L"UNDEFINED : %ls ", x.GetSymb().GetText());
      std::wcout << x.GetSymb().GetText() << std::endl;
      break;
    case DATA:
      fwprintf(out, L"DATA ");
      break;
    case CODE:
      fwprintf(out, L"CODE ");
      break;
    case INSTR:
      fwprintf(out, L"INSTR : %d ", x.GetIdbis());
      break;
    case REGISTRE:
      fwprintf(out, L"REG : %d ", x.GetIdbis());
      break;
    case NOMBRE:
      fwprintf(out, L"NOMBRE : %d ", x.GetIdbis());
      break;
    case ID:
      fwprintf(out, L"ID : %ls ", x.GetSymb().GetText());
      std::wcout << x.GetSymb().GetText() << std::endl;
      break;
    case DEUX_POINTS:
      fwprintf(out, L"DEUX_POINTS ");
      break;
    case VIRGULE:
      fwprintf(out, L"VIRGULE ");
      break;
    case FIN_LIGNE:
      fwprintf(out, L"FIN_LIGNE\n");
      break;
    case PLUS:
      fwprintf(out, L"PLUS ");
      break;
    case FOIS:
      fwprintf(out, L"FOIS ");
      break;
    case MOINS:
      fwprintf(out, L"MOINS ");
      break;
    case DIV:
      fwprintf(out, L"DIV ");
      break;
    case EXP:
      fwprintf(out, L"EXP ");
      break;
    case MODULO:
      fwprintf(out, L"MOD ");
      break;
    case PGAUCHE:
      fwprintf(out, L"PGAUCHE ");
      break;
    case PDROITE:
      fwprintf(out, L"PDROITE ");
      break;

    default:
      fwprintf(out, L"ERREUR ");
    }
    x.Read();
  }
  return 0;
}
