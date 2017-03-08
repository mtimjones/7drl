CC=gcc 
CFLAGS = -I. -std=c99 -g

DEPS = 7drltypes.h
OBJS = main.o map.o messages.o time.o player.o ces.o systems.o misc.o astar.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

7drl: $(OBJS)
	$(CC) -g -o $@ $^ $(CFLAGS) -lncurses -lm

clean:
	rm -f 7drl *.o
