ROOT_DIR=$(PWD)
SRC_DIR=$(ROOT_DIR)/src
INC_DIR=$(ROOT_DIR)/include
OUT_DIR=$(ROOT_DIR)/bin
CC=g++
CFLAGS=-W -Wall -ansi -pedantic -std=c++0x -DSIMULATOR
LDFLAGS=-DSIMULATOR

INCLUDE=-I. -I/usr/include -I$(INC_DIR)
LIBS=-L/usr/lib

EXEC=simulator
SRC=$(wildcard $(SRC_DIR)/*.cpp) 
OBJ=$(SRC:.cpp=.o)

all: main

main: $(OBJ) 
	$(CC) -o $(OUT_DIR)/$(EXEC) $^ $(LDFLAGS) $(LIBS) $(INCLUDE)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

.PHONY: clean mrproper

clean:
	rm -f $(SRC_DIR)/*.o

mrproper: clean
	rm -f $(OUT_DIR)/$(EXEC)

