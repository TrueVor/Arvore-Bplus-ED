#include <iostream>
#include <sequenceset.hpp> // relação com o sequence set


struct dado 
{
    unsigned posicao;
    char modelo[30]; // chave
    char cache[15];
    unsigned tdp;
    char frequencia[12];
    char nucleos[6];
    float cinebenchR15Single;
    float cinebenchR15Multi;
    float cinebenchR20;
};

using namespace std;

const int POS_INVALIDA = -1; // faz a marcação no sequence set de quais posições estão vagas
const int capacidade = 6; // capacidade máxima de cada bloco

// cabeçalho para a b+ -> faz referencia aos noh's folha
struct cabecalhoNohsFolha
{
	int nPedacos; // contador para o número de blocos do sequence set
	int primeiroBloco; // variável que armazena qual o primeiro bloco do sequence set
	int ultimoBloco; // variável que armazena qual o último bloco do sequence set
};

// cabeçalho para a b+ -> faz referências para os índices
struct cabecalhoIndices
{
	int nIndice; // contador para o números de índices do sequence set
	int primeiroIndice; // variável que armazena qual o primeiro índice do sequence set
	int ultimoIndice; // variável que armazena qual o último índice do sequence set
};

class Noh
{
	// Falta criar a class e os seus métodos
};

// classe para salvar os índices
class NohIndice
{
	friend class bPlus;
	private:
		int tamIndice;
		// posições no bloco:
		int proximo;
		int anterior;
		int atual;
		string indice;
	public:
		NohIndice(string Modelo)
		{
			anterior = POS_INVALIDA;
			proximo = POS_INVALIDA;
			atual =  POS_INVALIDA;
			indice = Protocolo;
		}
		NohIndice lerIndice(int pos, string arq, int ultimoIndice)
		{
			NohIndice bloco("0");
			ifstream arquivo(arq, ios::binary | ios::in);
			int posicaoLeitura = sizeof(cabecalhoFolhas) + sizeof(Noh)*ultimoIndice + sizeof(cabecalhoIndices)  + sizeof(NohIndice)*pos;
			arquivo.seekg(posicaoLeitura);
			arquivo.read((char *) &pedaco, sizeof(NohIndice));
			arquivo.close();
			return bloco;
		}
};

class bPlus
{
	friend class sequenceset;
	private:
		cabecalhoNohsFolha cabecalhoDaArvore;
		cabecalhoIndices indicesCabecalhos;
		fstream salvaArvore; // manipula o arquivo onde a árvore será salva
		int posArq (int posRelativa); // calcula qual a posição onde o bloco será inserido no arquivo
		int posRaiz; // variável que armazena qual a posição da raiz
		string arq; // nome do arquivo que recebe a árvore
	public:
		bPlus();
		~bPlus()
		{
			salvaArvore.close();
		}
		void insereNaArvore(Noh Bloco); // insere um elemento do sequence set na árvore
		void criaRaiz(); // cria a raiz da árvore
		void imprime(); // imprime a árvore
};

// contrutor da árvore, que cria o arquivo onde a mesma será salva no fim da execução do programa
bPlus::bPlus()
{
	arq = bPlus;
	ifstream arquivoArv(arq);
	if(arquivoArv)
	{
		arquivoArv.read((char*) &cabecalhoDaArvore, sizeof(cabecalhoNohsFolha));
		arquivoArv.close();
	} else
	{
		cabecalhoDaArvore = {0, POS_INVALIDA, POS_INVALIDA};
		ofstream arquivoArv(arq);
		arquivoArv.write((char*)&cabecalhoDaArvore, sizeof(cabecalhoNohsFolha));
		arquivoArv.close();
	}
	salvaArvore.open(arq);
}

int bPlus::posArq(int posRelativa)
{
	return sizeof(cabecalhoNohsFolha) + sizeof(Noh)*posRelativa;
}

void bPlus::insereNaArvore(Noh Bloco)
{
	// inserção dos blocos ordenados no arquivo:
	if(cabecalhoDaArvore.QuantidadePedacos == 0)
	{
		Noh novoBloco = Bloco;
		int PosicaoArq = posArq(novoBloco.PosicaoAtual);
		salvaArvore.seekp(PosicaoArq);
		salvaArvore.write((char*) &novoBloco, sizeof(Noh));
		
		cabecalhoDaArvore.primeiroBloco = 0;
		cabecalhoDaArvore.ultimoBloco = 0;
		cabecalhoDaArvore.QuantidadePedacos = 1;
		salvaArvore.seekp(0);
		salvaArvore.write((char*) &cabecalhoDaArvore, sizeof(cabecalhoNohsFolha));
	} else
	{
		Noh novoBloco = Bloco;
		int PosicaoArq = posArq(novoBloco.PosicaoAtual);
		salvaArvore.seekp(PosicaoArq);
		salvaArvore.write((char*) &novoBloco, sizeof(Noh));
		
		cabecalhoDaArvore.primeiroBloco = 0;
		cabecalhoDaArvore.ultimoBloco = novoBloco.PosicaoAtual;
		cabecalhoDaArvore.QuantidadePedacos+=1;
		salvaArvore.seekp(0);
		salvaArvore.write((char*) &cabecalhoDaArvore, sizeof(cabecalhoNohsFolha));
	}
}

void bPlus::imprimirArvore()
{
	int pos = cabecalhoDaArvore.primeiroBloco;
	while(pos != POS_INVALIDA)
	{
		Noh bloco = bloco.leBloco(pos,arq);
		bloco.imprimir();
		pos = bloco.proximo;
		
	}
	cout << endl;
}

void bPlus::criaRaiz()
{
	// criação do cabeçalho para o índice
	int posicao = sizeof(cabecalhoNohsFolha) + sizeof(Noh)*cabecalhoDaArvore.ultimoBloco + sizeof(cabecalhoIndices);
	indicesCabecalhos.primeiroIndice = POS_INVALIDA;
	indicesCabecalhos.ultimoIndice = POS_INVALIDA;
	indicesCabecalhos.nIndice = 0;
	salvaArvore.seekp(posicao);
	salvaArvore.write((char*) &indicesCabecalhos, sizeof(cabecalhoIndices));
	
	// salvamento no arquivo do primeiro elemento do bloco seguinte:
	int i = cabecalhoDaArvore.primeiroBloco;
	Noh Bloco = Bloco.leBloco(i, arq);
	i = Bloco.proximo;
	string Indice = 0;
	
	Bloco = Bloco.leBloco(i, arq);
	Indice = Bloco.vetDados[0].protocolo;
	
	NohIndice BlocoProtocolo(Indice);
	BlocoProtocolo.atual = 0;
	int pos = sizeof(cabecalhoNohsFolha) + sizeof(Noh)*cabecalhoDaArvore.ultimoBloco + sizeof(cabecalhoIndices) + sizeof(NohIndice)*BlocoProtocolo.atual;
	salvaArvore.seekp(pos);
	salvaArvore.write((char*) &BlocoProtocolo, sizeof(NohIndice));
	posicao = sizeof(cabecalhoNohsFolha) + sizeof(Noh)*cabecalhoDaArvore.ultimoBloco + sizeof(cabecalhoIndices);
	indicesCabecalhos.primeiroIndice = 0;
	indicesCabecalhos.ultimoIndice = 0;
	indicesCabecalhos.nIndice = 1;
	salvaArvore.seekp(posicao);
	salvaArvore.write((char*) &indicesCabecalhos, sizeof(cabecalhoIndices));
	
	Bloco = Bloco.leBloco(i, arq);
	i = Bloco.proximo;
	
	while(i != POS_INVALIDA)
	{
		Bloco = Bloco.leBloco(i, arq);
		Indice = Bloco.VetorDados[0].protocolo;	
		NohIndice blocoNovo(Indice);
		blocoNovo.atual = indicesCabecalhos.nIndice;
		
		int pos = sizeof(cabecalhoNohsFolha) + sizeof(Noh)*cabecalhoDaArvore.ultimoBloco + sizeof(cabecalhoIndices) + sizeof(NohIndice)*blocoNovo.atual;
		salvaArvore.seekp(pos);
		salvaArvore.write((char*) &blocoNovo, sizeof(NohIndice));
		
		indicesCabecalhos.primeiroIndice = blocoNovo.atual;
		indicesCabecalhos.nIndice += 1;
		salvaArvore.seekp(posicao);
		salvaArvore.write((char*) &indicesCabecalhos, sizeof(cabecalhoIndices));
		
		i = Bloco.proximo;
	}

	imprimeArvore();
}