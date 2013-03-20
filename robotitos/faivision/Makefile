SHELL = /bin/sh

CFLAGS = -Wall -O2
LIBFLAGS = -lSDL -lSDL_image -lcurl 

objects = comm.o faivision.o
     
all: $(objects)
	$(CC) $(CFLAGS) $(LIBFLAGS) -shared -o libfaivision.so $(objects)
     
$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean: 
	rm -f *.o libfaivision.so $(objects) core core.*


