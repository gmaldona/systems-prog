Authored By: GREGORY MALDONADO

B-Number:    B00784284

Date:        2024-08-04

STATUS: Completed.
DESCRIPTION: (Simple) Pthread Barrier Implementation.

No Memory Leaks via Valgrind
```
==1528450== HEAP SUMMARY:
==1528450==     in use at exit: 0 bytes in 0 blocks
==1528450==   total heap usage: 1 allocs, 1 frees, 96 bytes allocated
==1528450== 
==1528450== All heap blocks were freed -- no leaks are possible
==1528450== 
==1528450== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

Test Cases:
3 thread barrier, 4 threads spawn:
```
% gcc -Wall -pthread -D PIPE_BUF_MAX=1024 main.c mybarrier.c -o build/main -pthread
[FINE] Thread spawned
[FINE] Thread spawned
[FINE] Thread spawned
[FINE] Thread spawned
[FINE] Thread awake
[FINE] Thread awake
[FINE] Thread awake
[FINE] Barrier destroyed
%