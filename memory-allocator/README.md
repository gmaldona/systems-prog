Authored By: GREGORY MALDONADO

B-Number:    B00784284

Date:        2024-07-04

STATUS: Completed.
BONUS:  Not Completed.
DESCRIPTION: Uses a linked list for memory batches and a top level bitmap to keep track of allocation status.

No Memory Leaks via Valgrind
```
==2440889== HEAP SUMMARY:
==2440889==     in use at exit: 0 bytes in 0 blocks
==2440889==   total heap usage: 5 allocs, 5 frees, 1,338 bytes allocated
==2440889== 
==2440889== All heap blocks were freed -- no leaks are possible
```

Test Cases:
2. SLOT SIZE = 8, ALIGNMENT = 8, Pointers Allocated = 24
```
Batch 0:
0x4a5c150
0x4a5c158
0x4a5c160
0x4a5c168
0x4a5c170
0x4a5c178
0x4a5c180
0x4a5c188

Batch 1:
[INFO] New Batch Created: 0x4a5c610
[INFO] Batch Memory: 0x4a5c660
0x4a5c660
0x4a5c668
0x4a5c670
0x4a5c678
0x4a5c680
0x4a5c688
0x4a5c690
0x4a5c698

Batch 2:
[INFO] New Batch Created: 0x4a5c730
[INFO] Batch Memory: 0x4a5c780
0x4a5c780
0x4a5c788
0x4a5c790
0x4a5c798
0x4a5c7a0
0x4a5c7a8
0x4a5c7b0
0x4a5c7b8

============== Memory snapshot ===============
mem_list 0x4a5c040 slot_size 8 batch_count 3 free_slot_bitmap 0x4a5c800
bitmap 0x4a5c800 size 8 bytes: 0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  
mem_batch 0x4a5c100 batch_mem 0x4a5c150
mem_batch 0x4a5c610 batch_mem 0x4a5c660
mem_batch 0x4a5c730 batch_mem 0x4a5c780
==============================================
```

2. SLOT SIZE = 8, ALIGNMENT = 16, Pointers Allocated = 24
```
Batch 0:
0x4a5c150
0x4a5c160
0x4a5c170
0x4a5c180
0x4a5c190
0x4a5c1a0
0x4a5c1b0
0x4a5c1c0

Batch 1:
[INFO] New Batch Created: 0x4a5c650
[INFO] Batch Memory: 0x4a5c6a0
0x4a5c6a0
0x4a5c6b0
0x4a5c6c0
0x4a5c6d0
0x4a5c6e0
0x4a5c6f0
0x4a5c700
0x4a5c710

Batch 2:
[INFO] New Batch Created: 0x4a5c7b0
[INFO] Batch Memory: 0x4a5c800
0x4a5c800
0x4a5c810
0x4a5c820
0x4a5c830
0x4a5c840
0x4a5c850
0x4a5c860
0x4a5c870

============== Memory snapshot ===============
mem_list 0x4a5c040 slot_size 8 batch_count 3 free_slot_bitmap 0x4a5c8c0
bitmap 0x4a5c8c0 size 8 bytes: 0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  
mem_batch 0x4a5c100 batch_mem 0x4a5c150
mem_batch 0x4a5c650 batch_mem 0x4a5c6a0
mem_batch 0x4a5c7b0 batch_mem 0x4a5c800
==============================================
```
3. SLOT SIZE = 16, ALIGNMENT = 16, Pointers Allocated = 48
```
Batch 0:
0x4a5c150
0x4a5c160
0x4a5c170
0x4a5c180
0x4a5c190
0x4a5c1a0
0x4a5c1b0
0x4a5c1c0
0x4a5c1d0
0x4a5c1e0
0x4a5c1f0
0x4a5c200
0x4a5c210
0x4a5c220
0x4a5c230
0x4a5c240

Batch 1:
[INFO] New Batch Created: 0x4a5c6d0
[INFO] Batch Memory: 0x4a5c720
0x4a5c720
0x4a5c730
0x4a5c740
0x4a5c750
0x4a5c760
0x4a5c770
0x4a5c780
0x4a5c790
0x4a5c7a0
0x4a5c7b0
0x4a5c7c0
0x4a5c7d0
0x4a5c7e0
0x4a5c7f0
0x4a5c800
0x4a5c810

Batch 2:
[INFO] New Batch Created: 0x4a5c8b0
[INFO] Batch Memory: 0x4a5c900
0x4a5c900
0x4a5c910
0x4a5c920
0x4a5c930
0x4a5c940
0x4a5c950
0x4a5c960
0x4a5c970
0x4a5c980
0x4a5c990
0x4a5c9a0
0x4a5c9b0
0x4a5c9c0
0x4a5c9d0
0x4a5c9e0
0x4a5c9f0

============== Memory snapshot ===============
mem_list 0x4a5c040 slot_size 16 batch_count 3 free_slot_bitmap 0x4a5ca40
bitmap 0x4a5ca40 size 8 bytes: 0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  
         mem_batch 0x4a5c100 batch_mem 0x4a5c150
         mem_batch 0x4a5c6d0 batch_mem 0x4a5c720
         mem_batch 0x4a5c8b0 batch_mem 0x4a5c900
==============================================
```
4. Deallocation of a pointer and Reallocating to another pointer
```
0x4a5c240 == 0x4a5c240
```