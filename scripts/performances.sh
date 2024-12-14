#!/bin/bash

programs=("philo" "philo_tas" "philo_tts" "prodcons" "prodconsts" "prodconstts" "readwrite" "readwritets" "readwritetts")
threads=(2 4 8 16 32)
output="results/performances_all.csv"

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
            exec_time=$(/usr/bin/time -f "%e" ./$prob $t 2>&1 > /dev/null )
            echo "$prob,$t,$exec_time" >> $output
        done
    done
done
