#include <iostream>
#include "configuracao.hpp"

using namespace std;

// essa classe também poderia se chamar bloco, pagina, packet ou pedaco
class pacote {
    friend class arvoreB;
    friend class sequenceset;
    // classe não possui métodos públicos
    // objetos da classe são criados e manuseados
    // apenas pela classe sequenceset
    private:
        pacote* Pai;
        pacote* Filhos[CAP_PACOTE+1];
        dado elementos[CAP_PACOTE];
        bool Folha; // Boolean para checar se o Pacote é Folha (True) ou Índice (False).
        unsigned numElementos;
        int posProximoPacote;
        int posicao;
        pacote(): Pai(NULL), numElementos(0), posProximoPacote(POS_INVALIDA) { for(int i = 0; i < CAP_PACOTE+1; i++) Filhos[i] = NULL; }
        ~pacote();
        bool cheio() { return (numElementos == CAP_PACOTE); }
        void inserir(dado umDado);
        inline bool chaveEhMaiorQueTodos(tipoChave chave);
        inline bool chaveEhMenorQueTodos(tipoChave chave);
        void imprimir();
};

pacote::~pacote() {
    for(int i = 0; i < CAP_PACOTE+1; i++){
        delete Filhos[i];
    }
}

void pacote::inserir(dado umDado) {
    int posicao = numElementos - 1;
    // Faz a procura pela posição de inserção do elemento de forma decrescente
    while ( (posicao >= 0) and umDado.chave < elementos[posicao].chave) {
        elementos[posicao+1] = elementos[posicao];
        posicao--;
    }
    elementos[posicao+1] = umDado;
    numElementos++;
}

void pacote::imprimir() {
    cout << posicao << "[";
    for (unsigned i = 0; i < numElementos; i++)
        cout << "(" << elementos[i].chave << "/" << elementos[i].valor << ")";
    cout << "] ";
}

bool pacote::chaveEhMaiorQueTodos(tipoChave chave) {
    return ( elementos[numElementos-1].chave < chave );
}

bool pacote::chaveEhMenorQueTodos(tipoChave chave) {
    return ( elementos[0].chave > chave );
}