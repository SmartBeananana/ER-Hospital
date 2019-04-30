CC          =	gcc

CFLAGS      = -Wall -std=c99 -pedantic -g -lm

test: src/heapImpl.c src/PQImpl.c src/main.c src/patientImpl.c
	$(CC) $(CFLAGS) src/heapImpl.c src/PQImpl.c src/main.c src/patientImpl.c -Iinclude -o bin/testMe

testQ: src/test.c src/testPQueue.c src/PQImpl.c src/heapImpl.c
	$(CC) $(CFLAGS) src/test.c src/testPQueue.c src/PQImpl.c src/heapImpl.c -Iinclude -o bin/testQueue

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm bin/*
