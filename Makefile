FLAGS = -lsystemc -lpthread

main: 
	g++ -g src/main.cpp -o main $(FLAGS)

main.o:
	$(CC) -c main.cpp

debug:
	g++ -g src/main.cpp -o main $(FLAGS)
	valgrind --track-origins=yes --leak-check=full ./main

clean:
	rm main
	rm main.o
	rm tracefile.vcd


wave:
	gtkwave tracefile.vcd