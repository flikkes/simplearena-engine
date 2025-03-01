all: loop

loop:
	g++ --std=c++11 *.cpp `pkg-config --cflags --libs gtk4` -o loop.o

clean: 
	rm *.o
