# magnet Makefile script

CC=gcc
RM=rm -f
CFLAGS=-O3 -s
SOURCE=main.c
OUTPUT=magnet

.PHONY: interpreter clean all

interpreter: clean
	$(CC) $(CFLAGS) $(SOURCE) -o $(OUTPUT)

clean:
	$(RM) $(OUTPUT)

all: interpreter clean
