FLAGS = -Wall -g -std=gnu99

all : lexer

lexer: lexer.o
	gcc ${FLAGS} -o $@ $^

lexer.o: lexer.h

%.o : %.c
	gcc ${FLAGS} -c $<

tests:
	gcc ${FLAGS} -o test1 test1.c

clean:
	-rm *.o lexer
	-rm test1
