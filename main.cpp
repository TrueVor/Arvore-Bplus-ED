/*
    Trabalho de Estrutura de Dados
    Comparativo de Processadores para Notebooks
    Copyright 2020 by Izabelle Tomé, Mateus Margotti, Mateus Fratini
    Arquivos utilizados pelo algoritmo:
        -> teste.input (Arquivo que contém as entradas do programa)
        -> teste.dat (Arquivo onde o SequenceSet será salvo)
        -> teste2.dat (Arquivo onde a Árvore B+ será salva)
*/

#include <iostream>
#include <ctime> // para suportar a contagem de tempo na busca pelos elementos
#include "arvoreBmais.hpp"

using namespace std;

int main() {
    sequenceset meuSeqSet("teste.dat");
    arvoreB bMais;
    dado umDado;
    tipoChave umaChave;
    char operacao;

    clock_t buscaSequenceSet;
    clock_t buscaBMais;

    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // inserir
                    cin >> umDado.chave >> umDado.valor;
                    meuSeqSet.inserirDado(umDado);
                    break;
                case 'b': // buscar
                    cin >> umaChave;

                    /*buscaSequenceSet = clock();*/
                    umDado = meuSeqSet.buscar(umaChave);
                    //buscaSequenceSet = (clock() - buscaSequenceSet);

                    /*buscaBMais = clock();
                    umDado = bMais.buscar(umaChave);
                    buscaBMais = (clock() - buscaBMais);*/

                    cout << "Busca: "<< umDado.chave << "/" << umDado.valor << endl;

                    /*cout << endl;
                    cout << "SequenceSet X B+" << endl;
                    cout << "O tempo de busca do elemento no SequenceSet foi de: " << buscaSequenceSet << " milissegundos!" << endl;
                    cout << "O tempo de busca do elemento na B+ foi de: " << buscaBMais << " milissegundos!" << endl;*/
                    
                    break;
                case 'p': // mostrar estrutura
                    meuSeqSet.imprimir();
                    break;
                case 'd': // mostrar estrutura
                    meuSeqSet.depurar();
                    break;
                case 's': // sair
                    // será tratado no while
                    break;
                default:
                    cout << "Opção inválida!" << endl;
            }
        } catch (runtime_error& e) {
            cerr << e.what() << endl;
        }
    } while (operacao != 's');

    return 0;
}
