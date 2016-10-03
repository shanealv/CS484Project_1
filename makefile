CC=g++
CFLAGS=-c -std=c++11 -g
all: main.o BigInteger.o
	$(CC) main.o BigInteger.o -o program

main.o: main.cpp BigInteger.h
	$(CC) $(CFLAGS) BigInteger.h main.cpp 

BigInteger.o: BigInteger.h BigInteger.cpp
	$(CC) $(CFLAGS) BigInteger.h BigInteger.cpp

clean:
	rm -f *.o *.gch *.exe program


	
