objects=exec1c psh1c forkdemo1c forkdemo2c waitdemo1c psh2c

all:$(objects)
.PHONY:all clean

clean:
	-rm -f $(objects)

exec1c: exec1c.c
	cc exec1c.c -o exec1c -w

psh1c:psh1c.c
	cc psh1c.c -o psh1c -w

forkdemo1c:forkdemo1c.c
	cc forkdemo1c.c -o forkdemo1c -w

forkdemo2c:forkdemo2c.c
	cc forkdemo2c.c -o forkdemo2c -w

waitdemo1c:waitdemo1c.c
	cc waitdemo1c.c -o waitdemo1c -w

psh2c:psh2c.c
	cc psh2c.c -o psh2c -w