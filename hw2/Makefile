CC = gcc
CFLAGS = -g -Wall -Wvla -fsanitize=address

%: %.c
	$(CC) $(CFLAGS) $< -o $(basename $<)

all: 
	$(CC) $(CFLAGS) find.c -o find
	$(CC) $(CFLAGS) ls.c -o ls
	$(CC) $(CFLAGS) tree.c -o tree

clean:
	rm -f find
	rm -f ls
	rm -f tree