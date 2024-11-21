.SILENT:
# Variables
CC = gcc
CFLAGS = -Wall -pthread
PHILO = philosophers_exec
PRODCONS = producerconsummer_exec
SRC_DIR = src
OBJ_DIR = objects
SRC = $(wildcard $(SRC_DIR)/*.c)  # Trouve tous les fichiers .c dans src
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)  # Crée les fichiers .o dans objects

PHILO = philosophers_exec
PHILO2 = philo_graphs

# Valeur par défaut des variables
N ?= 5
P ?= 5
C ?= 5

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
	make clean

# =========== PRODUCERS & CONSUMMERS ============
$(PRODCONS): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	$(MAKE) run EXEC=$(PRODCONS) ARG1=$(P) ARG2=$(C)

prodcons: $(PRODCONS)

# Pour exécuter chaque exécutable après la compilation


# Make the performances graphs

$(PHILO2): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run:
	./$(EXEC) $(ARG) $(ARG1) $(ARG2)

clean:
	rm -f $(OBJ) $(PHILO) $(PRODCONS) $(PHILO2)

.PHONY: clean run philosophers all
