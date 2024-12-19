CC = gcc

all: hash_main hash_test

CFLAGS = -g -Wall -Wextra -Wpedantic -Wconversion

INCLUDES = src/*.h

COMMON_DEPS = $(INCLUDES) Makefile

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

hash_main: build/hash_main.o build/hash_table.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/main_ex3 build/hash_main.o build/hash_table.o build/unity.o

hash_table: build/hash_table.o build/hash_main.o $(COMMON_DEPS)
	$(CC) -o bin/hash_table build/hash_table.o build/hash_main.o

hash_test : build/hash_test.o build/hash_table.o build/unity.o
	$(CC) -o bin/test_ex3 build/hash_test.o build/hash_table.o build/unity.o

clean:
	rm -f build/* bin/*

test:
	bin/./test_ex3

run:	
	bin/./main_ex3 iliade.txt 3
 