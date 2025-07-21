#include "blackjack.hpp"
#include <iostream>

using std::cout; using std::cin;

int main()
{
    char continuar;
    
    do {
        jogo novojogo;
        cout << "\nDeseja Continuar? (s ou S)\n";
        cout << "> ";
        cin >> continuar;
        cin.ignore();
    } while(continuar == 's' || continuar == 'S');

    return 0;
}
