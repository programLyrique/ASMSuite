ROOT_DIR=$(PWD)
SRC_DIR=$(ROOT_DIR)
INC_DIR=$(ROOT_DIR)
OUT_DIR=$(ROOT_DIR)
CC=g++
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=

INCLUDE=-I. -I/usr/include -I$(INC_DIR)
LIBS=-L/usr/lib

EXEC=main
SRC=$(wildcard $(SRC_DIR)/*.cpp) 
OBJ=$(SRC:.cpp=.o)

all: $(EXEC)

main: $(OBJ) 
	$(CC) -o $(OUT_DIR)/$@ $^ $(LDFLAGS) $(LIBS) $(INCLUDE)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

.PHONY: clean mrproper

clean:
	rm -rf $(SRC_DIR)/*.o
	rm -rf $(ROOT_DIR)/screen.*.o

mrproper: clean
	rm -rf $(OUT_DIR)/$(EXEC)

