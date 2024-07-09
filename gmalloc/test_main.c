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

int main(int argc, char * argv[])
{
	// Your code
    unsigned char bitmap[] = {0xF7, 0xFF};
    
    int val = bitmap_find_first_bit(bitmap, sizeof(bitmap), 0);
    printf("%d\n", val);

    for (size_t i = 0; i < sizeof(bitmap); ++i) {
        printf("%x\t", bitmap[i]);
    }

    printf("\n");

    bitmap_set_bit(bitmap, sizeof(bitmap), 3);
    for (size_t i = 0; i < sizeof(bitmap); ++i) {
        printf("%x\t", bitmap[i]);
    }

    printf("\n");
    
    // bitmap_find_first_bit(bitmap, sizeof(bitmap), 0);

    // mem_mngr_init();


	// test your code here.


    // mem_mngr_leave();

    return 0;
}

//==================================================================== 80 ====>>
