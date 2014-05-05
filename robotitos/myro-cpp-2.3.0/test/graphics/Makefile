CC=g++
CFLAGS=`myro-cpp-config --cflags`
LIBS=`myro-cpp-config --libs`

BINARIES=circles robot_joystick robot_senses cascading_pictures

all: $(BINARIES) 

%: %.cpp
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	rm -f *.o core $(BINARIES)
