objects=smsh1 smsh2

all:$(objects)
.PHONY:all clean

clean:
	-rm -f $(objects)

smsh1:smsh1.c execute.c splitline.c
	cc smsh1.c execute.c splitline.c -o smsh1 -w


smsh2:smsh2.c process.c controlflow.c  execute.c splitline.c builtin.c varlib.c
	cc smsh2.c  process.c controlflow.c execute.c splitline.c builtin.c varlib.c -o smsh2 -w