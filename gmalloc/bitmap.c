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
#include <stdint.h>
#include <math.h>

#include "common.h"

//==================================================================== 80 ====>>

// https://stackoverflow.com/questions/72903837
void hex_bitmap(unsigned char hex, u_int8_t *dest) {
  for (int i = 0; i < BIT_PER_BYTE; ++i) {
	dest[i] = (hex >> i) & 1;
  }
}

unsigned char bitmap_hex(u_int8_t *src) {
  unsigned char hex = 0;

  for (int i = 7; i >= 0; --i) {
	hex = (hex << 1) | src[i];
  }
  return hex;
}

/*
 * Find the position (starting from 0) of the first bit that has value "val" in 
 * the "bitmap". 
 * 
 * @param bitmap: start address of the bitmap
 * @param size: size in bytes of the bitmap
 * @param val: 0 or non-0
 * @return: the position in the bitmap of the first 0 bit (if "val" is zero) 
 *              or the first 1 bit (if "val" is non-zero)
 * 
 *          BITMAP_OP_NOT_FOUND (defined in "common.h") if the bit of interest 
 *                  does not exist in the bitmap
 * 
 *          BITMAP_OP_ERROR (defined in "common.h") on any other errors
 */
int bitmap_find_first_bit(unsigned char *bitmap, int size, int val) {
  if (1 < val || val < 0 || size < 0) {
	return BITMAP_OP_ERROR;
  }

  u_int8_t dest[BIT_PER_BYTE];
  for (int i = 0; i < size; ++i) {
	hex_bitmap(bitmap[i], dest);

	// for (int i = 7; i >= 0; --i) {
	for (size_t j = 0; j < BIT_PER_BYTE; ++j) {
	  printf("i=%d\tbit=%d\t", i, dest[j]);
	  if (dest[j] == (u_int8_t)val) {
		return (i * BIT_PER_BYTE) + j;
	  }
	}
	printf("\n");
  }

  return BITMAP_OP_NOT_FOUND;
}

/*
 * Change the value of the "target_pos"-th bit (starting from 0) in the "bitmap"
 *  to 1.
 * 
 * @param bitmap: start address of the bitmap
 * @param size: size in bytes of the bit map
 * @param target_pos: the position of the bit of interest
 * @return: BITMAP_OP_SUCCEED (defined in "common.h") on success
 *          BITMAP_OP_ERROR (defined in "common.h") on any errors
 */
int bitmap_set_bit(unsigned char *bitmap, int size, int target_pos) {
  if (target_pos >= size * BIT_PER_BYTE || target_pos < 0) {
	return BITMAP_OP_ERROR;
  }

  size_t index = (size_t)floor(target_pos / BIT_PER_BYTE);
  uint8_t dest[BIT_PER_BYTE];

  for (size_t i = 0; i < BIT_PER_BYTE; ++i) {
	if (index + i == target_pos) {
	  dest[i] = 1;
	  bitmap[index] = bitmap_hex(dest);
	  return BITMAP_OP_SUCCEED;
	}
  }

  return BITMAP_OP_ERROR;
}

/*
 * Change the value of the "target_pos"-th bit (starting from 0) in the "bitmap"
 * to 0.
 * 
 * @param bitmap: start address of the bitmap
 * @param size: size in bytes of the bit map
 * @param target_pos: the position of the bit of interest
 * @return: BITMAP_OP_SUCCEED (defined in "common.h") on success
 *          BITMAP_OP_ERROR (defined in "common.h") on any errors
 */
int bitmap_clear_bit(unsigned char *bitmap, int size, int target_pos) {
  if (target_pos >= size * BIT_PER_BYTE || target_pos < 0) {
	return BITMAP_OP_ERROR;
  }

  size_t index = (size_t)floor(target_pos / BIT_PER_BYTE);
  uint8_t dest[BIT_PER_BYTE];

  hex_bitmap(bitmap[index], dest);

  for (size_t i = 0; i < BIT_PER_BYTE; ++i) {
	if ((index * BIT_PER_BYTE) + i == target_pos) {

	  dest[i] = 0;
	  *(bitmap + index) = bitmap_hex(dest);

	  return BITMAP_OP_SUCCEED;
	}
  }

  return BITMAP_OP_ERROR;
}

/*
 * Test if the value of the "pos"-th bit (starting from 0) in the "bitmap" is 1.
 * @param bitmap: start address of the bitmap
 * @param size: size in bytes of the bit map
 * @param pos: the position of the bit of interest
 * @return: the value of the bit of interest (i.e., 0 or 1) on success
 *          BITMAP_OP_ERROR (defined in "common.h") on any errors
 */
int bitmap_bit_is_set(unsigned char *bitmap, int size, int pos) {
  if (pos >= size * BIT_PER_BYTE || pos < 0) {
	return BITMAP_OP_ERROR;
  }

  size_t index = (size_t)floor(pos / BIT_PER_BYTE);
  uint8_t dest[BIT_PER_BYTE];

  hex_bitmap(bitmap[index], dest);

  for (size_t i = 0; i < BIT_PER_BYTE; ++i) {
	if (index + i == pos) {
	  return dest[i];
	}
  }

  return BITMAP_OP_ERROR;
}

/*
 * Print the content of a bitmap in starting from the first bit, and insert a 
 * space every 4 bits
 * 
 * @param bitmap: start address of the bitmap
 * @param size: size in bytes of the bit map
 * @return: BITMAP_OP_SUCCEED (defined in "common.h") on success
 *          BITMAP_OP_ERROR (defined in "common.h") on any errors
 * Do not change the implementation of this function.
 */
int bitmap_print_bitmap(unsigned char *bitmap, int size) {
  int pos = 0;
  int total_bits = size * BIT_PER_BYTE;
  unsigned char current_byte = 0;

  if (NULL == bitmap) {
	printf("ERROR: NULL bit map!\n");
	return BITMAP_OP_ERROR;
  }

  printf("bitmap %p size %d bytes: ", bitmap, size);

  while (pos < total_bits) {
	int v = 0;

	current_byte = *(bitmap + pos / BIT_PER_BYTE);
	v = ((current_byte >> pos % BIT_PER_BYTE) & 0x01);
	printf("%d", v);
	if ((pos + 1) % 4 == 0) {
	  printf("  ");
	}

	pos++;
  }

  printf("\n");

  return BITMAP_OP_SUCCEED;
}

//==================================================================== 80 ====>>
