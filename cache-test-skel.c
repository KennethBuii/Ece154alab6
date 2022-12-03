/*
Kenny Bui, Matthew Nguyen, Ethan Epp
Lab 6 - Mystery Caches

Mystery Cache Geometries:
mystery0:
    block size = 64 bytes
    cache size = 4194304 bytes = 4096 KB
    associativity = 16
mystery1:
    block size = 4 bytes
    cache size = 4096 bytes = 4 KB
    associativity = 1
mystery2:
    block size = 32 bytes
    cache size = 4096 bytes = 4 KB
    associativity = 128
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/* 
   Returns the size (in B) of the cache

   For each iteration, flush cache then initialize at address 0. Then fill every block that we know exist. If address 0 doesn't get rewritten, then we know that an additional block exists.
   Iterate until address 0 gets rewritten and we will receive the number of blocks. Multiple number of blocks by block size to get capacity.
*/

int get_cache_size(int block_size) {

  int numBlocks = 0;

  // fill up empty cache as much as possible per iteration -> counting number of blocks until address 0 gets overwritten. 
  while (access_cache(0)) {
    flush_cache();
    access_cache(0);

    // address 0 not overwritten, must mean there is at least one more block
    numBlocks++;

    // fill up all known existing blocks in cache
    int fill = 1;
    while (fill <= numBlocks) {
      access_cache(fill*block_size);
      fill++;
    }
  }

  return numBlocks * block_size; 
}

//
/*
   Returns the associativity of the cache

   Flush cache then do one access from address 0. Then do another access from an address a cache size
   away. This will fill the next way if there is another. Keep doing this until access cache with address 0
   misses. This indicates that all ways have been filled and we can return the associativity
*/

int get_cache_assoc(int size) {
  int assoc = 0;
  flush_cache();
  access_cache(0);
  while (access_cache(0)) {
    for (int x = 1; x <= assoc + 1; x++) {
        access_cache(x * size);
    }
    assoc++;
  }
  return assoc;
}

/*
   Returns the size (in B) of each block in the cache.
   Do one access to cache from address 0 then do accesses in increments of 1 until a miss
   that indicates the end of the first block
*/

int get_block_size() {
  int blockSize = 0;
  access_cache(0);
  while (access_cache(blockSize)){
    blockSize++;
  }
  return blockSize;
}

int main(void) {
  int size;
  int assoc;
  int block_size;
  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.
     You can test your geometry paramter discovery routines by 
     calling cache_init() w/ your own size and block size values. */
  cache_init(0,0);
  
  block_size = get_block_size();
  size = get_cache_size(block_size);
  assoc = get_cache_assoc(size);


  printf("Cache size: %d bytes\n",size);
  printf("Cache associativity: %d\n",assoc);
  printf("Cache block size: %d bytes\n",block_size);
  
  return EXIT_SUCCESS;
}
