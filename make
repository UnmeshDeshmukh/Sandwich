#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = g++
CFLAGS  = -O0 -g3 -Wall -fopenmp -c -fmessage-length=0 -std=c++11 

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: build

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
build:  restaurant inventory 
	$(CC) -o 275-project-2 restaurant.o inventory.o -fopenmp

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
restaurant:  
	$(CC) $(CFLAGS) -o restaurant.o restaurant.cpp 
# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
inventory:  
	$(CC) $(CFLAGS) -o inventory.o inventory.cpp 

# To create the object file scanner.o, we need the source files
# scanner.c and scanner.h:
#

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) build *.o *~