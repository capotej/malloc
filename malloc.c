#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <assert.h>

// #define ALLOC_SIZE 104857600 // 100 megabytes
#define ALLOC_SIZE 1024// 100 megabytes
#define CHUNK_SIZE 64        // 64 byte
#define SLOTS ALLOC_SIZE / CHUNK_SIZE


void *mapped_memory;

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
    printf("-> %d: (found:%d,needed:%d)", slot, slots_found, slots_needed);
    if (ledger[i] == NULL) {
      printf(" => %s", "o");
      slots_found++;
      if(slots_found == slots_needed){
        break;
      }
    } else {
      printf(" => %s", "x");
      slots_found = 0;
    }
    printf("\n");
  }
  printf("\n");

  return (slot - slots_needed) + 1;

}

void init_ledger(){
  for (int i = 0; i < SLOTS; ++i){
    ledger[i] = NULL;
  }
}

void test_divide_slots(){
  printf("test_divide_slots():\n");
  printf(" %d should be 1\n", divide_slots(10));
  printf(" %d should be 2\n", divide_slots(70));
  printf(" %d should be 3\n", divide_slots(130));
  printf("\n\n\n");
}

void test_find_free_slot(){
  printf("test_find_free_slot():\n");

  int f;
  ledger[0] = (void *)1;
  ledger[2] = (void *)1;
  ledger[5] = (void *)1;
  f = find_free_slot(50);
  printf(" %d should be 1\n", f);
  f = find_free_slot(100);
  printf(" %d should be 3\n", f);
  f = find_free_slot(500);
  printf(" %d should be 6\n", f);

  // init_ledger();
  // f = find_free_slot(50);
  // printf(" %d should be 0\n", f);

  printf("\n\n\n");
}

void *malloc(size_t size){
  int slot = find_free_slot(size);

}


int main(int argc, char *argv[]){
  mapped_memory = mmap(NULL, ALLOC_SIZE, PROT_READ|PROT_EXEC|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);

  init_ledger();

  test_find_free_slot();
  test_divide_slots();



  // sprintf((char *)mapped_memory, "hi");

  // void *strstart = mapped_memory[0];

  // sprintf((char *)&mapped_memory[0], "hello");

  // example
  // char *foo = (char *)malloc(sizeof(char) * 6);
  // sprintf(foo, "hey");


  // printf("%s", (char *)&mapped_memory[0]);

  // free(foo);




  return 0;

}


