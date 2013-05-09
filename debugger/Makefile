ROOT_DIR=$(PWD)
SRC_DIR=$(ROOT_DIR)/src
SRC_DIR2=$(ROOT_DIR)/../simulator/src
INC_DIR=$(ROOT_DIR)/include
INC_DIR2=$(ROOT_DIR)/../simulator/include
OUT_DIR=$(ROOT_DIR)/bin
CC=g++
CFLAGS=-W -Wall -ansi -pedantic -g -ggdb -std=c++0x
LDFLAGS=

INCLUDE=-I. -I/usr/include -I$(INC_DIR) -I$(INC_DIR2)
LIBS=-L/usr/lib

EXEC=debugger
SRC=$(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR2)/*.cpp)
OBJ=$(SRC:.cpp=.o)

all: main

main: $(OBJ)
	$(CC) -o $(OUT_DIR)/$(EXEC) $^ $(LDFLAGS) $(LIBS) $(INCLUDE)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

.PHONY: clean mrproper

clean:
	rm -rf $(SRC_DIR)/*.o
	rm -rf $(SRC_DIR2)/*.o

mrproper: clean
	rm -rf $(OUT_DIR)/$(EXEC)
