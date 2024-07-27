# CS 551 Project "MapReduce".
#
# author: Gregory Maldonado
# email : gmaldonado@cs.binghamton.edu
# date  : 2024-07-04
# web   : https://cs.binghamton.edu/~gmaldonado/
#
# Graduate student @ Thomas J. Watson College of Engineering and Applied
# Sciences, Binghamton University.

git_root=$(git worktree list | cut -d' ' -f1)

if [ -d build ]; then

  valgrind --leak-check=full \
           --show-leak-kinds=all \
           --track-origins=yes \
           --verbose \
           --log-file=build/valgrind-out.txt \
           "$git_root"/mapreduce/main