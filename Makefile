# Trying Features 
helloworld:
	gcc ./c-features/hello-world/*.c && ./a.out

global:
	gcc ./c-features/global/*.c && ./a.out

fp1:
	gcc ./c-features/fp-1/*.c && ./a.out

fp2:
	gcc ./c-features/fp-2/*.c && ./a.out

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
	gcc ./c-features/fd/write.c && ./a.out

read:
	gcc ./c-features/fd/read.c && ./a.out

fd:
	gcc ./c-features/fd/main.c && ./a.out

pipe-example:
	gcc ./c-features/pipe/example.c && ./a.out



# Some wheels
assert:
	gcc ./src/assert/*.c && ./a.out

buffer:
	gcc ./src/buffer/*.c && ./a.out

event:
	gcc ./src/event/*.c && ./a.out

pipe_channel:
	gcc ./src/pipe_channel/*.c && ./a.out