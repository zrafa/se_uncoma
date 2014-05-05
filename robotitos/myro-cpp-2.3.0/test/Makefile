CC=g++
CFLAGS=`myro-cpp-config --cflags`
LIBS=`myro-cpp-config --libs`

BINARIES=test_blob test_camera test_motor video_stream test_camera_fourwindow test_camera_nonblocking

all: $(BINARIES) 

%: %.cpp
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	rm -f *.o core $(BINARIES)
