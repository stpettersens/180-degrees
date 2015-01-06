#
# Makefile to build the simple Java "VM";
# really just a front end for the ClassLoader.
#

CC = g++

# Use the C++ 14 standard
STDFLAG = -std=c++1y

SOURCE = vm.cpp
TARGET = vm.exe
LFLAGS = -o
INCLUDES = -IC:/Dev/MinGW/include
PLATFORM = $(shell uname -s)

# Don't use Windows, use Linux. You change change this to suit your platform
# e.g. replace Linux with Darwin
ifeq ($(PLATFORM), Linux)
	TARGET = vm
	INCLUDES = -I/usr/include/boost
endif

make:
	$(CC) $(STDFLAG) $(SOURCE) $(LFLAGS) $(TARGET) $(INCLUDES)
	strip $(TARGET)

clean:
	rm -f $(TARGET)
