FLAGS = -lsystemc -lpthread

main:	
	g++ -g src/main.cpp src/OpenQM/qm.cpp src/OpenQM/implicant.cpp -o main $(FLAGS)

debug:
	g++ -g src/main.cpp -o main $(FLAGS)
	valgrind --track-origins=yes --leak-check=full ./main

clean:
	rm main
	rm tracefile.vcd

wave: main
	gtkwave tracefile.vcd