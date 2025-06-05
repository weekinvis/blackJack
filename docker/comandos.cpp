#include "comandos.hpp"
#include <functional>
#include <string>
#include <map>

using std::function;
using std::string;
using std::map;

string comando;

#ifdef _WIN32
    const bool win32 = true;
#else 
    const bool win32 = false;
#endif

static inline void cmdLimparTerminalWindows() {
    system("cls");
}

static inline void cmdLimparTerminalLinux() {
    system("clear");
}

void cmdLimparTerminal() {
    if(win32) cmdLimparTerminalWindows();
    else      cmdLimparTerminalLinux();
}

void cmdEncerrarExecucao() {
    exit(0);
}

static const map<string, function<void()>> comandosSemArg {
    {"limpar", cmdLimparTerminal},
    {"encerrar", cmdEncerrarExecucao}
};

bool processaComando(const string& comando)
{
    auto it = comandosSemArg.find(comando);

    if(it != comandosSemArg.end()) {
        it->second();
        return true;
    } 
    return false;

}