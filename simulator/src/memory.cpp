#include "memory.hpp"
#include <iostream>

Memory::Memory(int32_t* _addr, int32_t* _in, int32_t* _out)
{
    addr = _addr;
    in = _in;
    out = _out;
    for (int i = 0; i < 65536; i++) memory[i] = 0;
}

void Memory::load ()
{
  int32_t cluster = *addr >> 16;
  if (memory[cluster] == 0) memory[cluster] = new int32_t[N];
  if (memory[cluster] == 0) { // pas pu allouer la mémoire X(
    std::cerr << "Erreur : dépassement de mémoire." << std::endl;
    exit(1);
  }
  *out = memory[cluster][*addr & 0xFFFF];
}

void Memory::store ()
{
  int32_t cluster = *addr >> 16;
  if (memory[cluster] == 0) memory[cluster] = new int32_t[N];
  if (memory[cluster] == 0) {
    std::cerr << "Erreur : dépassement de mémoire." << std::endl;
    exit(1);
  }
  memory[cluster][*addr & 0xFFFF] = *in;
}

