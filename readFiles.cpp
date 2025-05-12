#include "cache.h"

// Definition of this function is the same as the given method for simbasica
cacheAccesData startCache(int argc, char **argv){

    char nomeArqConfig[100],
		  traceFileName[100];

	unsigned int nBlocosL1,				// Número total de blocos da cache L1
					 associatividadeL1,	// Número de blocos por conjunto da cache L1
					 nPalavrasBlocoL1;	// Número de palavras do bloco da cache L1

	FILE *arqConfig;	// Arquivo com configuração da cache
    cacheAccesData newAccesData{};

	if (argc != 3)
	{
		printf("\nUso: simbasica arquivoConfiguracao arquivoAcessos\n");
		exit(0);
	}

	// Lê arquivo de configuracao e obtem nBlocos, associatividade e nPalavrasBloco da cache L1
	strcpy(nomeArqConfig, argv[1]);
	arqConfig = fopen(nomeArqConfig, "rt");
	if (arqConfig == NULL)
	{
		printf("\nArquivo de configuração não encontrado\n");
		exit(0);
	}
	fscanf(arqConfig, "%d %d %d", &nBlocosL1, &associatividadeL1, &nPalavrasBlocoL1);
	fclose(arqConfig);

	// Abre arquivo de acessos
	strcpy(traceFileName, argv[2]);
    newAccesData.traceFile = fopen(traceFileName, "rt");
	if (newAccesData.traceFile == NULL)
	{
		printf("\nArquivo de acessos não encontrado\n");
		exit(0);
	}

	// Inicializa medidas de desempenho
	newAccesData.numOfInstructionAccess = 0;
	newAccesData.numOfDataAccess = 0;
	newAccesData.numOfL1Failure = 0;

	// Aloca e inicializa estrutura de dados da cache L1
	cache::Cache newCache{nBlocosL1, associatividadeL1, nPalavrasBlocoL1};
    newAccesData.newCache = newCache;
    return newAccesData;
}