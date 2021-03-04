objects=hello_multi twordcount

all:$(objects)
.PHONY:all clean

clean:
	-rm -f $(objects)

hello_multi:hello_multi.c
	cc hello_multi.c -o hello_multi -w -g -lpthread

twordcount:twordcount.c
	cc twordcount.c -o twordcount -w -g -lpthread