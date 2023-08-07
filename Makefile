CC = g++

main: root.o
	$(CC) *.cpp

%.o:
	$(CC) -c *.cpp

clean:
	rm *.o