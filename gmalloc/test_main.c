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

void test_bitmap(void) {

    unsigned char bitmap[] = {0xF7, 0xFF};
    
    int val = bitmap_find_first_bit(bitmap, sizeof(bitmap), 0);
    printf("%d\n", val);

    for (size_t i = 0; i < sizeof(bitmap); ++i) {
        printf("%x\t", bitmap[i]);
    }
    
    printf("\n");
    printf("bitmap@3 is %d\n", bitmap_bit_is_set(bitmap, sizeof(bitmap), 3));

    bitmap_set_bit(bitmap, sizeof(bitmap), 3);
    for (size_t i = 0; i < sizeof(bitmap); ++i) {
        printf("%x\t", bitmap[i]);
    }

    printf("\n");
    printf("bitmap@3 is %d\n", bitmap_bit_is_set(bitmap, sizeof(bitmap), 3));

    u_int8_t dest[BIT_PER_BYTE]; 
    bitmap_clear_bit(bitmap, sizeof(bitmap), 3);
    for (size_t i = 0; i < sizeof(bitmap); ++i) {
        printf("%x\t", bitmap[i]);
        hex_bitmap(bitmap[i], dest);
        for (size_t j = 0; j < sizeof(dest); j++) {
            printf("%d", dest[j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("bitmap@3 is %d\n", bitmap_bit_is_set(bitmap, sizeof(bitmap), 3));

}

int main(int argc, char * argv[])
{
	// Your code

    // mem_mngr_init();


	// test your code here.

    test_bitmap();
    // mem_mngr_leave();

    return 0;
}

//==================================================================== 80 ====>>
