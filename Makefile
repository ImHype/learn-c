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




assert:
	gcc ./src/assert/*.c && ./a.out

buffer:
	gcc ./src/buffer/*.c && ./a.out

event:
	gcc ./src/event/*.c && ./a.out