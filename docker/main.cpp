#include "comandos.hpp"
#include "docker.hpp"
#include "util.hpp"
#include <iostream>

using std::cout;
using std::cin;

int main(int argc, char *argv[])
{
    preset(argv[0]);
    cmdLimparTerminal();
    cout << ENTRADA;
    utilRecuperarDados();
    cout << "Digite o nome do seu docker: ";
    getline(cin, dockerName);

    while(true)
    {
        cout << ">>> ";
        getline(cin, comando);
        processaComando(comando);

    }

    return 0;
}