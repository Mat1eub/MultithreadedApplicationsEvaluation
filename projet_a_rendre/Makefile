# Variables des chemins
PH = src/philosophers
PHTS = src/philosophers_with_sem_TS
PHTTS = src/philosophers_with_sem_TTS

PC = src/producerconsummer
PCTS = src/producerconsummer_with_sem_TS
PCTTS = src/producerconsummer_with_sem_TTS

LE = src/readerwriter
LETS = src/readerwriter_with_sem_TS
LETTS = src/readerwriter_with_sem_TTS

TS = src/test-and-set
TTS = src/test-and-test-and-set

OUTPUT = results/output.csv

# Règle principale : all
all: init_output ph phts phtts pc pcts pctts le lets letts ts tts

init_output:
	@echo "problem,nb_of_threads,time" > $(OUTPUT)

ph:
	gcc -pthread $(PH).c -o $(PH).o
	bash time_calc_1.sh $(OUTPUT) $(PH)
	make clean

phts:
	gcc -pthread $(PHTS).c -o $(PHTS).o
	bash time_calc_1.sh $(OUTPUT) $(PHTS)
	clean

phtts:
	gcc -pthread $(PHTTS).c -o $(PHTTS).o
	bash time_calc_1.sh $(OUTPUT) $(PHTTS)
	make clean

pc:
	gcc -pthread $(PC).c -o $(PC).o
	bash time_calc_2.sh $(OUTPUT) $(PC)
	make clean

pcts:
	gcc -pthread $(PCTS).c -o $(PCTS).o
	bash time_calc_2.sh $(OUTPUT) $(PCTS)
	make clean

pctts:
	gcc -pthread $(PCTTS).c -o $(PCTTS).o
	bash time_calc_2.sh $(OUTPUT) $(PCTTS)
	make clean

le:
	gcc -pthread $(LE).c -o $(LE).o
	bash time_calc_2.sh $(OUTPUT) $(LE)
	make clean

lets:
	gcc -pthread $(LETS).c -o $(LETS).o
	bash time_calc_2.sh $(OUTPUT) $(LETS)
	make clean

letts:
	gcc -pthread $(LETTS).c -o $(LETTS).o
	bash time_calc_2.sh $(OUTPUT) $(LETTS)
	make clean

ts:
	gcc -pthread $(TS).c -o $(TS).o
	bash time_calc_1.sh $(OUTPUT) $(TS)
	make clean

tts:
	gcc -pthread $(TTS).c -o $(TTS).o
	bash time_calc_1.sh $(OUTPUT) $(TTS)
	make clean

graf:
	python3 results/performances_graphs.py

clean:
	rm -f src/*.o
