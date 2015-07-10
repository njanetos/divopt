# Specify extensions of files to delete when cleaning
CLEANEXTS   = o a

# Specify the target file and the install directory
OUTPUTFILE  = divopt.a
HEADER		  = divopt.h
INSTALLDIR  = /usr/lib/divopt

SRC         = src
INC         = include

# Default target
.PHONY: all
all: $(OUTPUTFILE)

$(OUTPUTFILE): divopt.o c_util.o c_rand_var_norm.o c_rand_var.o c_logger.o
	ar ru $@ $^
	ranlib $@

.PHONY: install
install:
	mkdir -p $(INSTALLDIR)
	cp -p $(OUTPUTFILE) $(INSTALLDIR)
	cp -p $(INC)/$(HEADER) $(INSTALLDIR)

.PHONY: clean
clean:
	for file in $(CLEANEXTS); do rm -f *.$$file; done

# Indicate dependencies of .ccp files on .hpp files
divopt.o:
	g++ -c -I$(INC) $(SRC)/divopt.cpp

c_util.o:
	g++ -c -I$(INC) $(SRC)/c_util.cpp

c_rand_var_norm.o:
	g++ -c -I$(INC) $(SRC)/c_rand_var_norm.cpp

c_rand_var.o:
	g++ -c -I$(INC) $(SRC)/c_rand_var.cpp

c_logger.o:
	g++ -c -I$(INC) $(SRC)/c_logger.cpp
