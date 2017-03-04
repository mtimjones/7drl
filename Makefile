CC=gcc
CFLAGS = -I.

DEPS = 
OBJS = main.o map.o input.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJS)
	$(CC) -g -o $@ $^ $(CFLAGS) -lncurses

clean:
	rm -f test *.o
