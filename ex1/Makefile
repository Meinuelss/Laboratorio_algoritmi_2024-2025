CC = gcc

all: ordered_records_main ordered_records_test

CFLAGS = -g -Wall -Wextra -Wpedantic -Wconversion

INCLUDES = src/*.h

COMMON_DEPS = $(INCLUDES) Makefile

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

ordered_records_main : build/ordered_records_main.o build/ordered_records.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/main_ex1 build/ordered_records_main.o build/ordered_records.o build/unity.o

ordered_records : build/ordered_records.o build/ordered_records_main.o $(COMMON_DEPS)
	$(CC) -o bin/ordered_records build/ordered_records.o build/ordered_records_main.o

ordered_records_test : build/ordered_records_test.o build/ordered_records.o build/unity.o
	$(CC) -o bin/test_ex1 build/ordered_records_test.o build/ordered_records.o build/unity.o


clean:
	rm -f build/* bin/*

test:
	bin/./test_ex1 

run_main:
	bin/./main_ex1 /Users/utente/Desktop/Lab_ASD/ex_1/records.csv /Users/utente/Desktop/Lab_ASD/ex_1/sorted.csv 1 1

run:
	bin/./main_ex1 ../records.csv ../sorted.csv 1  1