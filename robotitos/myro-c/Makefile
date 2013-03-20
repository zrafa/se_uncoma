###
# MyroC Makefile
#   Authors:  David Cowden
#	      Dilan Ustek	

TARGET := MyroC
VERSION = 1
SUBVERSION = 0
PATCH = 0

# Location to install the MyroC header and object / shared library file to..#
INSTALLPATH = /usr/local
# ------------------------------------------------------------- #

# Location of the Myro-Cpp install on your system ------------- #
MYROINST = /usr/local
# ------------------------------------------------------------- # 

MYROINC = $(MYROINST)/include/Myro-Cpp
MYROLIB = $(MYROINST)/lib

SRC = MyroC.cpp
OBJ = ${SRC:.cpp=.o}
HEAD = ${SRC:.cpp=.h}
SOBJ = ${SRC:.cpp=.so}	
SOBJV := ${SRC:.cpp=.so.$(VERSION)}
SOBJVS := ${SRC:.cpp=.so.$(VERSION).$(SUBVERSION)}
SOBJVSP := ${SRC:.cpp=.so.$(VERSION).$(SUBVERSION).$(PATCH)}
LCSOBJ := ${shell echo $(SOBJ) | tr A-Z a-z}
CPP = g++
CC = gcc
CPPFLAGS = -I$(MYROINC) -L$(MYROLIB) -lmyro-cpp -g

# Standard target:  Compile MyroC as a static library.
${TARGET}: $(SRC)
	$(CPP) $(CPPFLAGS) -c $(SRC) 

# Target/Shared:  Compile MyroC as a shared library.
${TARGET}/shared: $(SRC)
	$(CPP) $(CPPFLAGS) -fPIC -c $(SRC) 
	$(CC) -shared -Wl,-soname,lib$(TARGET).so.$(VERSION).$(SUBVERSION) -o lib$(TARGET).so.$(VERSION).$(SUBVERSION).$(PATCH) $(OBJ) -lc -L$(MYROLIB) -lmyro-cpp 

# Standard install target:  Install the MyroC.o file to INSTALLPATH/lib and
#                           MyroC.h to INSTALLPATH/include/MyroC
.PHONY : install
install: $(TARGET) $(HEAD)
	mkdir -p $(INSTALLPATH)/lib
	mkdir -p $(INSTALLPATH)/include/MyroC
	cp $(OBJ) $(INSTALLPATH)/lib/$(OBJ)
	cp $(HEAD) $(INSTALLPATH)/include/MyroC/$(HEAD)
	rm $(OBJ)

# Shared install target:  Install libMyroC.so.V.S.P to INSTALLPATH/lib and
#                         MyroC.h to INSTALLPATH/include/MyroC
.PHONY : install/shared
install/shared: $(TARGET)/shared $(HEAD)
	mkdir -p $(INSTALLPATH)/lib
	mkdir -p $(INSTALLPATH)/include/MyroC
	cp lib$(SOBJVSP) $(INSTALLPATH)/lib/lib$(SOBJVSP) 
	cp $(HEAD) $(INSTALLPATH)/include/MyroC/$(HEAD)
	ln -sf lib$(SOBJVSP) lib$(SOBJVS)
	ln -sf lib$(SOBJVS) lib$(SOBJ)
	ln -sf lib$(SOBJ) lib$(LCSOBJ) 
	cp -d lib* $(INSTALLPATH)/lib/
	rm $(OBJ) lib$(SOBJ) lib$(SOBJVS) lib$(SOBJVSP) lib$(LCSOBJ)


# Shortcut for TARGET
.PHONY : static
static : ${TARGET}

# Shortcut for TARGET/shared
.PHONY : shared
shared : ${TARGET}/shared

# Touch the header file to bring it up to date:
.PHONY : head
head:
	touch $(HEAD)

# Remove backup files and compiled object library files:
.PHONY : clean
clean:
	rm -f *~ \#* $(OBJ) lib$(SOBJVSP) lib$(SOBJVS) lib$(SOBJ) lib$(LCSOBJ)

