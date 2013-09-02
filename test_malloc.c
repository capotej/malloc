#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <math.h>
#include <assert.h>
#include "malloc.h"

void test_malloc_and_free(){
  void *ptr0 = malloc(sizeof(char) + 8);
  sprintf((char *)ptr0, "hello");
  printf("%s\n", (char *)ptr0);
  free(ptr0);
  void *ptr1 = malloc(sizeof(char) + 8);
  void *ptr2 = malloc(sizeof(char) + 300);
  void *ptr3 = malloc(sizeof(char) + 80);
  free(ptr2);
  void *ptr4 = malloc(sizeof(char) + 200);
  void *ptr5 = malloc(sizeof(char) + 8);
  //print_ledger();
}

void test_divide_slots(){
  printf("test_divide_slots():\n");
  printf(" %d should be 1\n", divide_slots(10));
  printf(" %d should be 2\n", divide_slots(70));
  printf(" %d should be 3\n", divide_slots(130));
  printf("\n\n\n");
}

// void test_find_free_slot(){
//   printf("test_find_free_slot():\n");

//   int f;
//   ledger[0] = (void *)1;
//   ledger[2] = (void *)1;
//   ledger[5] = (void *)1;
//   f = find_free_slot(50);
//   printf(" %d should be 1\n", f);
//   f = find_free_slot(100);
//   printf(" %d should be 3\n", f);
//   f = find_free_slot(500);
//   printf(" %d should be 6\n", f);
//   f = find_free_slot(50000000);
//   printf(" %d should be -1\n", f);
//   printf("\n\n\n");
//   init_ledger();
// }

int main(int argc, char *argv[]){

  // test_find_free_slot();
  test_divide_slots();
  test_malloc_and_free();
  return 0;

}
