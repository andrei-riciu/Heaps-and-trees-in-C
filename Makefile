
CFLAGS = -g -Wall -Wextra
CC = gcc

all: build

build:
	$(CC) $(CFLAGS) satelit.c main.c -o tema2
clean:
	rm -rf tema2