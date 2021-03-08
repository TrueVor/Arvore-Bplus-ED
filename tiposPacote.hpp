#include <iostream>
#include "configuracao.hpp"

using namespace std;

// essa classe também poderia se chamar bloco, pagina, packet ou pedaco
class pacote {
    friend class sequenceset;
    // classe não possui métodos públicos
    // objetos da classe são criados e manuseados
    // apenas pela classe sequenceset
    private:
        dado elementos[CAP_PACOTE];
        unsigned numElementos;
        int posProximoPacote;
        int posicao;
        pacote(): numElementos(0), posProximoPacote(POS_INVALIDA) { }
        bool cheio() { return (numElementos == CAP_PACOTE); }
        void inserir(dado umDado);
        inline bool chaveEhMaiorQueTodos(tipoChave chave);
        inline bool chaveEhMenorQueTodos(tipoChave chave);
        void imprimir();
};

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



class pacoteIndice {
    friend class arvoreB;
    friend class sequenceset;
    // classe não possui métodos públicos
    // objetos da classe são criados e manuseados
    // apenas pela classe sequenceset
    private:
        Indice elementos[CAP_PACOTE];
        unsigned numElementos;
        int posProximoPacote;
        int posicao;
        pacoteIndice(): numElementos(0), posProximoPacote(POS_INVALIDA) { }
        bool cheio() { return (numElementos == CAP_PACOTE); }
        void inserir(Indice umIndice);
        inline bool chaveEhMaiorQueTodos(tipoChave chave);
        inline bool chaveEhMenorQueTodos(tipoChave chave);
        void imprimir();
};

void pacoteIndice::inserir(Indice umIndice) {
    int posicao = numElementos - 1;
    // Faz a procura pela posição de inserção do elemento de forma decrescente
    while ( (posicao >= 0) and umIndice.chave < elementos[posicao].chave) {
        elementos[posicao+1] = elementos[posicao];
        posicao--;
    }
    elementos[posicao+1] = umIndice;
    numElementos++;
}

void pacoteIndice::imprimir() {
    cout << posicao << "[";
    for (unsigned i = 0; i < numElementos; i++)
        cout << "(" << elementos[i].chave << "/" << elementos[i].pacoteMenorQueChave
            << "/" << elementos[i].pacoteDaChave << ")";
    cout << "]";
}

bool pacoteIndice::chaveEhMaiorQueTodos(tipoChave chave) {
    return ( elementos[numElementos-1].chave < chave );
}

bool pacoteIndice::chaveEhMenorQueTodos(tipoChave chave) {
    return ( elementos[0].chave > chave );
}