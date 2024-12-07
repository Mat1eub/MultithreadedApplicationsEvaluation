#!/usr/bin/bash
OUTPUT_FILE=stderr
#"results/test.csv"

echo "problem,nb_of_threads,time" 

for i in 2 4 8 16 32
do
    for k in {1..5}
    do
        /usr/bin/time -f "$1, $i, %e" -a ./$1.o $i  2>&1

        /usr/bin/time -f "$2, $i, %e" -a ./$2.o $((i/2)) $((i/2))  2>&1
      
        /usr/bin/time -f "$3, $i, %e" -a ./$3.o $((i/2)) $((i/2))  2>&1
        
    done
done
