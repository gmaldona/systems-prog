Authored By: GREGORY MALDONADO

B-Number:    B00784284

Date:        2024-07-28

STATUS: Completed.
BONUS:  Completed.
DESCRIPTION: Implementation of MapReduce.

Performance:

1 process finding "CH4" in input-warpeace.txt
```
maldonadog@unova ~/sdv/gmaldonado.cs.binghamton.edu/cs551/2024-05-28/systems-prog/mapreduce
 % ./run-mapreduce "finder" input-warpeace.txt 1 "CH4"
***** RESULT ***** 
Result file: mr.rst
Map worker pids: 8793 
Reduce worker pid: 8793
Processing time (us): 16566
```

vs


8 processes finding "CH4" in input-warpeace.txt
```
maldonadog@unova ~/sdv/gmaldonado.cs.binghamton.edu/cs551/2024-05-28/systems-prog/mapreduce
 % ./run-mapreduce "finder" input-warpeace.txt 8 "CH4"
***** RESULT ***** 
Result file: mr.rst
Map worker pids: 8837 8838 8839 8840 8841 8842 8843 8836 
Reduce worker pid: 8836
Processing time (us): 5483
```

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

2. `./run-mapreduce "counter" input-alice30.txt 4`
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

3. `./run-mapreduce "finder" input-alice30.txt 4 "again, " && cat mr.rst | head -3`
```
heads down and saying "Come up again, dear!"  I shall only look
again, and we won't talk about cats or dogs either, if you don't
again, and the little golden key was lying on the glass table as
one for catching mice--oh, I beg your pardon!' cried Alice again,
```