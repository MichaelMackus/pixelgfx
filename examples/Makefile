CFLAGS = -O2
LIBFLAGS = -lSDL2 -lGL -L../ -lpixelgfx

test: test.c
	gcc test.c -o test -I../ $(CFLAGS) $(LIBFLAGS)

clean:
	rm test

