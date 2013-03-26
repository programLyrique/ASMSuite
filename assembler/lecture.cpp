#include "lecture.hpp"
#include <iostream>
#include <fstream>
#include <cwchar>

Lecture::Lecture(const char *filename) {
  file.open(filename); // ouvre le fichier en lecture.
  buffer = new wchar_t[SIZE_BUF]; // alloue le buffer
  id.txt = new wchar_t[SIZE_BUF]; // alloue un tampon pour sauvegarder le lexème courant.
  id.suiv = 0;
  id_courant = &id;
  nb_longstring = 0;
  taille_id_courant = 0;
  pointer = 0;
  line = 1;
  column = 0;
  
  // lit dans le buffer.
  file.get(buffer, SIZE_BUF, L'\0'); // est-ce que le délimiteur est correct ?
  //fread(buffer, sizeof(wchar_t), SIZE_BUF, file); // à peut-être remplacer par une boucle de fwgetc
}

inline void Lecture::IncPointer() {
  column++;
  if (++pointer == SIZE_BUF) {
    //fread(buffer, sizeof(wchar_t), SIZE_BUF, file); // peut-être non sûr.
    file.get(buffer, SIZE_BUF, L'\0');
    pointer = 0;
  }
}

wchar_t Lecture::GetNextChar() {
  unsigned int a, b;
  wchar_t c, d;
  c = buffer[pointer]; // lit le caractère courant.
  IncPointer();
  d = buffer[pointer]; // lit le caractère suivant.
  // saute le(s) commentaires /**/
  while((c == L'/') && (d == L'*')) {
    a = line;
    b = column;
    do {
      c = d;
      IncPointer();
      d = buffer[pointer];
      if (c == L'\n') {
	line++;
	column = 0;
      }
      if (c == L'\0') { // pas de fin de commentaire.
	std::wcerr << L"Erreur ligne " << a << L" colonne " << b << L"\u00a0: la fin du commentaire n'a pas été rencontrée." << std::endl;
	break;
      }
    } while ((c != L'*') || (d != L'/'));
    if (c == L'\0') break;
    IncPointer(); // saute le */ final
    c = buffer[pointer];
    IncPointer();
    d = buffer[pointer];
  }
  // supprime le commentaire // (et renvoie \n ou EOF).
  if ((c == L'/') && (d == L'/')) {
    do {
      c = buffer[pointer];
      IncPointer();
    } while ((c != L'\n') && (c != L'\0'));
  }
  if (c == '\n') {
    line++;
    column = 0;
  }
  // copie le caractère dans id_courant
  id_courant->txt[taille_id_courant] = c;
  if (++taille_id_courant == SIZE_BUF) {
    longstring *s = new longstring;
    s->txt = new wchar_t[SIZE_BUF];
    s->suiv = 0;
    id_courant->suiv = s;
    id_courant = s;
    nb_longstring++;
    taille_id_courant = 0;
  }
  return c;
}

wchar_t *Lecture::GetString() {
  unsigned int t = nb_longstring*SIZE_BUF+taille_id_courant;
  wchar_t *res = new wchar_t[t];
  longstring *a = &id;
  unsigned int i;
  for (i = 0; i < nb_longstring; i++) {
    wmemcpy(&(res[i*SIZE_BUF]), a->txt, SIZE_BUF); // copie les chaines.
    a = a->suiv;
  }
  wmemcpy(&(res[i*SIZE_BUF]), a->txt, t % SIZE_BUF);
  res[t-1] = L'\0'; // le dernier caractère lu est rejeté, car il indique la fin du lexème.
}

void Lecture::newToken() {
  longstring *a, *b;
  a = id.suiv;
  while (a != 0) {
    b = a->suiv;
    delete a->txt;
    delete a;
    a = b;
  }
  id.suiv = 0;
  id_courant = &id;
  nb_longstring = 0;
  taille_id_courant = 0;
  // saute les espaces et les tabulations.
  wchar_t c;
  c = GetChar();
  while ((c == L' ') || (c == L'\t')) {
    IncPointer();
    c = GetChar();
  }
}

wchar_t Lecture::Error() {
  wchar_t c;
  do {
    c = GetNextChar();
  } while ((c != L'\n') && (c != L'\0'));
  return c;
}

Lecture::~Lecture() {
  file.close();
  delete buffer;
  delete id.txt;
  longstring *a, *b;
  a = id.suiv;
  while (a != 0) {
    b = a->suiv;
    delete a->txt;
    delete a;
    a = b;
  }
}
