all:
	make test && make library

test:
	make -f makefile.test

library:
	make -f makefile.library

install:
	cp libtiresias.a /usr/local/lib/libtiresias.a
	cp include/libtiresias.h /usr/local/include/libtiresias.h

clean:
	rm -f *.o *~ core $(INC)/*~
	rm -f tiresias_tests
	rm -f libtiresias.a
