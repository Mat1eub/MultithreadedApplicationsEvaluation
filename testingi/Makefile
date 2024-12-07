PH = philosophers

PC = producerconsummer

LE = readerwriter


all:
	gcc -pthread $(PH).c -o $(PH).o
	
	gcc -pthread $(PC).c -o $(PC).o

	gcc -pthread $(LE).c -o $(LE).o	
	
	bash time_calc.sh  $(PH) $(PC)  $(LE)
	
	make clean

clean:
	rm -f *.o

