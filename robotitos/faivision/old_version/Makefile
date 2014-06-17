SHELL = /bin/sh

CFLAGS = -Wall -O2 -fPIC
LIBFLAGS = -lSDL -lSDL_image -lcurl 
INSTALL_DIR = /usr/local/lib

objects = comm.o faivision.o
     
all: $(objects)
	$(CC) $(CFLAGS) $(LIBFLAGS) -shared -o libfaivision.so $(objects) $(LIBFLAGS)
     
$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean: 
	rm -f *.o libfaivision.so $(objects) core core.*

install:
	cp libfaivision.so $(INSTALL_DIR)

uninstall:
	rm $(INSTALL_DIR)/libfaivision.so

