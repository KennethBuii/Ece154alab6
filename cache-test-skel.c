/*
Kenny Bui, Matthew Nguyen, Ethan Epp
Lab 6 - Mystery Caches

Mystery Cache Geometries:
mystery0:
    block size = 64 bytes
    cache size = 4096 KB
    associativity = 16
mystery1:
    block size = 4 bytes
    cache size = 4 KB
    associativity = 1
mystery2:
    block size = 32 bytes
    cache size = 4.03 KB
    associativity = 128
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/* 
   Returns the size (in B) of the cache
*/

int get_cache_size(int block_size) {
  int cachesize = 0;
  int check = block_size;
  flush_cache();
  access_cache(0);
  while (access_cache(0)) {
    cachesize = block_size;
    for (int x = cachesize; x <= check; x += block_size) {
      cachesize += block_size;
      access_cache(cachesize);
    }
    check += block_size;
  }
  
  return cachesize;
}
//
/*
   Returns the associativity of the cache
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
*/
int get_block_size() {
  int x = 0;
  int size = 0;
  access_cache(x);
  while (access_cache(x)){
    size++;
    x++;
  }
  return x;
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
