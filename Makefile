# Makefile for main.c // 3Sum program
build:
	@ gcc -o out -Wall main.c -lpthread

test:
	@ ./out

clean:
	@ rm -f out
	@ clear
