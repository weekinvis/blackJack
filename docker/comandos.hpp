#pragma once
#ifndef bdop_comandos_hpp__
#define bdop_comandos_hpp__

#include <string>
using std::string;

extern string comando;
extern const bool win32;

bool processaComando(const string& comando);
void cmdLimparTerminal();

#endif