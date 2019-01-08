# Compiler choice
CC=gcc
# Binary name
BIN=sistem.exe
# Compiler FLAGS
CFLAGS = -Wall

# *********************************************

# Build binary and then clean
all: build clean

build: main.o context.o file_helper.o lcs.o learning_mode.o linked_list.o  processing_mode.o string_helper.o trie.o
	$(CC) $(CFLAGS) -lm -o $(BIN) main.o context.o file_helper.o lcs.o learning_mode.o linked_list.o  processing_mode.o string_helper.o trie.o

context.o: context.c context.h config.h
	$(CC) $(CFLAGS) -c context.c

file_helper.o: file_helper.c config.h context.h trie.h string_helper.h lcs.h
	$(CC) $(CFLAGS) -c file_helper.c

lcs.o: lcs.c
	$(CC) $(CFLAGS) -c lcs.c

learning_mode.o: learning_mode.c config.h context.h trie.h string_helper.h lcs.h
	$(CC) $(CFLAGS) -c learning_mode.c

linked_list.o: linked_list.c
	$(CC) $(CFLAGS) -c linked_list.c

main.o: main.c config.h context.h trie.h linked_list.h learning_mode.h processing_mode.h
	$(CC) $(CFLAGS) -c main.c

processing_mode.o: processing_mode.c config.h context.h trie.h file_helper.h
	$(CC) $(CFLAGS) -c processing_mode.c

string_helper.o: string_helper.c
	$(CC) $(CFLAGS) -c string_helper.c

trie.o: trie.c config.h lcs.h string_helper.h linked_list.h
	$(CC) $(CFLAGS) -c trie.c
	
clean:
	rm *.o