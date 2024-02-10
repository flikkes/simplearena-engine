all: loop

loop:
	g++ *.cpp `pkg-config --cflags --libs gtk4` -o loop.o

clean: 
	rm *.o