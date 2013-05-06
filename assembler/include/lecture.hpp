#ifndef LECTURE_HPP
#define LECTURE_HPP

#define SIZE_BUF 4096
#include <cstdio>
#include <string>
//typedef std::basic_ifstream<wchar_t, std::char_traits<wchar_t> > wifstream;

class Lecture {
private :
  FILE* file;
  wchar_t* buffer; // buffer de taille SIZE_BUF
  std::wstring id;
  unsigned int pointer; // pointeur sur buffer (pointe sur le caractère suivant).
  unsigned int line; // ligne courante.
  unsigned int column; // colonne courante.
  wchar_t charcur; // caractère courant.

  inline void IncPointer();
  

public :
  Lecture(FILE *fichier); // prépare la lecture d'un fichier. Le fichier est supposé existant (code de sécurité dans le main()).
  unsigned int GetLine() { return line; }
  unsigned int GetColumn() { return column; }
  wchar_t GetChar() { return charcur; }
  wchar_t GetNextChar(); // incrémente le pointeur en sautant les éventuels commentaires et renvoit le caractère.
  wchar_t* GetString(); // renvoit la chaîne de caractères du lexème courant.

  void newToken(); // saute les espaces et les tabulations, et efface la chaîne de caractère du lexème précédent.

  ~Lecture(); // ferme le fichier, et désalloue les buffers.

};

#endif
