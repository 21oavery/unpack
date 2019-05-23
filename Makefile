CC=gcc
CFLAGS = -O3 -nostdlib -fPIC

main.bin: loader.o
	ld --oformat binary loader.o -o main.bin

*.o: *.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm *.o main.bin
