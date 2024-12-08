PH = philosophers_with_sem_TS


all:
	gcc -pthread $(PH).c -o $(PH).o
	
	bash time_calc.sh  $(PH) $(PHT)
	
	make clean

clean:
	rm -f *.o

