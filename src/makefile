# OSX compiler
CC = clang++

# Dwarf compiler
# CC = g++

CXX = $(CC)

# OSX include paths (for MacPorts)
#CFLAGS = -I/opt/local/include -I../include

# OSX include paths (for homebrew, probably)
CFLAGS = -I/usr/local/include -I../include

# Dwarf include paths
# CFLAGS = -I../include # opencv includes are in /usr/include
# CXXFLAGS = $(CFLAGS)

# OSX Library paths (if you use MacPorts)
#LDFLAGS = -L/opt/local/lib

#OSX Library paths (if you use homebrew, probably)
LDFLAGS = -L/usr/local/lib

# Dwarf Library paths
# LDFLAGS = -L/usr/lib/x86_64-linux-gnu # opencv libraries are here

# opencv libraries
LDLIBS = -lopencv_core -lopencv_highgui -lopencv_video -lopencv_videoio -lopencv_imgproc -lopencv_imgcodecs -lopencv_objdetect



BINDIR = ../bin

vid: vidDisplay.o
	$(CC) $^ -o $(BINDIR)/$@ $(LDFLAGS) $(LDLIBS)

imod: imgMod.o
	$(CC) $^ -o $(BINDIR)/$@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f *.o *~ 
