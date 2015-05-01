mazegame: main.o maze.o player.o
	g++ -std=gnu++11 main.o maze.o player.o -o mazegame

main.o: main.cpp maze.h player.h
	g++ -c -std=gnu++11 main.cpp

maze.o: maze.cpp maze.h
	g++ -c -std=gnu++11 maze.cpp

player.o: player.cpp player.h
	g++ -c -std=gnu++11 player.cpp

clean:
	rm *.o mazegame
