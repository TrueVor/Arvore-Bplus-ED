#include <iostream>
#include <fstream>
#include <stdexcept>
#include "tiposPacote.hpp"

using namespace std;

class arvoreB {
    friend class sequenceset;
    private:
        pacote* Raiz;
        unsigned numPacotes;
        pacote* dividirPacote(pacote* umPacote);     
    public:
        arvoreB();
        ~arvoreB();
        void promover(pacote* Pacote1, pacote* Pacote2, unsigned Chave);
        int promoverIndice(pacote* umPacote, unsigned Chave);
        int InserirIndice(pacote* umPacote, unsigned Chave);
        void imprimir(pacote* umPacote, int tam = 0);
        void depurar();
        void buscar(tipoChave chave, pacote* raiz);
};

arvoreB::arvoreB() {
    Raiz = NULL;
    numPacotes = 0;
}

arvoreB::~arvoreB() {
    delete Raiz;
}

pacote* arvoreB::dividirPacote(pacote* umPacote) {
    pacote* novo = new pacote();
    if(umPacote->Pai == NULL){
        pacote* pai = new pacote();

        for(unsigned i = 0; i < CAP_PACOTE/2; i++){
            novo->elementos[i] = umPacote->elementos[i + (CAP_PACOTE/2) + 1];
        }

        pai->elementos[0] = umPacote->elementos[CAP_PACOTE/2];
        pai->numElementos++;

        umPacote->numElementos = CAP_PACOTE/2;
        novo->numElementos = CAP_PACOTE/2;

        pai->Filhos[0] = umPacote;
        pai->Filhos[1] = novo;

        umPacote->Pai = pai;
        novo->Pai = pai;
        pai->Folha = false;

        Raiz = pai;
    } else {
        for(unsigned i = 0; i < CAP_PACOTE/2; i++){
            novo->elementos[i] = umPacote->elementos[i + CAP_PACOTE/2 + 1];
        }

        int pos = promoverIndice(umPacote->Pai, umPacote->elementos[CAP_PACOTE/2].chave);
        umPacote->numElementos = CAP_PACOTE/2;
        novo->numElementos = CAP_PACOTE/2;

        // um função promover precisar retornar uma posição para sabermos em q posição
        // vamos colocar os filhos

        umPacote->Pai->Filhos[pos] = umPacote;
        umPacote->Pai->Filhos[pos+1] = novo;
    }
    return novo;
}

int arvoreB::promoverIndice(pacote* umPacote, unsigned Chave){
    int pos = 0;
    if(umPacote->Pai == NULL){
        Raiz = new pacote();
        Raiz->elementos[0].chave = Chave;
        Raiz->numElementos = 1;
        Raiz->Folha = false;
        umPacote->Pai = Raiz;
    } else {
        if(!umPacote->Pai->cheio()){
            pos = umPacote->Pai->numElementos - 1;
            while(pos >= 0 && umPacote->Pai->elementos[pos].chave > Chave){
                umPacote->Pai->elementos[pos+1] = umPacote->Pai->elementos[pos];
                umPacote->Pai->Filhos[pos+1] = umPacote->Pai->Filhos[pos];
                pos--;
            }
            umPacote->Pai->elementos[pos+1].chave = Chave;
            umPacote->Pai->numElementos++;
        } else {
            pacote* novo = dividirPacote(umPacote->Pai);
            if(Chave <= umPacote->Pai->elementos[CAP_PACOTE/2].chave){
                pos = InserirIndice(umPacote->Pai, Chave);
            } else {
                pos = InserirIndice(novo, Chave);
            }
        }
    }
    return pos;
}

void arvoreB::buscar(tipoChave chave, pacote* raiz) {
    if(raiz->Folha) {
        int aux = 0;
        while(raiz->numElementos > aux and raiz->elementos[aux].chave != chave) aux++;

        if(aux == raiz->numElementos){
            cout << "Chave não encontrada";
        }
        else{
            cout << "(" << raiz->elementos[aux].chave << "/" << raiz->elementos[aux].valor << ")";
        }
    }
    else {
        pacote* auxiliar = raiz;
        int aux = 0;
        while(auxiliar->numElementos > aux and chave > auxiliar->elementos[aux].chave) aux++;

        buscar(chave, auxiliar->Filhos[aux]);
    }
}

int arvoreB::InserirIndice(pacote* umPacote, unsigned Chave){
    int pos = umPacote->numElementos - 1;
    while(pos >= 0 && umPacote->elementos[pos].chave > Chave){
        umPacote->elementos[pos+1] = umPacote->elementos[pos];
        umPacote->Filhos[pos+1] = umPacote->Filhos[pos];
        pos--;
    }
    umPacote->elementos[pos+1].chave = Chave;
    umPacote->numElementos++;
    return pos;
}

void arvoreB::promover(pacote* Pacote1, pacote* Pacote2, unsigned Chave){
    if(Pacote1->Pai == NULL){ // Raiz é o próprio pacote
        // Criando raiz
        Raiz = new pacote();
        Raiz->elementos[0].chave = Chave;
        Raiz->numElementos = 1;
        Raiz->Filhos[0] = Pacote1;
        Raiz->Filhos[1] = Pacote2;
        Raiz->Folha = false;
        Pacote1->Pai = Raiz;
    } else {
        if(!Pacote1->Pai->cheio()){
            int pos = Pacote1->Pai->numElementos - 1;
            while(pos >= 0 && Pacote1->Pai->elementos[pos].chave > Chave){
                Pacote1->Pai->elementos[pos+1] = Pacote1->Pai->elementos[pos];
                Pacote1->Pai->Filhos[pos+1] = Pacote1->Pai->Filhos[pos];
                pos--;
            }
            Pacote1->Pai->elementos[pos+1].chave = Chave;
            Pacote1->Pai->Filhos[pos+2] = Pacote2;
            Pacote1->Pai->numElementos++;
        } else {
            pacote* novo = dividirPacote(Pacote1->Pai);
            if(Chave <= Pacote1->Pai->elementos[CAP_PACOTE/2].chave){
                int pos = InserirIndice(Pacote1->Pai, Chave);
                Pacote1->Pai->Filhos[pos+2] = Pacote2;
            } else {
                int pos = InserirIndice(novo, Chave);
                novo->Filhos[pos+2] = Pacote2;
            }
        }
    }
}

void arvoreB::imprimir(pacote* umPacote, int tam = 0) {
    int aux1 = 0;
    
    // vai entrar se já existir alguma indice na arvore b+
    if(umPacote->numElementos != 0){
        // vai rodar de início o próprio pacote
        for(int i=0; i<tam; i++) cout << "-";
        cout << "->[";
        while(umPacote->numElementos > aux1){
            cout << "(" << umPacote->elementos[aux1].chave << ")";
            
            aux1++;
        }
        cout << "]" << endl;
        aux1 = 0;
        // se os pacotes filhos nao forem folhas
        // criei essa variavel filhosNaoFolha só pra isso mesmo
        if(!umPacote->Filhos[0]->Folha){
            while(umPacote->numElementos >= aux1){
                imprimir(umPacote->Filhos[aux1], tam+1);
                aux1++;
            }
        }
        // se forem
        else{
            pacote* auxiliar = new pacote();
            // vai rodar por todas os pacotes em que o indice aponta
            while(umPacote->numElementos >= aux1){
                // só pra encontrar o pacote no arquivo
                // tive q criar essa funçao nessa classe tbm, igual a da classe de baixo,
                // mas coloquei o nome do arquivo direto ao invés de variavel
                lerPacoteDoArquivo(auxiliar, umPacote->Filhos[aux1]);
                for(int i=0; i<tam+1; i++) cout << "-";
                // imprimir o pacote completo com a funçao do pacote
                cout << "->";
                auxiliar->imprimir();
                cout << endl;
                aux1++;
            }
        }
    }
}

void arvoreB::depurar() {

}


class sequenceset {
    private:
        arvoreB ArvoreB;
        unsigned numPacotes;
        int posPrimeiroPacote;
        int proxPosicaoVazia; 
        string nomeArquivo; 
        inline bool cabecalhoEhConsistente(const cabecalhoArqSS& umCabecalho);
        void atualizarCabecalhoNoArquivo();
        void gravarPacoteNoArquivo(pacote* umPacote, unsigned posicao);
        void lerPacoteDoArquivo(pacote* umPacote, unsigned posicao);
        unsigned encontrarProxPosDisponivel();
        unsigned encontrarPacoteParaInsercao(pacote* umPacote, dado umDado);
        pacote* dividirPacote(pacote* umPacote, unsigned posNovoPacote); 
        dado buscaBinaria(dado vetor[], int inicio, int fim, tipoChave chave);       
    public:
        sequenceset(string arquivo);
        ~sequenceset();
        void inserirDado(dado umDado);
        void imprimir();
        void depurar();
        dado buscar(tipoChave chave);
        /* 
        void remover(tipoChave chave);
        */
};

sequenceset::sequenceset(string arquivo) {
    nomeArquivo = arquivo;
    ifstream arqEntrada(nomeArquivo);
    cabecalhoArqSS cabecalho;

    // verifica se o arquivo existe, se sim, lê o cabeçalho 
    // e verifica se os dados são consistentes com a configuração
    // do sequence set
    if ( arqEntrada ) {
        arqEntrada.read((char*) &cabecalho, sizeof(cabecalhoArqSS));
        arqEntrada.close();
        if (not cabecalhoEhConsistente(cabecalho)) {
            throw runtime_error("Aplicação usa configuração diferente das usadas no arquivo");
        }
        // atualiza os dados do sequence set de acordo com o cabeçalho do arquivo
        numPacotes = cabecalho.numPacotes;
        posPrimeiroPacote = cabecalho.posPrimeiroPacote;
        proxPosicaoVazia = cabecalho.proxPosicaoVazia;
    } 
    // não existe o arquivo de entrada ainda, inicializa novo sequence set
    // e salva o cabeçalho no arquivo
    else { 
        numPacotes = 0;
        posPrimeiroPacote = POS_INVALIDA;
        proxPosicaoVazia = POS_INVALIDA;
        // cria o arquivo
        ofstream ArqSaida(nomeArquivo);
        ArqSaida.close();
        atualizarCabecalhoNoArquivo();
    }    
}

sequenceset::~sequenceset() {
    // apenas atualiza o cabeçalho, para garantir que esteja tudo ok
    atualizarCabecalhoNoArquivo(); 
}

bool sequenceset::cabecalhoEhConsistente(const cabecalhoArqSS& umCabecalho) {
    return ((umCabecalho.capacidadeMaxPacote == CAP_PACOTE)
             and (umCabecalho.capacidadeMinPacote == MIN_PACOTE)
             and (umCabecalho.posicaoMeio == POS_MEIO));    
}

void sequenceset::atualizarCabecalhoNoArquivo() {
    cabecalhoArqSS cabecalho; 
    cabecalho.capacidadeMaxPacote = CAP_PACOTE;
    cabecalho.capacidadeMinPacote = MIN_PACOTE;
    cabecalho.posicaoMeio = POS_MEIO;
    cabecalho.numPacotes = numPacotes;
    cabecalho.posPrimeiroPacote = posPrimeiroPacote;
    cabecalho.proxPosicaoVazia = proxPosicaoVazia;
    // precisa ser fstream para não apagar o arquivo já existente
    fstream arqSaida(nomeArquivo, ios::in | ios::out);
    arqSaida.write((const char*) &cabecalho, sizeof(cabecalhoArqSS));
    arqSaida.close();    
}

void sequenceset::lerPacoteDoArquivo(pacote* umPacote, unsigned posicao) {
     // pula o cabeçalho do arquivo e o número de páginas anteriores
    unsigned posArq = sizeof(cabecalhoArqSS) + posicao*sizeof(pacote);  
    fstream arqEntrada(nomeArquivo, ios::in | ios::out);
    arqEntrada.seekg(posArq);
    arqEntrada.read((char*) umPacote, sizeof(pacote));
    arqEntrada.close();    
}


void sequenceset::gravarPacoteNoArquivo(pacote* umPacote, unsigned posicao) {
     // pula o cabeçalho do arquivo e o número de páginas anteriores
    unsigned posArq = sizeof(cabecalhoArqSS) + posicao*sizeof(pacote); 
    // precisa ser fstream para não apagar o arquivo já existente
    fstream arqSaida(nomeArquivo, ios::in | ios::out);
    arqSaida.seekp(posArq);
    arqSaida.write((const char*) umPacote, sizeof(pacote));
    arqSaida.close();   
}

unsigned sequenceset::encontrarProxPosDisponivel() {
    // se não tem pacote vazio no meio do arquivo
    // então a próxima posição disponível será uma posição a mais
    // que a última do arquivo (numPacotes-1)
    if (proxPosicaoVazia == POS_INVALIDA) {
        return numPacotes;  
    } else {
        // este trecho código só é útil com remoção
        // como ainda não temos remoção, então gera exceção
        throw runtime_error("Não era para proxPosicaoVazia ser diferente de POS_INVALIDA");

        // reaproveitar primeira posição vazia
        unsigned posicao = proxPosicaoVazia;
        pacote* pacoteInvalido = new pacote();
        lerPacoteDoArquivo(pacoteInvalido, proxPosicaoVazia);
        proxPosicaoVazia = pacoteInvalido->posProximoPacote;
        return posicao; 
    }
}



void sequenceset::inserirDado(dado umDado) {
    unsigned posicao;
    pacote* pacoteDestino = new pacote();
    posicao = encontrarPacoteParaInsercao(pacoteDestino, umDado);
    pacoteDestino->posicao = posicao;
    // pacote está cheio, precisa dividir
    if ( pacoteDestino->cheio() ) {
        unsigned posicaoNovoPacote = encontrarProxPosDisponivel();
        pacote* novoPacote = dividirPacote(pacoteDestino, posicaoNovoPacote);
        novoPacote->posicao = posicaoNovoPacote;
        ArvoreB.promover(pacoteDestino, novoPacote, novoPacote->elementos[0].chave);
        if ( umDado.chave > novoPacote->elementos[0].chave )
            novoPacote->inserir(umDado);
        else 
            pacoteDestino->inserir(umDado);
        gravarPacoteNoArquivo(pacoteDestino, posicao);
        gravarPacoteNoArquivo(novoPacote, posicaoNovoPacote);
        delete novoPacote;
        numPacotes++;
        atualizarCabecalhoNoArquivo();
    }
    else {
        pacoteDestino->inserir(umDado);
        gravarPacoteNoArquivo(pacoteDestino, posicao);
    }
    delete pacoteDestino;
}

// o método encontrarPacoteParaInsercao retorna dois elementos:
// um pacote, já carregado do disco, em que será feita a inserção
// e a posição relativa desse pacote no disco, para facilitar
// a gravação posterior, após alterações
// o método recebe um pacote recém-criado e o dado para busca
unsigned sequenceset::encontrarPacoteParaInsercao(pacote* umPacote, dado umDado) {
    // caso vetor expansível esteja vazio, criar primeiro pacote
    if (posPrimeiroPacote == POS_INVALIDA) {
        posPrimeiroPacote = encontrarProxPosDisponivel();
        numPacotes = 1;
        atualizarCabecalhoNoArquivo();
        return posPrimeiroPacote;
    }
    // sequence set não está vazio: procura o pacote para inserir o elemento
    else {
        pacote* proximoPacote = new pacote();
        lerPacoteDoArquivo(umPacote, posPrimeiroPacote);
        if(umPacote->posProximoPacote != POS_INVALIDA) {
            lerPacoteDoArquivo(proximoPacote, umPacote->posProximoPacote);
        }
        unsigned posicao = posPrimeiroPacote;

        // este laço vai lendo pacotes do disco, enquanto a chave
        // for maior que os valores do pacote atual
        while ( (umPacote->posProximoPacote != POS_INVALIDA)
                 and (umPacote->chaveEhMaiorQueTodos(umDado.chave))
                 and (not proximoPacote->chaveEhMenorQueTodos(umDado.chave)) ) {
            posicao = umPacote->posProximoPacote;
            lerPacoteDoArquivo(umPacote, posicao);
            lerPacoteDoArquivo(proximoPacote, umPacote->posProximoPacote);
        }
        return posicao;
    }
}



pacote* sequenceset::dividirPacote(pacote* umPacote, unsigned posNovoPacote) {
    pacote* novo = new pacote();
    // copia metade superior dos dados do pacote atual para o novo
    for (unsigned i = 0; i <= CAP_PACOTE/2; i++) {
        novo->elementos[i] = umPacote->elementos[i + CAP_PACOTE/2];
    }

    Indice auxiliar;
    auxiliar.chave = novo->elementos[0].chave;
    auxiliar.pacoteMenorQueChave = umPacote->posicao;
    auxiliar.pacoteDaChave = posNovoPacote;

    novo->posProximoPacote = umPacote->posProximoPacote;
    umPacote->posProximoPacote = posNovoPacote;
    novo->numElementos = CAP_PACOTE - CAP_PACOTE/2;
    umPacote->numElementos = CAP_PACOTE/2; 
    return novo;
}

dado sequenceset::buscar(tipoChave chave) {
    if (posPrimeiroPacote == POS_INVALIDA) {
        throw runtime_error("Busca: Sequence Set vazio.");
    }
    // sequence set não está vazio: 
    // procura o pacote que poderia conter o elemento
    else {
        pacote* umPacote = new pacote();
        lerPacoteDoArquivo(umPacote, posPrimeiroPacote);

        // este laço vai lendo pacotes do disco, enquanto a chave
        // for maior que os valores do pacote atual
        while ( (umPacote->posProximoPacote != POS_INVALIDA)
                 and (umPacote->chaveEhMaiorQueTodos(chave)) ) {
            lerPacoteDoArquivo(umPacote, umPacote->posProximoPacote);
        }
        // ou o dado está no pacote que saiu do while 
        // ou não existe no sequence set - precisa agora buscar o elemento no 
        // vetor de elementos

        return buscaBinaria(umPacote->elementos, 0, umPacote->numElementos-1, chave);
    } 
}

//funcao de busca binaria recursiva
dado sequenceset::buscaBinaria(dado vetor[], int inicio, int fim, tipoChave chave) {
    int meio = (inicio+fim)/2;

    if (inicio <= fim) {
        if (chave > vetor[meio].chave)
            return buscaBinaria(vetor,meio+1,fim,chave);
        else if (chave < vetor[meio].chave)
            return buscaBinaria(vetor,inicio,meio-1,chave);
        else
            return vetor[meio];
    } else { // inicio == fim, ou seja, não há mais o que buscar
        // retornamos -1 para indicar posição não encontrada
        throw runtime_error("Busca: elemento não encontrado.");
    } 
}


void sequenceset::imprimir() {

    if (numPacotes > 0) {
        pacote* auxiliar = new pacote();
        lerPacoteDoArquivo(auxiliar,posPrimeiroPacote);
        
        while (auxiliar->posProximoPacote != POS_INVALIDA) {
            auxiliar->imprimir();
            cout << "->";
            lerPacoteDoArquivo(auxiliar,auxiliar->posProximoPacote);
        }
        auxiliar->imprimir();
        delete auxiliar;
    }
    cout << endl;  
}

void sequenceset::depurar() {
    cout << "-*- Dados do Sequence Set -*-" << endl
         << "Número de pacotes: " << numPacotes << endl
         << "Posição do primeiro pacote: " << posPrimeiroPacote << endl
         << "Próxima posição vazia (-1 se não tiver remoção): " << proxPosicaoVazia << endl;
    if (numPacotes > 0) {
        cout << "Dados dos pacotes no formato: "
             << "{posição do pacote}(número de elementos/próximo pacote)[elementos]"
             << endl;
        pacote* auxiliar = new pacote();
        unsigned posicao = posPrimeiroPacote;
        lerPacoteDoArquivo(auxiliar,posPrimeiroPacote);
        
        while (auxiliar->posProximoPacote != POS_INVALIDA) {
            cout << "{" << posicao << "}" 
                 << "(" << auxiliar->numElementos << "/" 
                 << auxiliar->posProximoPacote << ")";
            auxiliar->imprimir();
            cout << "->";
            posicao = auxiliar->posProximoPacote;
            lerPacoteDoArquivo(auxiliar,auxiliar->posProximoPacote);
        }
        cout << "(" << auxiliar->numElementos << "/" 
             << auxiliar->posProximoPacote << ")";
        auxiliar->imprimir();
        delete auxiliar;
    }
    cout << endl << "-*- Fim dos Dados -*-" << endl;  
}


