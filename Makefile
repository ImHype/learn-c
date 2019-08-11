# Trying Features 
helloworld:
	gcc ./src/hello-world/*.c && ./a.out

global:
	gcc ./src/global/*.c && ./a.out

fp1:
	gcc ./src/function-pointer/fp-1.c && ./a.out

fp2:
	gcc ./src/function-pointer/fp-2.c && ./a.out

voidp:
	gcc ./src/voidp/*.c && ./a.out

callback:
	gcc ./src/callback/*.c && ./a.out

fork:
	gcc ./src/process/fork.c && ./a.out

transfer-by-pipe:
	gcc ./src/process/pipe.c && ./a.out

signal:
	gcc ./src/process/signal.c && ./a.out

write:
	gcc ./src/file-descriptor/write.c && ./a.out

read:
	gcc ./src/file-descriptor/read.c && ./a.out

fd:
	gcc ./src/file-descriptor/main.c && ./a.out

pipe-example:
	gcc ./src/pipe/example.c && ./a.out

so: 
	@gcc -fPIC -shared ./src/so/*.c -o libhello.so
	@gcc ./src/so/main.c -L. -lhello

gdb:
	gcc -g ./src/gdb/main.c && ./a.out
