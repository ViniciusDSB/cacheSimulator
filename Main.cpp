#include "cache.h"



int main(int argc, char **argv){

    using namespace cache;

    cacheAccesData& cacheData = startCache(argc, argv);
    cache::Cache instCache{
			cacheData.cacheConfigs[0],
			cacheData.cacheConfigs[1],
			cacheData.cacheConfigs[2]
		};
	cache::Cache* dataCache = ( cacheData.cacheConfigs[3] )? 
		new cache::Cache(
			cacheData.cacheConfigs[3],
			cacheData.cacheConfigs[4],
			cacheData.cacheConfigs[5]
		) : nullptr ;
	cache::Cache* l2Cache = ( cacheData.cacheConfigs[6] )? 
		new cache::Cache(
			cacheData.cacheConfigs[6],
			cacheData.cacheConfigs[7],
			cacheData.cacheConfigs[8]
		) : nullptr ;

    FILE* &traceFile = cacheData.traceFile;
    
    char tipoAcesso; // Instruction read, Load or Store data (I, L, S)
	int accessRequest,
		 resultAcesso,
		 endereco;

	while (! feof(traceFile)){

		accessRequest= fscanf(traceFile, "%c %d\n", &tipoAcesso, &endereco);

		if ((accessRequest != 0) && (accessRequest != EOF))
		{
			if (tipoAcesso == 'I') // Instruction reading
			{
				cacheData.numOfInstL1Access++;
				resultAcesso = instCache.findInsert(endereco);
			}	
			else // Read or write data
			{
				cacheData.numOfDataL1Access++;

				// If data cache is defined, access it, else, acces the global instCache;
				resultAcesso = ( dataCache != nullptr ) ? 
					dataCache->findInsert(endereco) : 
					instCache.findInsert(endereco); 
			}

			// If there was a failure in cache L1 (instaCache and dataCache) we acces cache L2 if exists
			if (resultAcesso != 0)
			{
				cacheData.numOfL1Failure++;

				if( l2Cache != nullptr)
				{
					cacheData.numOfInstL2Access++;
					if( l2Cache->findInsert(endereco) != 0)
						cacheData.numOfL2Failure++;
				}
					
			}
		}
	}


	// auto myBlocks = instCache.getBlocks();
	// printf(" V - Tag - Order \n");
	// for(int i{}; i < instCache.numOfBlocks; i++){
	// 	printf(" %d - %d - %d \n", myBlocks[i].validityBit, myBlocks[i].tag, myBlocks[i].accessOrder);
	// }

    cacheData.displayData();

    return 0;
}