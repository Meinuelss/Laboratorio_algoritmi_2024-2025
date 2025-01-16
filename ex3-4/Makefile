CC=gcc

CFLAGS = -g -Wall -Wextra -Wpedantic -Wconversion

INCLUDES = src/*.h

COMMON_DEPS = $(INCLUDES) Makefile

all: bin/main_ex3-4 bin/test_ex3-4

bin/main_ex3-4: build/hash_table.o build/graph.o build/bfs.o build/main.o $(COMMON_DEPS)
	$(CC) $(CFLAGS) build/hash_table.o build/graph.o build/bfs.o build/main.o -o bin/main_ex3-4

bin/test_ex3-4: build/test.o build/hash_table.o build/graph.o build/bfs.o build/unity.o $(COMMON_DEPS)
	$(CC) $(CFLAGS) build/test.o build/hash_table.o build/graph.o build/bfs.o build/unity.o -o bin/test_ex3-4

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f build/* bin/*
	@echo "Pulizia completata."

run:
	bin/main_ex3-4 ./italian_dist_graph.csv torino ./output.txt
	
test:
	bin/test_ex3-4
	
	