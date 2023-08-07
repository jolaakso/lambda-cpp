CXX = g++

main: root.o
	$(CXX) *.cpp -o lambdaint

%.o:
	$(CXX) -c *.cpp

clean:
	rm *.o