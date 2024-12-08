#!/usr/bin/bash
OUTPUT_FILE=$1

for i in 2 4 8 16 32
do
    for k in {1..5}
    do
        /usr/bin/time -f "$2, $i, %e" -o "$OUTPUT_FILE" -a ./$2.o $i > /dev/null 2>&1
    done
done
