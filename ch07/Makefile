objects=hello1c hello2c hello3c sleep1c sigactdemo ticker_demo bounce1c bounce_a1

all:$(objects)
.PHONY:all clean

clean:
	-rm -f $(objects)

hello1c:hello1c.c
	cc hello1c.c -o hello1c -w -lncurses

hello2c: hello2c.c
	cc hello2c.c -o hello2c -w -lncurses

hello3c:hello3c.c
	cc hello3c.c -o hello3c -w -lncurses

sleep1c:sleep1c.c
	cc sleep1c.c -o sleep1c -w -lncurses

sigactdemo:sigactdemo.c
	cc sigactdemo.c -o sigactdemo -w -lncurses

ticker_demo:ticker_demo.c
	cc ticker_demo.c -o ticker_demo -w -lncurses

bounce1c:bounce1c.c
	cc bounce1c.c -o bounce1c -w -lncurses

bounce_a1:bounce_a1.c
	cc bounce_a1.c -o bounce_a1 -w -lncurses
