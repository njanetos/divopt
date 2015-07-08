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

$(OUTPUTFILE): divopt.o
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
	g++ -c $(SRC)/divopt.cpp
