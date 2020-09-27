CXX=clang++

CFLAGS=-std=c++14 -stdlib=libc++

minesweeper.o: minesweeper.h minesweeper.cc
	$(CXX) $(CFLAGS) -c minesweeper.cc

main: minesweeper.o
	$(CXX) $(CFLAGS) -o main minesweeper.o main.cc

clean:
	$(RM) *.o *.gch a.out
