# Turner Trowbridge
# CS480 Section 1 Spring 2023
# Assignment 4

# CXX Make variable for compiler
CC=g++
# -std=c++11  C/C++ variant to use, e.g. C++ 2011
# -Wall       show the necessary warning files
# -g3         include information for symbolic debugger e.g. gdb 
CCFLAGS=-std=c++11 -Wall -g3 -c -g

# object files
OBJS = main.o

# Program name
PROGRAM = cryptoexc

# The program depends upon its object files
$(PROGRAM) : $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS)

main.o : main.cpp
	$(CC) $(CCFLAGS) main.cpp

# Once things work, people frequently delete their object files.
# If you use "make clean", this will do it for you.
# As we use gnuemacs which leaves auto save files terminating
# with ~, we will delete those as well.
clean :
	rm -f *.o *~ $(PROGRAM)

