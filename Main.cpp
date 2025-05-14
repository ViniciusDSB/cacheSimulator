#include "cache.h"


int main(int argc, char **argv){

    using namespace cache;

    cacheAccessInfo& cacheInfo = startCache(argc, argv);

    cache::Cache instCache{
			cacheInfo.cacheConfigs[0],
			cacheInfo.cacheConfigs[1],
			cacheInfo.cacheConfigs[2]
		};
	cache::Cache* dataCache = ( cacheInfo.cacheConfigs[3] != 0 )? 
		new cache::Cache(
			cacheInfo.cacheConfigs[3],
			cacheInfo.cacheConfigs[4],
			cacheInfo.cacheConfigs[5]
		) : nullptr ;
	cache::Cache* l2Cache = ( cacheInfo.cacheConfigs[6] != 0)? 
		new cache::Cache(
			cacheInfo.cacheConfigs[6],
			cacheInfo.cacheConfigs[7],
			cacheInfo.cacheConfigs[8]
		) : nullptr ;

	// For verification only;
	printf("You have Level 1 cache; \n");
    if(dataCache != nullptr)
		printf("You have instructions cache and data cache; \n");
	if(l2Cache != nullptr)
		printf("You have Level 2 cache; \n");
    
    char tipoAcesso; // Instruction read, Load or Store data (I, L, S)
	int accessRequest,
		 resultAcesso,
		 endereco;

	while (! feof(cacheInfo.traceFile)){

		accessRequest= fscanf(cacheInfo.traceFile, "%c %d\n", &tipoAcesso, &endereco);

		if ((accessRequest != 0) && (accessRequest != EOF))
		{
			if (tipoAcesso == 'I') // Instruction reading
			{
				cacheInfo.numOfL1Access++;
				cacheInfo.numOfInstL1Access++;
				resultAcesso = instCache.findInsert(endereco);
			}	
			else // Read or write data
			{
				cacheInfo.numOfL1Access++;
				cacheInfo.numOfDataL1Access++;

				// If data cache is defined, access it, else, acces the global instCache;
				resultAcesso = ( dataCache != nullptr ) ? 
					dataCache->findInsert(endereco) : 
					instCache.findInsert(endereco); 
			}

			// If there was a failure in cache L1 (instaCache and dataCache) we acces cache L2 if exists
			if (resultAcesso != 0)
			{
				cacheInfo.numOfL1Failure++;

				if( l2Cache != nullptr)
				{
					cacheInfo.numOfInstL2Access++;
					if( l2Cache->findInsert(endereco) != 0)
						cacheInfo.numOfL2Failure++;
				}
					
			}
		}
	}

    cacheInfo.displayData();

    return 0;
}