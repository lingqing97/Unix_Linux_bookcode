objects=cp1c who1c who2c who_am_i

all: cp1c who1c who2c who_am_i
.PHONY:all,clean

cp1c: cp1c.c
	-cc cp1c.c -o cp1c -w

who1c: who1c.c
	-cc who1c.c -o who1c -w

who2c: who2c.c
	-cc who2c.c -o who2c -w

who_am_i: who_am_i.c
	-cc who_am_i.c -o who_am_i -w

clean:
	-rm -f $(objects)
