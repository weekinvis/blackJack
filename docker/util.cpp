#include "util.hpp"
#include <fstream>
#include <string>

using std::string;

extern bool win32;

string ENTRADA;

bool dadosRecuperados;

bool utilRecuperarDados() 
{
    return false;
}

void defineEntradaESaida(char argv[]) {
    std::string caminhoExecutavel(argv);
    std::string diretorioBase;

#ifdef _WIN32
    size_t pos = caminhoExecutavel.find_last_of("\\/");
    diretorioBase = caminhoExecutavel.substr(0, pos);
    diretorioBase += "\\arqvs";
    system(("mkdir \"" + diretorioBase + "\" >nul 2>nul").c_str());

    ENTRADA = diretorioBase + "\\in.txt";
#else
    size_t pos = caminhoExecutavel.find_last_of("/");
    diretorioBase = caminhoExecutavel.substr(0, pos);
    diretorioBase += "/arqvs";
    system(("mkdir -p \"" + diretorioBase + "\"").c_str());

    ENTRADA = diretorioBase + "/in.txt";
#endif
}

void preset(char argv[]) {
    if(win32)
    {
        system("mkdir dadosUsuario >nul 2>nul");
    } else 
    {
        system("mkdir -p dadosUsuario");
    }
    defineEntradaESaida(argv);
}