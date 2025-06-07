#include "blackjack.hpp"
#include <iostream>

using std::cout; using std::cin;

int main()
{
    char continuar = 's';
    while(continuar == 's' || continuar == 'S') {
        jogo novojogo;
        cout << "\nDeseja Continuar? (s ou S)\n";
        cout << "> ";
        cin >> continuar;
        cin.ignore();
    }

    return 0;
}