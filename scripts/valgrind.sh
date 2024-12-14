programs=("philo" "philo_tas" "philo_tts" "prodcons" "prodconsts" "prodconstts" "readwrite" "readwritets" "readwritetts")

for prob in "${programs[@]}"; do
    # Ensure the program is compiled
    if ! make $prob; then
        echo "Error: Could not compile $prob" #>&2
        continue
    fi

    valgrind ./$prob 8
    
done