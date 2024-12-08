PH = philosophers_with_sem_TS


all:
	gcc -pthread $(PH).c -o $(PH).o
	
	bash time_calc.sh  $(PH)
	
	make clean

clean:
	rm -f *.o

