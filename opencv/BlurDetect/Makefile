
CFLAGS = -std=c++11
CFLAGS += $(shell pkg-config --cflags opencv)
LDFLAGS = $(shell pkg-config --libs opencv)

OBJ = BlurDetect.cpp utimer.cpp
TARGET = BlurDetect

all:
	g++ $(CFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)
