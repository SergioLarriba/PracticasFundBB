CC = gcc -g
CFLAGS = -Wall -Wextra -pedantic -ansi
LDLIBS = -lodbc

# recompile if this heder changes
HEADERS = odbc.h

EXE = menu-classic
OBJ = $(EXE).o
all : $(EXE)


%.o: %.c $(HEADERS)
	@echo Compiling $<...
	$(CC) $(CFLAGS) -c -o $@ $<
	
$(EXE) : % : %.o odbc.o

$EXE: $(DEPS) $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(LDLIBS) odbc.o

clean :
	rm -f *.o core $(EXE)


