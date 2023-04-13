# CXX Make variable for compiler
CC=g++
# -std=c++11  C/C++ variant to use, e.g. C++ 2011
# -Wall       show the necessary warning files
# -g3         include information for symbolic debugger e.g. gdb 
CCFLAGS=-std=c++11 -Wall -g3 -c -g

# object files
OBJS = print_helpers.o vaddr_tracereader.o level.o map.o TLB.o page_table.o main.o

# Program name
PROGRAM = mmuwithtlb

# The program depends upon its object files
$(PROGRAM) : $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS)

main.o : main.cpp
	$(CC) $(CCFLAGS) main.cpp
	
print_helpers.o : print_helpers.cpp print_helpers.h
	$(CC) $(CCFLAGS) print_helpers.cpp

vaddr_tracereader.o : vaddr_tracereader.cpp vaddr_tracereader.h
	$(CC) $(CCFLAGS) vaddr_tracereader.cpp

level.o : level.cpp level.h
	$(CC) $(CCFLAGS) level.cpp

page_table.o : page_table.cpp page_table.h
	$(CC) $(CCFLAGS) page_table.cpp

map.o : map.cpp map.h
	$(CC) $(CCFLAGS) map.cpp

TLB.o : TLB.cpp TLB.h
	$(CC) $(CCFLAGS) TLB.cpp

# Once things work, people frequently delete their object files.
# If you use "make clean", this will do it for you.
# As we use gnuemacs which leaves auto save files termintating
# with ~, we will delete those as well.
clean :
	rm -f *.o *~ $(PROGRAM)

