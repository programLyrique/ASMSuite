#ifndef LECTURE_HPP
#define LECTURE_HPP

#define SIZE_BUF 4096
#include <fstream>

struct longstring {
  wchar_t* txt;
  longstring* suiv;
};

class Lecture {
private :
  std::wifstream file;
  wchar_t* buffer; // buffer de taille SIZE_BUF
  longstring id;
  longstring* id_courant; // chaine contenant l'identifiant.
  unsigned int nb_longstring; // taille de la liste de longstrings.
  unsigned int taille_id_courant; // nb de wchar_t dans le longstring courant.
  unsigned int pointer; // pointeur sur buffer.
  unsigned int line; // ligne courante.
  unsigned int column; // colonne courante.

  inline void IncPointer();

public :
  Lecture(const char *filename); // prépare la lecture d'un fichier. Le fichier est supposé existant (code de sécurité dans le main()).
  
  unsigned int GetLine() { return line; }
  unsigned int GetColumn() { return column; }
  wchar_t GetChar() { return buffer[pointer]; } //utilité ???
  wchar_t GetNextChar(); // renvoit le caractère et incrémente le pointeur en sautant les éventuels commentaires).
  wchar_t* GetString(); // renvoit la chaîne de caractères du lexème courant.

  void newToken(); // met à jour les pointeur, et éventuellement le buffer.

  wchar_t Error(); // va à la ligne suivante (pour faire un rattrapage d'erreur en mode panique)
  ~Lecture(); // ferme le fichier, et désalloue les buffers.

};

#endif
