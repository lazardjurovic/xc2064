FLAGS = -lsystemc -lpthread

main: 
	g++ -g main.cpp -o main $(FLAGS)
	./main

main.o:
	$(CC) -c main.cpp

debug:
	g++ -g main.cpp -o main $(FLAGS)
	valgrind --track-origins=yes --leak-check=full ./main

clean:
	rm main
	rm tracefile.vcd
	rm main.o

wave:
	gtkwave tracefile.vcd

