#include "hashtable.hpp"
#include "symbole.hpp"

Hashtable Symbole::hash = Hashtable();

Symbole::Symbole(const wchar_t *name) : e(hash.Add(name)) {}

void Symbole::SetValue(unsigned int n) {
  e->value = n;
  e->init = true;
}

unsigned int Symbole::GetValue() {
  return e->value;
}

const wchar_t* Symbole::GetText() {
  return e->name;
}

bool Symbole::GetInit() {
  return e->init;
}

