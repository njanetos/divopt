all:
	make test && make library

test:
	make -f makefile.test

library:
	make -f makefile.library

clean:
	rm -f *.o *~ core $(INC)/*~
	rm -f tiresias_tests
	rm -f libtiresias.a
