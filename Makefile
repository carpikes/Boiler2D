CFLAGS=-Wall -std=c++11
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf

all:
	g++ -g -o microgue $(CFLAGS) $(LDFLAGS) \
	Engine/Text.cc Engine/Config.cc main.cc Engine/Image.cc Engine/Engine.cc
