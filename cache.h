#ifndef _cache
#define _cache

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace cache{

    struct Block{
        int validityBit{},
        tag{},
        accesOrder{}; // A real one also has data
    };
    
    class Cache{

        public:
        
            unsigned numOfBlocks,	// Número total de blocos da cache
            assoc,		            // Número de blocos por conjunto
            numOfWordsPerBlock,	    // Número de palavras do bloco
            numOfSets;	

            // Constructors/destructor:
            Cache();
            Cache(unsigned numOfBlocks, unsigned assoc, unsigned numOfWordsPerBlock);
            ~Cache();

            // Other methods
            int findInsert(unsigned address);
            Block* getBlocks();

        private:

            Block* blocks;
    };

}


struct cacheAccesData{
    ~cacheAccesData(){ 
        fclose(traceFile); 
        std::cout << "Cache traceFile closed!" << std::endl;
    }

    FILE* traceFile;
    cache::Cache newCache;
    unsigned    numOfInstructionAccess,
                numOfDataAccess,
                numOfL1Failure;

};
// This ufnciton reads config file, returns a new cache and set traceFile;
cacheAccesData startCache(int argc, char **argv);

#endif