# Variables
CC = gcc
CFLAGS = -Wall -pthread
SRC_DIR = src
OBJ_DIR = objects
SRC = $(wildcard $(SRC_DIR)/*.c)  # Trouve tous les fichiers .c dans src
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)  # Crée les fichiers .o dans objects

PHILO = philosophers_exec
PHILO2 = philo

PRODCONS = producerconsummer_exec
PRODCONS2 = prodcons

# Valeur par défaut des variables
N ?= 5
P ?= 5
C ?= 5

# Pour l'instant philo, encore à décider d'un truc plus général
all: $(PHILO) $(PRODCONS)


# Compile les .c dans src et met le resultat ().o) dans objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)


# =========== PHILOSOPHERS ===========
$(PHILO): $(OBJ_DIR)/philosophers.o
	$(CC) -o $@ $^ $(CFLAGS)
	$(MAKE) run EXEC=$(PHILO) ARG=$(N)

$(PHILO2): $(OBJ_DIR)/philosophers.o
	$(CC) -o $@ $^ $(CFLAGS)

philosophers: $(PHILO)
	make clean

# =========== PRODUCERS & CONSUMMERS ============
$(PRODCONS): $(OBJ_DIR)/producerconsummer.o
	$(CC) -o $@ $^ $(CFLAGS)
	$(MAKE) run EXEC=$(PRODCONS) ARG1=$(P) ARG2=$(C)

$(PRODCONS2): $(OBJ_DIR)/producerconsummer.o
	$(CC) -o $@ $^ $(CFLAGS)

prodcons: $(PRODCONS)


# Facilitate each execution
run:
	./$(EXEC) $(ARG) $(ARG1) $(ARG2)

clean:
	rm -f $(OBJ) $(PHILO) $(PRODCONS) $(PHILO2) $(PRODCONS2)

.PHONY: clean run philosophers all
