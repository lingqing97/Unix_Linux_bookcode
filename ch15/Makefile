objects=selectdemo shm_ts shm_tc file_ts file_tc shm_ts2 shm_tc2

all:$(objects)
.PHONY:all clean

clean:
	-rm -f $(objects)

selectdemo:selectdemo.c
	cc selectdemo.c -o selectdemo -w -g

shm_ts:shm_ts.c
	cc shm_ts.c -o shm_ts -w -g

shm_tc:shm_tc.c
	cc shm_tc.c -o shm_tc -w -g

file_ts:file_ts.c
	cc file_ts.c -o file_ts -w -g

file_tc:file_tc.c
	cc file_tc.c -o file_tc -w -g

shm_ts2:shm_ts2
	cc shm_ts2.c -o shm_ts2 -w -g

shm_tc2:shm_tc2
	cc shm_tc2.c -o shm_tc2 -w -g