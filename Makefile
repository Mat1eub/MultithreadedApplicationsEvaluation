# Everything here is explained in the README at the section "How to use this project"
# Variables
CC = gcc
CFLAGS = -Wall -pthread -march=armv8-a 
SRC_DIR = src
OBJ_DIR = objects
BIN_DIR = bin
SCRIPT_DIR = scripts
SRC = $(wildcard $(SRC_DIR)/*.c)  # Trouve tous les fichiers .c dans src
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)  # Crée les fichiers .o dans objects

# Compile les .c dans src et met le resultat ().o) dans objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

SEMATS = fctsemaphore_TS
SEMATTS = fctsemaphore_TTS


all:
	bash $(SCRIPT_DIR)/performances.sh
	make clean

# =========== PHILOSOPHERS ===========
philo: $(OBJ_DIR)/philosophers.o | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

philots: $(OBJ_DIR)/philosophers_with_sem_TS.o $(OBJ_DIR)/$(SEMATS).o | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

philotts: $(OBJ_DIR)/philosophers_with_sem_TTS.o $(OBJ_DIR)/$(SEMATTS).o | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

test_philosophers:
	bash $(SCRIPT_DIR)/philosophers_time.sh
	make clean

# =========== PRODUCERS & CONSUMMERS ===========
prodcons: $(OBJ_DIR)/producerconsummer.o | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

prodconsts: $(OBJ_DIR)/producerconsummer_with_sem_TS.o $(OBJ_DIR)/$(SEMATS).o | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

prodconstts: $(OBJ_DIR)/producerconsummer_with_sem_TTS.o $(OBJ_DIR)/$(SEMATTS).o | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

test_producersconsummers:
	bash $(SCRIPT_DIR)/prodcons_time.sh
	make clean

# Personnalized number of P and C
prodconsperso: $(OBJ_DIR)/producerconsummer.o | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

prodconstsperso: $(OBJ_DIR)/producerconsummer_with_sem_TS.o $(OBJ_DIR)/$(SEMATS).o | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

prodconsttsperso: $(OBJ_DIR)/producerconsummer_with_sem_TTS.o $(OBJ_DIR)/$(SEMATTS).o | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

# =========== READERS & WRITERS ===========
readwrite: $(OBJ_DIR)/readerwriter.o | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

readwritets: $(OBJ_DIR)/readerwriter_with_sem_TS.o $(OBJ_DIR)/$(SEMATS).o | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

readwritetts: $(OBJ_DIR)/readerwriter_with_sem_TTS.o $(OBJ_DIR)/$(SEMATTS).o | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

test_readerswriters:
	bash $(SCRIPT_DIR)/readerwriter_time.sh
	make clean

# =========== CLEANING THE MESS ===========

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/* *~

.PHONY: clean all
