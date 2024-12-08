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
all: 
	make init
	gcc -pthread $(PH).c -o $(PH).o
	bash time_calc_1.sh $(OUTPUT) $(PH)
	gcc -pthread $(PHTS).c -o $(PHTS).o
	bash time_calc_1.sh $(OUTPUT) $(PHTS)
	gcc -pthread $(PHTTS).c -o $(PHTTS).o
	bash time_calc_1.sh $(OUTPUT) $(PHTTS)
	gcc -pthread $(PC).c -o $(PC).o
	bash time_calc_2.sh $(OUTPUT) $(PC)
	gcc -pthread $(PCTS).c -o $(PCTS).o
	bash time_calc_2.sh $(OUTPUT) $(PCTS)
	gcc -pthread $(PCTTS).c -o $(PCTTS).o
	bash time_calc_2.sh $(OUTPUT) $(PCTTS)
	gcc -pthread $(LE).c -o $(LE).o
	bash time_calc_2.sh $(OUTPUT) $(LE)
	gcc -pthread $(LETS).c -o $(LETS).o
	bash time_calc_2.sh $(OUTPUT) $(LETS)
	gcc -pthread $(LETTS).c -o $(LETTS).o
	bash time_calc_2.sh $(OUTPUT) $(LETTS)
	gcc -pthread $(TS).c -o $(TS).o
	bash time_calc_1.sh $(OUTPUT) $(TS)
	gcc -pthread $(TTS).c -o $(TTS).o
	bash time_calc_1.sh $(OUTPUT) $(TTS)
	make clean

init:
	
	echo "problem,nb_of_threads,time" > $(OUTPUT)
		
ph:
	make init
	gcc -pthread $(PH).c -o $(PH).o
	bash time_calc_1.sh $(OUTPUT) $(PH)
	make clean

phts:
	make init
	gcc -pthread $(PHTS).c -o $(PHTS).o
	bash time_calc_1.sh $(OUTPUT) $(PHTS)
	clean

phtts:
	make init
	gcc -pthread $(PHTTS).c -o $(PHTTS).o
	bash time_calc_1.sh $(OUTPUT) $(PHTTS)
	make clean

pc:
	make init
	gcc -pthread $(PC).c -o $(PC).o
	bash time_calc_2.sh $(OUTPUT) $(PC)
	make clean

pcts:
	make init
	gcc -pthread $(PCTS).c -o $(PCTS).o
	bash time_calc_2.sh $(OUTPUT) $(PCTS)
	make clean

pctts:
	make init
	gcc -pthread $(PCTTS).c -o $(PCTTS).o
	bash time_calc_2.sh $(OUTPUT) $(PCTTS)
	make clean

le:
	make init
	gcc -pthread $(LE).c -o $(LE).o
	bash time_calc_2.sh $(OUTPUT) $(LE)
	make clean

lets:
	make init
	gcc -pthread $(LETS).c -o $(LETS).o
	bash time_calc_2.sh $(OUTPUT) $(LETS)
	make clean

letts:
	make init
	gcc -pthread $(LETTS).c -o $(LETTS).o
	bash time_calc_2.sh $(OUTPUT) $(LETTS)
	make clean

ts:
	make init
	gcc -pthread $(TS).c -o $(TS).o
	bash time_calc_1.sh $(OUTPUT) $(TS)
	make clean

tts:
	make init
	gcc -pthread $(TTS).c -o $(TTS).o
	bash time_calc_1.sh $(OUTPUT) $(TTS)
	make clean

graf:
	python3 results/performances_graphs.py

clean:
	rm -f src/*.o
