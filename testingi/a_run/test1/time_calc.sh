#!/usr/bin/bash
OUTPUT_FILE=stderr
#"results/test.csv"

echo "problem,nb_of_threads,time" 

for i in 2 4 8
do
    for k in {1..5}
    do
        /usr/bin/time -f "$1, $i, %e" -a timeout 22s ./$1.o $i  2>&1
        /usr/bin/time -f "$2, $i, %e" -a timeout 22s ./$2.o $i  2>&1
    done
done
