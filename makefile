CC=g++ -std=c++11 -g
exe=assignment4

# Complete the makefile
# Your code here:
$(exe): bats.o event.o game.o gold.o room.o stalactites.o wumpus.o main.cpp
	$(CC) bats.o event.o game.o gold.o room.o stalactites.o wumpus.o main.cpp -o $(exe)

bats.o: bats.cpp bats.h
	$(CC) -c bats.cpp

event.o: event.cpp event.h
	$(CC) -c event.cpp

game.o: game.cpp game.h
	$(CC) -c game.cpp

gold.o: gold.cpp gold.h
	$(CC) -c gold.cpp

room.o: room.cpp room.h
	$(CC) -c room.cpp

stalactites.o: stalactites.cpp stalactites.h
	$(CC) -c stalactites.cpp

wumpus.o: wumpus.cpp wumpus.h
	$(CC) -c wumpus.cpp

clear:
	rm -f *.out *.o

clean:
	rm -f *.out *.o $(exe)

run: $(exe)
	@clear && $(exe)