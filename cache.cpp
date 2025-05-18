#include "cache.h"

namespace cache
{
// Definition of Cache constructor:
Cache::Cache(){} 
Cache::Cache(unsigned numOfBlocks, unsigned assoc, unsigned numOfWordsPerBlock)
{
    this->numOfBlocks = numOfBlocks;
    this->assoc = assoc;
    this->numOfWordsPerBlock = numOfWordsPerBlock;
    this->numOfSets = (numOfBlocks/assoc);

    this->blocks = new Block [numOfBlocks]{};
}

Cache::~Cache()
{
    delete[] blocks;
    std::cout << "Blocks freed!" << std::endl;
}

int Cache::findInsert(int address)
{
    
    int wordAddress,
		 blockAddres,
		 setIndex,
		 realIndex,
		 tag,
		 indexHit,	// Posição que causou acerto
		 freeIndex,	// Primeira posição livre encontrada no conjunto
		 iLRU,		// Posição com menor valor de ordemAcesso no conjunto (bloco LRU)
		 minOrder,	// Dentre as posições ocupadas no conjunto, menor valor de ordemAcesso
		 maxOrder,	// Dentre as posições ocupadas no conjunto, maior valor de ordemAcesso
		 result;

	// Interpreta bits do endereço de memória acessado
	wordAddress = address / N_BYTES_PALAVRA;
	blockAddres = wordAddress / numOfWordsPerBlock;
	setIndex = blockAddres % numOfSets;
	realIndex = setIndex * assoc;
	tag = blockAddres / numOfSets;

	// Procura dado na cache
	indexHit 	= -1;
	freeIndex   = -1;
	iLRU    	= -1;
	minOrder	= INT_MAX;
	maxOrder	= -1;    
    
	// Iterate through every block in the set
    for(unsigned i{}; i < assoc; i++){
        
		//Checks if there is any data in the block
        if( blocks[realIndex + i].validityBit == 1 ){
			
			// Checks if its the data we are looking for
			if( blocks[realIndex + i].tag == tag )
				indexHit = (realIndex + i);
			
			// Checkd the LRU block order
			if(maxOrder < blocks[realIndex + i].accessOrder)
				maxOrder = blocks[realIndex + i].accessOrder;
			
			if( minOrder > blocks[realIndex + i].accessOrder){
					iLRU = (realIndex + i);
					minOrder = blocks[realIndex + i].accessOrder;
			}
        
		}else{ // Posição não possui dado válido
			if (freeIndex == -1)
				freeIndex = ( realIndex + i);
		}

		
		if( indexHit != -1 ){ // Hit
			blocks[indexHit].accessOrder = maxOrder + 1;
			result = 0;
		}
		else if( freeIndex != -1){ // Failure withoud overwriting
			blocks[freeIndex].validityBit	= 1;
			blocks[freeIndex].tag 			= tag;
			blocks[freeIndex].accessOrder	= maxOrder;
			result = 1;
		}
		else{ // Failure and overwriting
			blocks[iLRU].tag 		 = tag;
			blocks[iLRU].accessOrder = maxOrder;
			result = 2;
		}

    }

	return result;
}

Block* Cache::getBlocks(){ return blocks; }

}

void cacheAccessInfo::displayData()
{
    printf("\n========== RELATÓRIO FINAL ==========\n");

    printf("%-27s %d\n", "Acessos L1:", numOfL1Access);
	printf("%-27s %d\n", "Falhas L1:", numOfL1Failure);
    printf("%-27s %d\n", "Acessos Inst L1:", numOfInstL1Access);
	printf("%-27s %d\n", "Falhas Inst L1:", numOfInstL1Failure);
    printf("%-27s %d\n", "Acessos Dados L1:", numOfDataL1Access);
	printf("%-27s %d\n", "Falhas Dados L1:", numOfDataL1Failure);

    if(numOfL1Access > 0)
	{
        float taxaFalhaL1 = 100.0f *  numOfL1Failure / numOfL1Access;
		float taxaFalhaInstL1 = 100.0f *  numOfInstL1Failure / numOfInstL1Access;
		float taxaFalhaDataL1 = 100.0f *  numOfDataL1Failure / numOfDataL1Access;

		printf("\n");
		printf("%-27s %.2f%%\n", "Taxa de acerto L1:", 100.0f - taxaFalhaL1);
        printf("%-27s %.2f%%\n", "Taxa de falha L1:", taxaFalhaL1);
		printf("%-27s %.2f%%\n", "Taxa de falha de instrucoes L1:", taxaFalhaInstL1);
		printf("%-27s %.2f%%\n", "Taxa de falha de dados L1:", taxaFalhaDataL1);
    }


    if(numOfL2Access > 0)
	{
		printf("\n");
		printf("%-27s %d\n", "Acessos L2:", numOfL2Access);
		printf("%-27s %d\n", "Falhas L2:", numOfL2Failure);

        float taxaFalhaL2 = 100.0f * numOfL2Failure / numOfL2Access;
		float taxaFalhaInstL2 = 100.0f *  numOfInstL2Failure / numOfInstL2Access;
		float taxaFalhaDataL2 = 100.0f *  numOfDataL2Failure / numOfDataL2Access;

		printf("%-27s %.2f%%\n", "Taxa de acerto L2:", 100.0f - taxaFalhaL2);
        printf("%-27s %.2f%%\n", "Taxa de falha L2:", taxaFalhaL2);
		printf("%-27s %.2f%%\n", "Taxa de falha de instrucoes L2:", taxaFalhaInstL2);
		printf("%-27s %.2f%%\n", "Taxa de falha de dados L2:", taxaFalhaDataL2);

		printf("\n---GLOBAIS---\n");
		float taxaFalhaGlobal = 100.0f * numOfL2Failure / numOfL1Access;
		printf("%-27s %.2f%%\n", "Taxa de acerto GLOBAL:", 100.0f - taxaFalhaGlobal);
		printf("%-27s %.2f%%\n", "Taxa de falha GLOBAL:", taxaFalhaGlobal);
    }

    printf("=====================================\n\n");
}
