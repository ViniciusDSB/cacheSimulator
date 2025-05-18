# Cache Simulator is:
Home Work of Computer Architecture; When done this should simulate a simple, data/instruction and multilevel, cache.

# Note
  Config files has 3 attibutes per line:
- num of blocks, associativity, words per block
  If more lines is given this means:
- 2 lines -> 1 level cache, split in data and instructions;
- 3 lines -> 2 levels, data and instructions in the same level 2;
  Trace files has a char, that represents a access type, and a number, which is an addres in decimal base ( I 12354, for example).

# In code
- In the code, everytime it fails to acces something the class writes the 'data' in the block (changes validity bit to 1 and the tag);
- If there is level 2 cache it writes the data in level 1 anyway and also in level 2; In real cache this also happens but in different order (the processor fails on level 1 and brings data from level 2).

# In code structures
- There is a class for blocks and for cache (Block, Cache);
- The Block struct holds validity biy, tag and access order ( for LRU policy );
- The Cache class holds a vector of Blocks and its index is calculated by findInsert(addres) method using addres ( seems like a hash table );
- The address is read using readFiles; it reads config file and returns an int[9] containing the configs (it has 9 positions because its all we need since we have 3 params for each cache and 3 caches at most);
- There is no structure for holding sets of blocks; The number we use to iterate blocks is 'realIndex';
- There is also an struct for holding cache acces information (cacheAccesInfo), but i just think it would be better to store access informrmation in Cache itself.
