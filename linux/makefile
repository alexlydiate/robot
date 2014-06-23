CC=g++
CFLAGS=-g -Wall
INCLUDE=-I/usr/local/include/opencv -I/usr/local/include
SRC=./src/r_o_p.cpp
LIBS=-lopencv_core -lopencv_objdetect -lopencv_highgui -lopencv_imgproc -lncurses
EXEC=./rop

all:
	$(CC) $(CFLAGS) $(SRC) -std=c++0x $(INCLUDE) $(LIBS) -o $(EXEC)
