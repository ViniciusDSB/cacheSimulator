#include "cache.h"

int main(int argc, char **argv){

    using namespace cache;

    cacheAccesData newCacheData = startCache(argc, argv);
    cache::Cache& cache1 = newCacheData.newCache;

    auto myBlocks = cache1.getBlocks();

    return 0;
}

void finishProgram(cacheAccesData cacheAccessData){

	// Imprime medidas de desempenho
	printf("nAcessosI: %d\n", cacheAccessData.numOfInstructionAccess);
	printf("nAcessosD: %d\n", cacheAccessData.numOfDataAccess);
	printf("nFalhasL1: %d\n", cacheAccessData.numOfL1Failure);

	// Libere estrutura de dados da cache e do cacheAccessData com os destrutores.
}