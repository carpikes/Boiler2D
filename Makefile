CFLAGS=-Wall -std=c++11
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf

all:
	g++ -g -o microgue $(CFLAGS) $(LDFLAGS) \
	Text.cc Config.cc main.cc Image.cc Engine.cc
