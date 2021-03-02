objects=tinybc timeserv timeclnt rls rlsd

all:$(objects)
.PHONY:all clean

clean:
	-rm -f $(objects)

tinybc: tinybc.c
	cc tinybc.c -o tinybc -w

timeserv: timeserv.c
	cc timeserv.c -o timeserv -w

timeclnt: timeclnt.c
	cc timeclnt.c -o timeclnt -w

rls: rls.c
	cc rls.c -o rls -w -g

rlsd: rlsd.c
	cc rlsd.c -o rlsd -w -g
