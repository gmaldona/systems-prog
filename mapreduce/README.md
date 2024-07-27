Authored By: GREGORY MALDONADO

B-Number:    B00784284

Date:        2024-07-04

STATUS: Completed.
BONUS:  Not Completed.
DESCRIPTION: Implementation of MapReduce.

No Memory Leaks via Valgrind
```
==383203== HEAP SUMMARY:
==383203==     in use at exit: 0 bytes in 0 blocks
==383203==   total heap usage: 1 allocs, 1 frees, 16 bytes allocated
==383203== 
==383203== All heap blocks were freed -- no leaks are possible
```

Test Cases:
1. `./run-mapreduce "counter" input-warpeace.txt 4`
```
a:210858
b:36749
c:63180
d:117758
e:313171
f:54497
g:53053
h:171161
i:172657
j:2485
k:22650
l:96051
m:61289
n:183139
o:191489
p:49163
q:2320
r:151191
s:162131
t:224512
u:64916
v:26787
w:58932
x:4034
y:45944
z:2387
```

2. 1. `./run-mapreduce "counter" inpuut-alice30.txt 4`
```
a:8791
b:1475
c:2399
d:4931
e:13574
f:2001
g:2531
h:7374
i:7514
j:146
k:1158
l:4716
m:2107
n:7016
o:8146
p:1524
q:209
r:5437
s:6499
t:10689
u:3468
v:846
w:2675
x:148
y:2264
z:78
```