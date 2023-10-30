FLAGS = -lsystemc -lpthread

main: 
	g++ main.cpp -o main $(FLAGS)
	./main

main.O:
	$(CC) -c main.cpp

clean:
	rm main

wave:
	gtkwave tracefile.vcd