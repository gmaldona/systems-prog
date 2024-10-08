/*
 * CS 551 Project "Memory manager".
 * This file does not need to be turned in. 
 *
 * author: Gregory Maldonado
 * email : gmaldonado@cs.binghamton.edu
 * date  : 2024-07-04
 * web   : https://cs.binghamton.edu/~gmaldonado/
 *
 * Graduate student @ Thomas J. Watson College of Engineering and Applied
 * Sciences, Binghamton University.
 */

#include "memory_manager.h"
#include "interposition.h"

//==================================================================== 80 ====>>

void
test_bitmap(void) {
  printf("\n\n================ TESTS ================\n");
  unsigned char bitmap[] = {0xF7, 0xFF};

  printf("\n================ FIND FIRST BIT TEST ================\n");
  int val = bitmap_find_first_bit(bitmap, sizeof(bitmap), 0);
  printf("%d\n", val);

  for (size_t i = 0; i < sizeof(bitmap); ++i) {
    printf("%x\t", bitmap[i]);
  }

  printf("\n\n================ SET BIT TEST ================\n");
  u_int8_t dest[BIT_PER_BYTE];
  bitmap_set_bit(bitmap, sizeof(bitmap), 3);

  for (size_t i = 0; i < sizeof(bitmap); ++i) {
    printf("%x\t", bitmap[i]);
    for (size_t j = 0; j < sizeof(dest); j++) {
      if (j % 4 == 0) {
        printf("  ");
      }
      printf("%d", dest[j]);
    }
    printf("\n");
  }

  printf("\n\n================ CLEAR BIT TEST ================\n");
  bitmap_clear_bit(bitmap, sizeof(bitmap), 3);
  for (size_t i = 0; i < sizeof(bitmap); ++i) {
    printf("%x\t", bitmap[i]);
    hex_bitmap(bitmap[i], dest);
    for (size_t j = 0; j < sizeof(dest); j++) {
      if (j % 4 == 0) {
        printf("  ");
      }
      printf("%d", dest[j]);
    }
    printf("\n");
  }

  printf("\n");
  printf("bitmap@3 is %d\n", bitmap_bit_is_set(bitmap, sizeof(bitmap), 3));

}

void double_free_test() {
  void *p1 = mem_mngr_alloc(7);
  mem_mngr_free(p1);
  mem_mngr_free(p1);
}

void realloc_mem_test() {
  void *p1 = mem_mngr_alloc(7);
  mem_mngr_free(p1);
  void *p2 = mem_mngr_alloc(3);
  printf("%p == %p\n", p1, p2);
}

void
test_allocator() {
  void *p1 = mem_mngr_alloc(7);
  // TODO: fix double free
  void *p2 = mem_mngr_alloc(7);
  void *p3 = mem_mngr_alloc(7);
  void *p4 = mem_mngr_alloc(7);
  void *p5 = mem_mngr_alloc(7);
  void *p6 = mem_mngr_alloc(7);
  void *p7 = mem_mngr_alloc(7);
  void *p8 = mem_mngr_alloc(7);
  void *p9 = mem_mngr_alloc(7);
  void *p10 = mem_mngr_alloc(7);
  void *p11 = mem_mngr_alloc(7);

  printf("pointer 1\t%p\n", p1);
  printf("pointer 2\t%p\n", p2);
  printf("pointer 3\t%p\n", p3);
  printf("pointer 4\t%p\n", p4);
  printf("pointer 5\t%p\n", p5);
  printf("pointer 6\t%p\n", p6);
  printf("pointer 7\t%p\n", p7);
  printf("pointer 8\t%p\n", p8);
  printf("pointer 9\t%p\n", p9);
  printf("pointer 10\t%p\n", p10);
  printf("pointer 11\t%p\n", p11);

   printf("Expecting two batches\n");
   mem_mngr_print_snapshot();
}

void allot_alloc() {
  for (int i = 0; i < 3; ++i) {  // batches
    printf("Batch %d:\n", i);
    for (int j = 0; j < MEM_BATCH_SLOT_COUNT; ++j) {// slots
      void* p = mem_mngr_alloc(7);
      printf("%p\n", p);
    }
    printf("\n");
  }
//  printf("Total pointers allocated: %d\n", 3 * MEM_BATCH_SLOT_COUNT);
  mem_mngr_print_snapshot();
}

void variable_dealloc() {
  for (int i = 0; i < 1; ++i) {  // batches
    for (int j = 0; j < MEM_BATCH_SLOT_COUNT -1; ++j) { // slots
      mem_mngr_alloc(7);
    }
  }
  void* p1 = mem_mngr_alloc(7);
  mem_mngr_free(p1);
  void* p2 = mem_mngr_alloc(7);
  printf("%p == %p\n", p1, p2);

  mem_mngr_print_snapshot();
}

int
main(int argc, char *argv[]) {
  // Your code

//  test_bitmap();

  mem_mngr_init();
//  double_free_test();
//  realloc_mem_test();
//  test_allocator();
    allot_alloc();
//  variable_dealloc();
  mem_mngr_leave();

  return 0;
}

//==================================================================== 80 ====>>
