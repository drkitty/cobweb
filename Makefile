.SECONDEXPANSION:


SRC := client.c echo_server.c terminal.c
OBJ := $(SRC:%.c=%.o)
EXE := client echo_server

CC := gcc

CFLAGS := -std=c99 -g -Wall -Wextra -Werror -Wsign-compare

LDFLAGS := -pthread -lrt


all: $(EXE)

$(OBJ): $$(patsubst %.o,%.c,$$@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXE): $$@.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(EXE)

client.o: terminal.h
client: terminal.o


.DEFAULT_GOAL := all
.PHONY: all clean
