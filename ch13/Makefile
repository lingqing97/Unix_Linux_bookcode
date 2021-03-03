objects=dgrec dgsend

all: $(objects)
.PHONY:all clean

clean:
	-rm -f $(objects)

dgrec: dgrec.c dgram.c
	cc dgrec.c dgram.c -o dgrec -w -g

dgsend: dgsend.c dgram.c
	cc dgsend.c dgram.c -o dgsend -w -g