test:
	make -f makefile.test

server:
	make -f makefile.server

clean:
	rm -f *.o *~ core $(INC)/*~
	rm -f *.gcno *~ core $(INC)/*~
	rm -f *.gcda *~ core $(INC)/*~
	rm tiresias_tests
	rm tiresias_server
