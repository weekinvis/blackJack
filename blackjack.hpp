#pragma once
#ifndef bdop_blackjack_hpp__
#define bdop_blackjack_hpp__

#include <algorithm> // shuffle
#include  <iostream>
#include   <iomanip>
#include    <string>
#include    <random> // std::default_random_engine
#include    <chrono> // std::chrono::system_clock
#include    <vector>
#include     <stack>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using std::setw;

#define QNT_CARTAS 52
#define QNT_NAIPES  4

using std::vector;
using std::string;
using  std::stack;
using   std::pair;
using   std::cout;
//♥♦♣♠
const char naipes[] = {'C', 'O', 'P', 'E'};

class carta
{
    private:
        char   naipe;
        int    valor;  
        bool visivel = true;
    public:
        carta(int valor, char naipe)
        {
            this->valor = valor;
            this->naipe = naipe;
        }

        void getInfo() const
        {
            visivel ? cout << std::left << setw(3) << this->valor : cout << std::left << setw(3) << "?";

        }

        void setVisibilidade(bool visivel)
        {
            this->visivel = visivel;
        }

        int getValue()
        {
            return visivel ? this->valor : 0;
        }

        int c_getValue()
        {
            return this->valor;
        }

};

class baralho
{
    private:
        stack<carta> b_baralho;
        void obtemBaralhoEmbaralhado();
        
    public:
        void listaBaralhoAtual();
        carta ultimaCarta();

        baralho()
        {
            obtemBaralhoEmbaralhado();
        }

};

class jogador
{
    private:
        string nome;
        vector<carta> j_cartas;
    public:
        jogador(string nome)
        {
            this->nome = nome;
        }

        void getCarta(carta cartaObtida) { j_cartas.push_back(cartaObtida); }

        string getNome() { return this->nome; }

        void showCartas() { for(carta it : j_cartas) { it.getInfo(); std::cout << " "; } }

        int getSoma() { int total = 0; for(carta it : j_cartas) { total += it.getValue(); } return total; }

        int c_getSoma() { int total = 0; for(carta it : j_cartas) { total += it.c_getValue(); } return total; }

        void fim() { j_cartas[0].setVisibilidade(true); }

        int getValueFirst() { return j_cartas[0].getValue(); }

};

class jogo
{
    private:
        baralho baralhoUsado;               // Ja esta embaralhado
        pair<jogador, jogador> jogadores = {jogador("Dealer"), jogador("Usuario")};
        pair<bool, bool> parar = {false, false};
        bool turno = true;

        void mostrarSituacao();
        void processaTurno();
    public:
        jogo();
        

};

#endif
