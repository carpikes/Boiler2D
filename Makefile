CFLAGS=-Wall -std=c++11
LDFLAGS=-lSDL2 -lSDL_image

all:
	g++ -o microgue $(CFLAGS) main.cc Image.cc $(LDFLAGS)
