main.bin: loader.o
	ld --oformat binary loader.o -o main.bin

*.o: *.c
	gcc -nostdlib -fPIC -o $@ -c $<

clean:
	rm *.o main.bin
