# Variables
CC = gcc
CFLAGS = -Wall -pthread
PHILO = philosophers_exec
PRODCONS = producerconsummer_exec
SRC_DIR = src
OBJ_DIR = objects
SRC = $(wildcard $(SRC_DIR)/*.c)  # Trouve tous les fichiers .c dans src
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)  # Crée les fichiers .o dans objects

# Valeur par défaut des variables
N ?= 5
A ?= 5
B ?= 5

# Pour l'instant philo, encore à décider d'un truc plus général
all: $(PHILO)


# .c dans src => .o dans objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< $(CFLAGS) -o $@


# =========== PHILOSOPHERS ===========
$(PHILO): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	$(MAKE) run EXEC=$(PHILO) ARG=$(N)

philosophers: $(PHILO)

# =========== PRODUCERS & CONSUMMERS ============
$(PRODCONS): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	$(MAKE) run EXEC=$(PRODCONS) ARG="$(A) $(B)"

prodcons: $(PRODCONS)

# Pour exécuter chaque exécutable après la compilation
run:
	./$(EXEC) $(ARG)

clean:
	rm -f $(OBJ) $(PHILO) $(PRODCONS)

.PHONY: clean run philosophers all
