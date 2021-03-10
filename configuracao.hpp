using namespace std;

struct elemento {
    unsigned chave;
    char valor[10];
};

struct elementoNaoFolha {
    unsigned chave;
    int pacoteRaiz;
    unsigned pacoteMenorQueChave;
    unsigned pacoteDaChave;
    bool apontaParaFolha;
    elementoNaoFolha(): pacoteRaiz(-1), apontaParaFolha(true) {}
};

struct cabecalhoArqSS {
    unsigned capacidadeMaxPacote; 
    unsigned capacidadeMinPacote;
    unsigned posicaoMeio;  
    unsigned numPacotes;
    int posPrimeiroPacote;  
    int proxPosicaoVazia;   // para poder reaproveitar pacotes que 
                            // fiquem vazios no meio do arquivo
};

typedef elemento dado; // a arvore guarda informacoes do tipo Dado
typedef elementoNaoFolha Indice;
typedef unsigned tipoChave; // tipo da chave usada na comparação

// capacidade máxima e mínima do pacote
const unsigned CAP_PACOTE = 4;
const unsigned MIN_PACOTE = 2;

// posição do elemento do meio do pacote
const unsigned POS_MEIO = 1;

// posição inválida no disco
const int POS_INVALIDA = -1;
