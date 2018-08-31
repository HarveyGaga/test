##########################################################
#
#
#  copyright zhht.ltd
#
#
##########################################################

CC = g++
CXX = g++
LDFLAGS = -g
CFLAGS = -W -g
OPENCVFLAGS = `pkg-config --cflags --libs opencv`
OBJ = main.o video_api.o utimer.o
#LIB += -L./ -L /home/nvidia/ffmpeg-3.3.2/lib -L /home/nvidia/libconfig/libconfig-1.5/lib/.libs/ 
LIB += -L./ -L /home/nvidia/libconfig/libconfig-1.5/lib/.libs/ -L /home/nvidia/ffmpeg_gpu 
LIB +=    -lm -lpthread  -lz    -lavutil   -lrt -lopencv_core  -lopencv_imgproc -lopencv_gpu  -lopencv_highgui -lconfig++ 
LIB += -lswscale -lswresample -lavcodec  -lavformat 
INCLUDE += -I /home/nvidia/ffmpeg-2.8.13  -I. 
TARGET = main 
ARCH = $(shell arch)

ifeq ($(findstring arm, $(ARCH)), arm)
	CFLAGS += -DGPIO
endif

all: $(OBJ)
	$(CXX) $(LDFLAGS)  $(OBJ) -o $(TARGET)  $(OPENCVFLAGS) $(LIB) $(INCLUDE)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDE) 

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@ $(INCLUDE) 


clean:
	rm $(TARGET) $(OBJ) *.cpp~ *.c~ *.h~ *.tmp -rf
