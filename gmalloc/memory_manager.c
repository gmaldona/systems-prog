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

#include <math.h>
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
  STRU_MEM_LIST *list = mem_pool;
  while (list) {

	STRU_MEM_BATCH *batch = list->first_batch;
	while (batch) {
	  free(batch->batch_mem);
	  batch = batch->next_batch;
	}

	free(list->free_slots_bitmap);
	list = list->next_list;
  }
}

/*
 * Allocate a chunk of memory 	
 * @param size: size in bytes to be allocated
 * @return: the pointer to the allocated memory slot
 */
void *
mem_mngr_alloc(size_t size) {

  STRU_MEM_LIST *list = mem_pool;
  while (list) { // iterate over each list... when does other lists init??
	int pos = bitmap_find_first_bit(list->free_slots_bitmap,
									MEM_BATCH_SLOT_COUNT, 1);

	if (pos < 0) {
	  printf("[INFO] New Batch Created\n");
	  // Get the last batch in the list - do we want to move this outside?? ^^^
	  STRU_MEM_BATCH *batch = list->first_batch;
	  while (list->first_batch->next_batch) {
		batch = batch->next_batch;
	  }

	  STRU_MEM_BATCH *new_batch = (STRU_MEM_BATCH *)malloc(sizeof(STRU_MEM_BATCH));
	  new_batch->batch_mem = malloc(MEM_ALIGNMENT_BOUNDARY * MEM_BATCH_SLOT_COUNT);

	  unsigned char *new_bitmap = malloc((list->batch_count + 1) * sizeof(unsigned char));

	  memcpy(new_bitmap, list->free_slots_bitmap, sizeof(list->free_slots_bitmap));
	  free(list->free_slots_bitmap);

	  list->free_slots_bitmap = new_bitmap;
	  list->free_slots_bitmap[list->batch_count] = 0xFF;

	  bitmap_print_bitmap(list->free_slots_bitmap, sizeof(list->free_slots_bitmap));
	  list->batch_count++;

	  pos = bitmap_find_first_bit(list->free_slots_bitmap,
								  MEM_BATCH_SLOT_COUNT, 1);
	}

	bitmap_clear_bit(list->free_slots_bitmap,
					 sizeof(list->free_slots_bitmap), pos);

	int slot = pos % MEM_ALIGNMENT_BOUNDARY;
	int i = 0;
	int target_batch = (int)floor(slot / MEM_ALIGNMENT_BOUNDARY);

	STRU_MEM_BATCH *batch = list->first_batch;
	while (i < target_batch) {
	  batch = batch->next_batch;
	  i++;
	}
	return (batch->batch_mem + (slot * MEM_ALIGNMENT_BOUNDARY));

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
  STRU_MEM_LIST *list = mem_pool;
  size_t _BATCH_INDEX = 0;
  while (list) {
	STRU_MEM_BATCH *_batch_0 = list->first_batch;
	STRU_MEM_BATCH *_batch_1 = _batch_0->next_batch;
	// if _batch_1 is NULL then batch_0 will still be operated on.
	while (_batch_0 && _batch_1) {
	  if ((STRU_MEM_BATCH *)ptr >= _batch_0 || (STRU_MEM_BATCH *)ptr < _batch_1) {
		break;
	  } else {
		_batch_0 = _batch_0->next_batch;
		_batch_1 = _batch_1->next_batch;
		++_BATCH_INDEX;
	  }
	}

	void *batch_mem = _batch_0->batch_mem;
	for (int i = 0; i < MEM_BATCH_SLOT_COUNT; ++i) {
	  if (ptr == (batch_mem + (i * MEM_ALIGNMENT_BOUNDARY))) {
		// free(ptr); NOT FREEING, you still have the memory in the manager
		if (bitmap_bit_is_set(list->free_slots_bitmap,
							  list->batch_count,
							  (_BATCH_INDEX * MEM_ALIGNMENT_BOUNDARY) + i) == 1) {
		  printf("[ERROR] double free on pointer\t%p\n", ptr);
		  return;
		}
		bitmap_set_bit(list->free_slots_bitmap,
					   list->batch_count,
					   (_BATCH_INDEX * MEM_ALIGNMENT_BOUNDARY) + i);
		return;
	  } else if (ptr > (batch_mem + (i * MEM_ALIGNMENT_BOUNDARY)) &&
		  ptr <= (batch_mem + (i * MEM_ALIGNMENT_BOUNDARY) + 7)) {
		printf("[ERROR] unaligned starting memory of pointer\t%p\n", ptr);
		return;
	  }
	}

	list = list->next_list;
  }

  printf("[WARNING] Pointer given is not being managed.\n");
}

//==================================================================== 80 ====>>
