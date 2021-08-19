PROGRAM = libpixelgfx.a
OBJS = gfx.o sdl.o
CFLAGS = -O2
LIBFLAGS = -lSDL2 -lGL

$(PROGRAM): $(OBJS)
	ar rcs $(PROGRAM) $(OBJS)

%.o: %.c
	gcc -o $@ $(CFLAGS) -c $<

clean:
	rm *.o
	rm $(PROGRAM)
	make -C examples clean
