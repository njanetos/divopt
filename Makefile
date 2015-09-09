# Specify the target file and the install directory
SRC         = src
INC         = include
LIB 				= lib

CLEANEXTS   = o a gcno
CC					= g++
CFLAGS			= -Wall -fexceptions -g -I$(INC) -I/usr/include -fprofile-arcs -ftest-coverage -std=c++11
CFLAGS_BUILD= -Wall -fexceptions -g -I$(INC) -I/usr/include
LIBS				= -L$(LIB) -lgcov -larmadillo -lMvtnorm lib/libnlopt.a

_DEPS = mvtnorm.h utils.h c_rand_var_norm.h c_rand_var.h c_logger.h catch.hpp common.h
DEPS = $(patsubst %,$(INC)/%,$(_DEPS))

_OBJ = utils.o c_rand_var_norm.o c_rand_var.o c_logger.o c_tests.o
OBJ = $(patsubst %,%,$(_OBJ))

_OBJ_LIB = utils.o c_rand_var_norm.o c_rand_var.o c_logger.o
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
