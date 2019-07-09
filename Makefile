CC = gcc
.PHONY: default build run
default: build run
build: main.c 
	$(CC) -o main string/init.c main.c
run: main
	./main
main.c:
	$(error "main.c undefined")
