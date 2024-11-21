#!/bin/bash

programs=("philo_graphs" "prodcons_graphs" "readwrite_graphs")
threads=(2 4 8 16 32)
output="results/performances_part1.csv"



# Add header to the CSV file
echo "problem,nb_of_threads,time" > $output

for prob in "${programs[@]}"; do
    # Ensure the program is compiled
    if ! make $prob; then
        echo "Error: Could not compile $prob" #>&2
        continue
    fi

    # Loop through thread configurations
    for t in "${threads[@]}"; do
        exec_time=$(/usr/bin/time -f "%e" ./$prob $t 2>&1 > /dev/null)
        echo "$prob,$t,$exec_time" >> $output
    done
done
