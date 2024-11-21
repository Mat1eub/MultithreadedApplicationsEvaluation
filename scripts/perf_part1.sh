#!/bin/bash

programs=("philsophers" "prodcons" "readwrite")

threads=( 2 4 8 16 32 )

output="../results/performances_part1.csv"

echo "problem, nb_of_threads, time" > $output

for prob in "${programs[@]}"; do
    # Loop into each threads configuration
    for t in "${threads[@]}"; do
        # TODO trouver comment séparer le nombre de threads
        exec_time=$( { /usr/bin/time -f "%e" ./$prob N=$t > /dev/null; } 2>&1 )
        echo "$prog, $t, $exec_time" >> $output
    done
done
