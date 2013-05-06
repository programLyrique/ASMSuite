#include "lecture.hpp"
#include <iostream>
#include <fstream>
#include <cwchar>
#include <cstdio>

Lecture::Lecture(FILE* f) {
  //file->open(filename); // ouvre le fichier en lecture.
  file = f;
  buffer = new wchar_t[SIZE_BUF]; // alloue le buffer
  pointer = 0;
  line = 1;
  column = 0;
  
  // lit dans le buffer.
  //file->get(buffer, SIZE_BUF, WEOF); // est-ce que le délimiteur est correct ?
  //file->read(buffer, SIZE_BUF);
  //std::cout << file->gcount() << std::endl;
  //fread(buffer, sizeof(wchar_t), SIZE_BUF, file); // à peut-être remplacer par une boucle de fwgetc
  for (int i = 0; i < SIZE_BUF; i++) {
    buffer[i] = fgetwc(file);
    //std::wcout << buffer[i];
    if (buffer[i] == WEOF) buffer[i] = 0;
  }
  GetNextChar(); // met à jour charcur.
}

inline void Lecture::IncPointer() {
  column++;
  if (++pointer == SIZE_BUF) {
    for (int i = 0; i < SIZE_BUF; i++) {
      buffer[i] = fgetwc(file);
      //std::wcout << buffer[i];
      if (buffer[i] == WEOF) buffer[i] = 0;
    }
    //fread(buffer, sizeof(wchar_t), SIZE_BUF, file); // peut-être non sûr.
    //file->get(buffer, SIZE_BUF, L'\0');
    //file->read(buffer, SIZE_BUF);
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
  id += c;
  charcur = c;
  return c;
}

wchar_t *Lecture::GetString() {
  wchar_t* ch = new wchar_t[id.length()];
  for (int i = 0; i < (int) id.length()-1; i++)
    ch[i] = id[i];
  ch[id.length()-1] = 0;
  return ch;
}

void Lecture::newToken() {
  // saute les espaces et les tabulations.
  wchar_t c;
  c = GetChar();
  while ((c == L' ') || (c == L'\t')) {
    c = GetNextChar();
  }
  id.clear();
  id += GetChar();
}

Lecture::~Lecture() {
  //file->close(); // ou alors déléguer cela au main ?
  delete[] buffer;
}
