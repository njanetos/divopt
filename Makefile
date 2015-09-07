# Specify the target file and the install directory
SRC         = src
INC         = include
LIB 				= lib

CLEANEXTS   = o a gcno
CC					= g++
CFLAGS			= -Wall -fexceptions -g -I$(INC) -I/usr/include -fprofile-arcs -ftest-coverage
CFLAGS_BUILD= -Wall -fexceptions -g -I$(INC) -I/usr/include
LIBS				= -L$(LIB) -lgcov -larmadillo -lMvtnorm

_DEPS = mvtnorm.h c_util.h c_rand_var_norm.h c_rand_var.h c_logger.h catch.hpp c_constraint.h
DEPS = $(patsubst %,$(INC)/%,$(_DEPS))

_OBJ_LIB = c_util.o c_rand_var_norm.o c_rand_var.o c_logger.o c_constraint.o
OBJ_LIB = $(patsubst %,%,$(_OBJ_LIB))

# Default target
.PHONY: all
all: divopt

divopt: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: library
library: divopt.a

divopt.a: $(OBJ_LIB)
	ar ru $@ $^
	ranlib $@

.PHONY: clean
clean:
	rm -f *.o *~ core $(INC)/*~
	rm -f *.gcno *~ core $(INC)/*~
	rm -f *.gcda *~ core $(INC)/*~
	rm divopt

# Dependencies

%.o: $(SRC)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(LIBS)
