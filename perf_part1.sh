#!/bin/bash
export LC_NUMERIC="C"

programs=("philo" "prodcons" "readwrite_graphs")
threads=(2 4 8 16 32)
output="results/performances_part1.csv"

echo "problem,nb_of_threads,time" > $output # Headers of columns

for prob in "${programs[@]}"; do
    # Ensure the program is compiled
    if ! make $prob; then
        echo "Error: Could not compile $prob" #>&2
        continue
    fi

    # Loop through thread configurations
    for t in "${threads[@]}"; do
        for _ in {1..5}; do
            exec_time=$(/usr/bin/time -p ./$prob $t 2>&1 | grep real | awk '{print $2}')
            printf -v exec_time "%.3f" "$exec_time"
            echo "$prob,$t,$exec_time" >> $output
        done
    done
done
