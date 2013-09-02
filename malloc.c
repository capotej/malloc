#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <math.h>
#include <assert.h>
#include "malloc.h"

#define _GNU_SOURCE

#define ALLOC_SIZE 104857600 // 100 megabytes
#define CHUNK_SIZE 64        // 64 byte
#define SLOTS ALLOC_SIZE / CHUNK_SIZE


void *mapped_memory = NULL;

void *ledger[SLOTS];

int divide_slots(size_t size) {
  return (int)ceil((float)size / CHUNK_SIZE);
}

// Find first slot that accomodates at least size_t of contingous chunks in ledger
int find_free_slot(size_t size){
  int slots_needed = divide_slots(size);
  assert(slots_needed > 0);

  int slots_found = 0;
  int slot = 0;

  for (int i = 0; i < SLOTS; ++i){
    slot = i;
    if (ledger[i] == NULL) {
      slots_found++;
      if(slots_found == slots_needed){
        break;
      }
    } else {
      slots_found = 0;
    }
  }

  if (slots_found != slots_needed) {
    return -1;
  }
  return (slot - slots_needed) + 1;
}

void init_ledger(){
  for (int i = 0; i < SLOTS; ++i){
    ledger[i] = NULL;
  }
}

void init_allocator(){
  if (mapped_memory == NULL) {
    mapped_memory = mmap(NULL, ALLOC_SIZE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
    assert(mapped_memory != MAP_FAILED);
    init_ledger();
  }
}

void *malloc(size_t size){
  init_allocator();
  int slot = find_free_slot(size);
  int slots_needed = divide_slots(size);
  assert(slots_needed > 0);
  if (slot == -1)
    return NULL;
  void *ptr;
  ptr = (void *)&mapped_memory[slot];
  for (int i = 0; i < slots_needed; ++i){
    ledger[slot + i] = ptr;
  }
  return ptr;
}

void free(void *slot_ptr){
  for (int i = 0; i < SLOTS; ++i){
    if (ledger[i] == slot_ptr){
      ledger[i] = NULL;
    }
  }
}

void print_ledger(){
  for (int i = 0; i < SLOTS; ++i){
    printf("%d: %p\n", i, ledger[i]);
  }
}

int main(int argc, char const *argv[]){
  return 0;
}
