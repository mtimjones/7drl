CC=gcc 
CFLAGS = -I. -std=c99 -g

DEPS = 7drltypes.h
OBJS = main.o map.o input.o messages.o time.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJS)
	$(CC) -g -o $@ $^ $(CFLAGS) -lncurses

clean:
	rm -f test *.o
