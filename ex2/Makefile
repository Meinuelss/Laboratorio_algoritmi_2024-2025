CC = gcc

all: distance_main distance_test

CFLAGS = -g -Wall -Wextra -Wpedantic -Wconversion

INCLUDES = src/*.h

COMMON_DEPS = $(INCLUDES) Makefile

build/%.o: src/%.c $(COMMON_DEOS)
	$(CC) $(CFLAGS) -c $< -o $@

distance_main : build/distance_main.o build/distance.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/main_ex2 build/distance_main.o build/distance.o build/unity.o

distance: build/distance.o build/distance_main.o $(COMMON_DEPS)
	%(CC) -o bin/distance build/distance.o build/distance_main.o

distance_test : build/distance_test.o build/distance.o build/unity.o
	$(CC) -o bin/test_ex2 build/distance_test.o build/distance.o build/unity.o

clean:
	rm -f build/* bin/*

test:
	bin/./test_ex2

run:
	bin/./main_ex2 ../dictionary.txt ../correctme.txt


