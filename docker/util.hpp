#pragma once
#ifndef bdop_util_hpp__
#define bdop_util_hpp__

#include <string>

extern std::string ENTRADA;

extern bool dadosRecuperados;

void preset(char argv[]);
bool utilRecuperarDados();
void defineEntradaESaida(char argv[]);

#endif