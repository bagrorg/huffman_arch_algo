.PHONY: all clean test

all: hw_03
test: hw_03_test

CFLAGS= -I include -Wall -Werror -g -std=c++11

obj:
	mkdir obj

hw_03: obj obj/huffman.o obj obj/huffman_tree.o obj obj/main.o
	g++ obj/main.o obj/huffman.o obj/huffman_tree.o -o hw_03

obj/huffman.o: src/huffman.cpp include/huffman.h
	g++ $(CFLAGS) -c src/huffman.cpp -o obj/huffman.o

obj/huffman_tree.o: src/huffman_tree.cpp include/huffman_tree.h
	g++ $(CFLAGS) -c src/huffman_tree.cpp -o obj/huffman_tree.o

obj/main.o: src/main.cpp
	g++ $(CFLAGS) -c src/main.cpp -o obj/main.o


hw_03_test: obj obj/test.o obj obj/huffman.o obj/huffman_tree.o obj obj/huffman_test.o obj obj/autotest.o
	g++ obj/test.o obj/huffman.o obj/huffman_test.o obj/autotest.o obj/huffman_tree.o -o hw_03_test

obj/test.o: test/test.cpp
	g++ $(CFLAGS) -c test/test.cpp -o obj/test.o

obj/autotest.o: test/autotest.cpp test/autotest.h
	g++ $(CFLAGS) -c test/autotest.cpp -o obj/autotest.o

obj/huffman_test.o: test/huffman_test.cpp test/huffman_test.h
	g++ $(CFLAGS) -c test/huffman_test.cpp -o obj/huffman_test.o

clean:
	rm -rf ./obj hw_03 hw_03_test

