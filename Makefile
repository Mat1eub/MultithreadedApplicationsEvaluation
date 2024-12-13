# Everything here is explained in the README at the section "How to use this project"
# Variables
CC = gcc
CFLAGS = -Wall -pthread -march=armv8-a 
SRC_DIR = src
OBJ_DIR = objects
SRC = $(wildcard $(SRC_DIR)/*.c)  # Trouve tous les fichiers .c dans src
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)  # Crée les fichiers .o dans objects

# Compile les .c dans src et met le resultat ().o) dans objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

SEMATS = fctsemaphore_TS
SEMATTS = fctsemaphore_TTS

all:
	bash performances.sh
	make clean

# =========== PHILOSOPHERS ===========
philo: $(OBJ_DIR)/philosophers.o
	$(CC) -o $@ $^ $(CFLAGS)

philots: $(OBJ_DIR)/philosophers_with_sem_TS.o $(OBJ_DIR)/$(SEMATS).o
	$(CC) -o $@ $^ $(CFLAGS)

philotts: $(OBJ_DIR)/philosophers_with_sem_TTS.o $(OBJ_DIR)/$(SEMATTS).o
	$(CC) -o $@ $^ $(CFLAGS)

test_philosophers:
	bash philosophers_time.sh
	make clean

# =========== PRODUCERS & CONSUMMERS ============
prodcons: $(OBJ_DIR)/producerconsummer.o
	$(CC) -o $@ $^ $(CFLAGS)

prodconsts: $(OBJ_DIR)/producerconsummer_with_sem_TS.o $(OBJ_DIR)/$(SEMATS).o
	$(CC) -o $@ $^ $(CFLAGS)

prodconstts: $(OBJ_DIR)/producerconsummer_with_sem_TTS.o $(OBJ_DIR)/$(SEMATTS).o
	$(CC) -o $@ $^ $(CFLAGS)

test_producersconsummers:
	bash prodcons_time.sh
	make clean

# Personnalized number of P and C
prodconsperso: $(OBJ_DIR)/producerconsummer.o
	$(CC) -o $@ $^ $(CFLAGS)

prodconstsperso: $(OBJ_DIR)/producerconsummer_with_sem_TS.o $(OBJ_DIR)/$(SEMATS).o
	$(CC) -o $@ $^ $(CFLAGS)

prodconsttsperso: $(OBJ_DIR)/producerconsummer_with_sem_TTS.o $(OBJ_DIR)/$(SEMATTS).o
	$(CC) -o $@ $^ $(CFLAGS)

# =========== READERS & WRITERS ============
readwrite: $(OBJ_DIR)/readerwriter.o
	$(CC) -o $@ $^ $(CFLAGS)

readwritets: $(OBJ_DIR)/readerwriter_with_sem_TS.o $(OBJ_DIR)/$(SEMATS).o
	$(CC) -o $@ $^ $(CFLAGS)

readwritetts: $(OBJ_DIR)/readerwriter_with_sem_TTS.o $(OBJ_DIR)/$(SEMATTS).o
	$(CC) -o $@ $^ $(CFLAGS)

test_readerswriters:
	bash readerwriter_time.sh
	make clean

clean:
	rm -f $(OBJ) philo philots philotts prodcons prodconsts prodconstts readwrite readwritets readwritetts

.PHONY: clean run philosophers all
