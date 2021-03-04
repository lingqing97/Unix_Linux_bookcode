objects=dgrec dgsend lclnt1 lserv1 logfiled logfilec

all: $(objects)
.PHONY:all clean

clean:
	-rm -f $(objects)

dgrec: dgrec.c dgram.c
	cc dgrec.c dgram.c -o dgrec -w -g

dgsend: dgsend.c dgram.c
	cc dgsend.c dgram.c -o dgsend -w -g

lclnt1: lclnt1.c lclnt_funcs1.c dgram.c
	cc lclnt1.c lclnt_funcs1.c dgram.c -o lclnt1 -w -g

lserv1: lserv1.c lserv_funcs1.c dgram.c
	cc lserv1.c lserv_funcs1.c dgram.c -o lserv1 -w -g

logfiled:logfiled.c
	cc logfiled.c -o logfiled -w -g

logfilec:logfilec.c
	cc logfilec.c -o logfilec -w -g
