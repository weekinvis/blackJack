#include "blackjack.hpp"
#include <iostream>

using std::cin;

static bool forcado = false;

void baralho::obtemBaralhoEmbaralhado()
{
    vector<carta> baralhoProvisorio;

    for(int p = 0; p < QNT_NAIPES; p++) {
        for(int q = 1; q <= QNT_CARTAS/QNT_NAIPES; q++) {
            baralhoProvisorio.emplace_back(((q > 10) ? 10 : q), naipes[p]); // nao existem cartas com valores maiores do que 10. 
        }
    }

    // seed para embaralhar
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    // shuffle
    shuffle(baralhoProvisorio.begin(), baralhoProvisorio.end(), std::default_random_engine(seed));

    for(auto carta : baralhoProvisorio) {
        b_baralho.push(carta);
    }

    baralhoProvisorio.clear();
}

carta baralho::ultimaCarta()
{
    carta ultima = b_baralho.top();
    b_baralho.pop();
    return ultima;
}

void baralho::listaBaralhoAtual()
{
    stack<carta> copia = b_baralho;
    int i = 0;
    while (!copia.empty()) {
        copia.top().getInfo();
        copia.pop();
        i++;
        if(i % (QNT_CARTAS/QNT_NAIPES) == 0) cout << std::endl;
    }

}

void jogo::mostrarSituacao()
{
    cout << this->jogadores.first.getNome() << std::endl;
    this->jogadores.first.showCartas();
    cout << "(" << this->jogadores.first.getSoma() << ")";
    cout << std::endl << std::endl;
    this->jogadores.second.showCartas();
    cout << "(" << this->jogadores.second.getSoma() << ")";
    cout << std::endl << this->jogadores.second.getNome();
}

void jogo::processaTurno() 
{
    static bool jaJogado = false;
    if(!turno)
    {
        int c_valor;
        int d_valor = jogadores.second.c_getSoma();
        d_valor -= jogadores.second.getValueFirst();
        c_valor = jogadores.first.c_getSoma();
        

        if(c_valor >= 17 || d_valor >= 17) 
        {
            turno = !turno;

            cout << "Dealer deseja parar.\n";
            #ifdef _WIN32
                Sleep(1350);
            #else
                sleep(2);
            #endif

            parar.first = true;
            return;
            
        } else 
        {
            cout << "Dealer comprou uma carta.\n";

            #ifdef _WIN32
                Sleep(1750);
            #else
                sleep(2);
            #endif

            turno = !turno;
            parar.first = false; parar.second = false;
            this->jogadores.first.getCarta(this->baralhoUsado.ultimaCarta());

            return;
        }

    } else {

        if(forcado || this->jogadores.second.getSoma() >= 21) 
        {
            turno = !turno;
            parar.second = true;
            return;
        }

        string comando;
        if(!jaJogado) cout << "O que deseja fazer?\nDigite draw para puxar uma carta, digite stop para parar seu turno.\n> ";
        else cout << "O que deseja fazer?\n> ";
        jaJogado = true;
        getline(cin, comando);

        if(comando == "draw") {
            turno = !turno;
            parar.first = false; parar.second = false;
            this->jogadores.second.getCarta(this->baralhoUsado.ultimaCarta());
            return;
        } else if(comando == "stop") {

            turno = !turno;
            parar.second = true;
            return;

        } else if (comando == "!stop") {
            forcado = true;
        }else if(comando == "exit") {
            exit(0);
        }
        else {
            cout << "Comando nao encontrado: digite draw ou stop." << std::endl;
            #ifdef _WIN32
                Sleep(1750);
            #else
                sleep(2);
            #endif
            return;
        }

    }
}

jogo::jogo() 
{
    int p = 0;

    carta cartaAdicionadaInvisivel = this->baralhoUsado.ultimaCarta();
    cartaAdicionadaInvisivel.setVisibilidade(false);
    this->jogadores.first.getCarta(cartaAdicionadaInvisivel);
    this->jogadores.first.getCarta(this->baralhoUsado.ultimaCarta());

    this->jogadores.second.getCarta(this->baralhoUsado.ultimaCarta());
    this->jogadores.second.getCarta(this->baralhoUsado.ultimaCarta());

    while(!(parar.first) || !(parar.second))
    {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        mostrarSituacao();
        cout << "\n";
        processaTurno();
    }

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    jogadores.first.fim();
    mostrarSituacao();

    cout << "\n";

    forcado = false;

    if(jogadores.first.c_getSoma() > 21 && jogadores.second.c_getSoma() < 21) {
        cout << "Parabens, voce venceu!\n";
        return;
    }
    if(jogadores.second.c_getSoma() > 21 && jogadores.first.c_getSoma() < 21) {
        cout << "Voce perdeu!\n";
        return;
    }
    if(21 - jogadores.first.c_getSoma() == 21 - jogadores.second.c_getSoma()) {
        cout << "Empate.\n";
        return;
    }

    if(jogadores.first.c_getSoma() == 21 && jogadores.second.c_getSoma() != 21) {
        cout << "Voce perdeu!\n";
        return;
    }
    if(jogadores.first.c_getSoma() != 21 && jogadores.second.c_getSoma() == 21) {
        cout << "Parabens, voce venceu!\n";
        return;
    }

    int v1 = 21 - jogadores.first.c_getSoma();
    int v2 = 21 - jogadores.second.c_getSoma();

    if(0 > v1 && 0 > v2) {
        if(v1 < v2) {
            cout << "Parabens, voce venceu!\n";
        } else {
            cout << "Voce perdeu!\n";
        }
    } else {
        if(v1 > v2) {
            cout << "Parabens, voce venceu!\n";
        } else {
            cout << "Voce perdeu!\n";
        }
    }

}
