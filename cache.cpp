#include "cache.h"

namespace cache{

// Definition of Cache constructor:
Cache::Cache(){} 
Cache::Cache(unsigned numOfBlocks, unsigned assoc, unsigned numOfWordsPerBlock){
    this->numOfBlocks = numOfBlocks;
    this->assoc = assoc;
    this->numOfWordsPerBlock = numOfWordsPerBlock;
    this->numOfSets = (numOfBlocks/assoc);

    this->blocks = new Block [numOfBlocks]{};
}

Cache::~Cache(){
    free(blocks);
    std::cout << "Blocks freed!" << std::endl;
}

int Cache::findInsert(unsigned address){ return address; }

Block* Cache::getBlocks(){ return blocks; }

}