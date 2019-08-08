# Trying Features 
helloworld:
	gcc ./c-features/hello-world/*.c && ./a.out

global:
	gcc ./c-features/global/*.c && ./a.out

fp1:
	gcc ./c-features/function-pointer/fp-1.c && ./a.out

fp2:
	gcc ./c-features/function-pointer/fp-2.c && ./a.out

voidp:
	gcc ./c-features/voidp/*.c && ./a.out

callback:
	gcc ./c-features/callback/*.c && ./a.out

fork:
	gcc ./c-features/process/fork.c && ./a.out

transfer-by-pipe:
	gcc ./c-features/process/pipe.c && ./a.out

signal:
	gcc ./c-features/process/signal.c && ./a.out

write:
	gcc ./c-features/file-descriptor/write.c && ./a.out

read:
	gcc ./c-features/file-descriptor/read.c && ./a.out

fd:
	gcc ./c-features/file-descriptor/main.c && ./a.out

pipe-example:
	gcc ./c-features/pipe/example.c && ./a.out

so: 
	@gcc -fPIC -shared ./c-features/so/*.c -o libhello.so
	@gcc ./c-features/so/main.c -L. -lhello

gdb:
	gcc -g ./c-features/gdb/main.c && ./a.out

# Some wheels
assert:
	@$(MAKE) assert.o && ./assert.o

buffer:
	@$(MAKE) buffer.o && ./buffer.o

event:
	@gcc ./src/event/*.c ./src/hash_map/hash_map.c ./src/linked-list/linked-list.c -o event.o;./event.o

pipe_channel:
	$(MAKE) pipe_channel.o && ./pipe_channel.o

test-top-k:
	@gcc src/top-k/top-k.c src/top-k/test.c ./src/heap/heap.c -o top-k.o;./top-k.o; rm -rf top-k.o;

test-heap_sorting:
	@gcc src/heap_sorting/heap_sorting.c src/heap/heap.c src/heap_sorting/test.c -o heap_sorting.o;./heap_sorting.o; rm -rf heap_sorting.o;
# %.o:src/%
# 	$(CC) ./$</*.c -o $@