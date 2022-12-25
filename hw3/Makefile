CC = gcc
CFLAGS = -g -Wall -Wvla -fsanitize=address

%: %.c
	$(CC) $(CFLAGS) shell.c -o shell

clean:
	rm -f shell