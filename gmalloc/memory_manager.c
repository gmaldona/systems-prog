/*
 * CS 551 Project "Memory manager".
 * This file needs to be turned in.	
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

//==================================================================== 80 ====>>

static STRU_MEM_LIST *mem_pool = NULL;

/*
 * Print out the current status of the memory manager.
 * Reading this function may help you understand how the memory manager organizes the memory.
 * Do not change the implementation of this function. It will be used to help the grading.
 */
void
mem_mngr_print_snapshot(void) {
  STRU_MEM_LIST *mem_list = NULL;

  printf("============== Memory snapshot ===============\n");

  mem_list = mem_pool; // Get the first memory list
  while (NULL != mem_list) {
	STRU_MEM_BATCH *mem_batch = mem_list->first_batch; // Get the first mem batch from the list

	printf("mem_list %p slot_size %d batch_count %d free_slot_bitmap %p\n",
		   mem_list, mem_list->slot_size, mem_list->batch_count, mem_list->free_slots_bitmap);
	bitmap_print_bitmap(mem_list->free_slots_bitmap, mem_list->bitmap_size);

	while (NULL != mem_batch) {
	  printf("\t mem_batch %p batch_mem %p\n", mem_batch, mem_batch->batch_mem);
	  mem_batch = mem_batch->next_batch; // get next mem batch
	}

	mem_list = mem_list->next_list;
  }

  printf("==============================================\n");
}

/*
 * Initialize the memory manager with 8 bytes slot size mem_list.
 * Initialize this list with 1 batch of slots.
 */
void
mem_mngr_init(void) {
  mem_pool = (STRU_MEM_LIST *)malloc(sizeof(STRU_MEM_LIST));

  mem_pool->slot_size = MEM_BATCH_SLOT_COUNT;
  mem_pool->batch_count = 1;
  mem_pool->bitmap_size = BIT_PER_BYTE;
  mem_pool->next_list = NULL;

  mem_pool->free_slots_bitmap =
	  (unsigned char *)malloc(sizeof(unsigned char));
  *(mem_pool->free_slots_bitmap) = 0xFF; // init first slot bitmap to all 1s.

  mem_pool->first_batch =
	  (STRU_MEM_BATCH *)malloc(sizeof(STRU_MEM_BATCH));

  mem_pool->first_batch->batch_mem =
	  malloc(MEM_ALIGNMENT_BOUNDARY * MEM_BATCH_SLOT_COUNT);

  mem_pool->first_batch->next_batch = NULL;
}

/*
 * Clean up the memory manager (e.g., release all the memory allocated)
 */
void
mem_mngr_leave(void) {
  /* Your code here */
}

/**
 * Aux function for batch expansion in a list.
 * Takes the last filled batch and returns a new batch of managed memory with
 * a link between the prev_batch and the new_batch.
 * @param prev_batch
 */
STRU_MEM_BATCH *
mem_mngr_batch_expansion(STRU_MEM_BATCH *prev_batch) {
  return NULL;
}

/*
 * Allocate a chunk of memory 	
 * @param size: size in bytes to be allocated
 * @return: the pointer to the allocated memory slot
 */
void *
mem_mngr_alloc(size_t size) {

  printf("[DEBUG] Memory allocated: %zu\n", size);

  STRU_MEM_LIST *list = mem_pool;
  while (list) { // iterate over each list... when does other lists init??
	int slot = bitmap_find_first_bit(list->free_slots_bitmap,
									 MEM_BATCH_SLOT_COUNT, 1);
	if (slot < 0) {
	  // TODO: need to expand for more slots.
	}

//	printf("[DEBUG] Free slot: %d\n", slot);
	bitmap_clear_bit(list->free_slots_bitmap,
					 sizeof(list->free_slots_bitmap), slot);

	//	STRU_MEM_BATCH *batch = mem_pool->first_batch;

	return NULL;

	list = list->next_list;
  }
  return NULL;
}

/*
 * Free a chunk of memory pointed by ptr
 * Print out any error messages
 * @param: the pointer to the allocated memory slot
 */
void
mem_mngr_free(void *ptr) {
//	STRU_MEM_LIST * list = mem_pool;
//	while (list) {
//		STRU_MEM_BATCH* batch = list->first_batch;
//
//		while (batch) {
//			batch = batch->next_batch;
//		}
//		list = list->next_list;
//	}
}

//==================================================================== 80 ====>>
