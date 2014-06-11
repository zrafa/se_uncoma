SHELL = /bin/sh

CFLAGS = -Wall -O2 -fPIC
LIBFLAGS = -lSDL -lSDL_image -lcurl 
INSTALL_DIR = /usr/local/lib
CPPFLAGS = `pkg-config opencv cvblob --cflags --libs`

objects = comm.o faivision.o
objects_cpp = detectar_colores.o
     
all: $(objects) $(objects_cpp)
	$(CC) $(CFLAGS) $(LIBFLAGS) -shared -o libfaivision.so $(objects) $(objects_cpp) $(LIBFLAGS)
     
$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(objects_cpp): %.o: %.cpp
	g++ -c $(CPPFLAGS) $< -o $@

clean: 
	rm -f *.o libfaivision.so $(objects) $(objects_cpp) core core.*

install:
	cp libfaivision.so $(INSTALL_DIR)

uninstall:
	rm $(INSTALL_DIR)/libfaivision.so

