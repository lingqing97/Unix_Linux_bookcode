objects=stdinredir1 stdinredir2 whotofile pipedemo pipedemo2 pipe

all:$(objects)
.PHONY:all clean

clean:
	-rm -f $(objects)

stdinredir1: stdinredir1.c
	cc stdinredir1.c -o stdinredir1 -w

stdinredir2: stdinredir2.c
	cc stdinredir2.c -o stdinredir2 -w

whotofile: whotofile.c
	cc whotofile.c -o whotofile -w

pipedemo: pipedemo.c
	cc pipedemo.c -o pipedemo -w

pipedemo2: pipedemo2.c
	cc pipedemo2.c -o pipedemo2 -w

pipe: pipe.c
	cc pipe.c -o pipe -w