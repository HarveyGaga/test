
CFLAGS = $(shell pkg-config --cflags opencv)
LDFLAGS = $(shell pkg-config --libs opencv)

all:
	g++ $(CFLAGS) rotate.cpp -o rotate $(LDFLAGS)
