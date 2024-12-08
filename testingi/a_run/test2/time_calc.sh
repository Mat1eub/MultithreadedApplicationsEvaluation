#!/usr/bin/bash
OUTPUT_FILE=stderr
#"results/test.csv"

echo "problem,nb_of_threads,time" 

for i in 2 4 8 16 32
do
    for k in {1..5}
    do
        /usr/bin/time -f "$1, $i, %e" -a timeout 20s ./$1.o $i  2>&1
    done
done
