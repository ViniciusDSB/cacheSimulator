#ifndef _cache
#define _cache

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define N_BYTES_PALAVRA 4

namespace cache{

    struct Block{
        int validityBit{},
        tag{},
        accessOrder{}; // A real one also has data
    };
    
    class Cache{

        public:
        
            unsigned numOfBlocks,	// Número total de blocos da cache
            assoc,		            // Número de blocos por conjunto
            numOfWordsPerBlock,	    // Número de palavras do bloco
            numOfSets;	

            Cache();
            Cache(unsigned numOfBlocks, unsigned assoc, unsigned numOfWordsPerBlock);
            ~Cache();

            int findInsert(int address);
            Block* getBlocks();

        private:

            Block* blocks;
    };

}


class cacheAccesData{
    public:

    ~cacheAccesData(){ 
        fclose(traceFile); 
        std::cout << "Cache traceFile closed!" << std::endl;
    }

    FILE* traceFile;

    unsigned cacheConfigs[9]{}; // Each 3 numebers correspond to a cache config, so we can have 3 caches (data, instructions, level 2)
    unsigned    numOfInstL1Access{},
                numOfDataL1Access{},
                numOfL1Failure{},
                numOfInstL2Access{},
                numOfL2Failure{};

    void displayData();

};
// This ufnciton reads config file, returns vector of configs and sets a traceFile;
cacheAccesData& startCache(int argc, char **argv);

#endif