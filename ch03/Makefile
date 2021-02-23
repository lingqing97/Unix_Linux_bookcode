objects=ls1c ls2c

all: $(objects)
.PHONY:all clean

ls1c: ls1c.c
	cc ls1c.c -o ls1c -w

ls2c: ls2c.c
	cc ls2c.c -o ls2c -w

clean:
	rm -f $(objects)