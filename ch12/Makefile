objects=demo1 demo1d demo2d websev

all:$(objects)
.PHONY:all clean

clean:
	-rm -f $(objects)

demo1: demo1.c socklib.c
	cc demo1.c socklib.c -o demo1 -w -g

demo1d: demo1d.c socklib.c
	cc demo1d.c socklib.c -o demo1d -w -g

demo2d: demo2d.c socklib.c
	cc demo2d.c socklib.c -o demo2d -w -g

websev:websev.c socklib.c
	cc websev.c socklib.c -o websev -w -g