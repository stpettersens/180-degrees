#
# Makefile to build the simple Java "VM";
# really just a front end for the ClassLoader.
#
CC = g++

# Use the C++ 14 standard
STDFLAG = -std=c++1y

SOURCE = vm.cpp
TARGET = vm
LFLAGS = -o
INCLUDES = -I/usr/include/boost

make:
	$(CC) $(STDFLAG) $(SOURCE) $(LFLAGS) $(TARGET) $(INCLUDES)
	strip $(TARGET)

clean:
	rm -f $(TARGET)
