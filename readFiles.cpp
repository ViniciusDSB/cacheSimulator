#include "cache.h"

cacheAccessInfo accesData{};

// Definition of this function is the same as the given method for simbasica
cacheAccessInfo& startCache(int argc, char **argv){

    char nomeArqConfig[100],
		  traceFileName[100];

	FILE *arqConfig;	// Arquivo com configuração da cache

	if (argc != 3){
		printf("\nUso: simbasica arquivoConfiguracao arquivoAcessos\n");
		exit(0);
	}

	// Lê arquivo de configuracao e obtem nBlocos, associatividade e nPalavrasBloco da cache L1
	strcpy(nomeArqConfig, argv[1]);
	arqConfig = fopen(nomeArqConfig, "rt");
	if (arqConfig == NULL){
		printf("\nArquivo de configuração não encontrado\n");
		exit(0);
	}

	// Reads the lines of the config file and stores the data
	for( int i{}; !feof(arqConfig); i+=3){
		fscanf( arqConfig, "%u %u %u", 
			&accesData.cacheConfigs[i], 
			&accesData.cacheConfigs[i+1], 
			&accesData.cacheConfigs[i+2]
		);
	}

	fclose(arqConfig);
	printf("Configs have been read! \n");

	// Abre arquivo de acessos
	strcpy(traceFileName, argv[2]);
    accesData.traceFile = fopen(traceFileName, "rt");
	if (accesData.traceFile == NULL)
	{
		printf("\nArquivo de acessos não encontrado\n");
		exit(0);
	}
	
    return accesData;
}