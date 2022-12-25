TARGET = testing
CC     = gcc
CFLAGS = -g -Wall -Wvla -fsanitize=address

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $@ $^ mymalloc.c && ./testing

clean:
	rm testing
