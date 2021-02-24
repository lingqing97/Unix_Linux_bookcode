objects=set_fcntl stty

all: $(objects)
.PHONY:all clean

clean:
	-rm -f $(objects)

set_fcntl: set_fcntl.c
	cc set_fcntl.c -o set_fcntl -w

stty: stty.c
	cc stty.c -o stty -w
