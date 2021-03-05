objects=hello_multi twordcount twordcount2 htbounce1d

all:$(objects)
.PHONY:all clean

clean:
	-rm -f $(objects)

hello_multi:hello_multi.c
	cc hello_multi.c -o hello_multi -w -g -lpthread

twordcount:twordcount.c
	cc twordcount.c -o twordcount -w -g -lpthread

twordcount2:twordcount2
	cc twordcount2.c -o twordcount2 -w -g -lpthread

htbounce1d:htbounce1d.c
	cc htbounce1d.c -o htbounce1d -w  -lncurse -lpthread