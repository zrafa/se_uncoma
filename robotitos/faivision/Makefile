SHELL = /bin/sh

CFLAGS = -Wall -O2 -fPIC
LIBFLAGS = -lSDL -lSDL_image -lcurl 
INSTALL_DIR = /usr/local/lib
CPPFLAGS = `pkg-config opencv cvblob --cflags --libs`
# LIBCPPFLAGS = -L/usr/local/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab -lcvblob 
LIBCPPFLAGS = `pkg-config opencv cvblob --cflags --libs`

objects = comm.o faivision.o
objects_cpp = detectar_colores.o
     
all: $(objects) $(objects_cpp)
	# $(CC) $(CFLAGS) $(LIBFLAGS) -shared -o libfaivision.so $(objects_cpp) $(objects) $(LIBFLAGS) $(LIBCPPFLAGS)
	g++ $(CFLAGS) $(LIBFLAGS) -lstdc++ -shared -o libfaivision.so $(objects_cpp) $(objects) $(LIBFLAGS) $(LIBCPPFLAGS)
     
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

