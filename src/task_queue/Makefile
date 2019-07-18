all:
	@$(MAKE) main_process.o;

libtask_queue.so:
	@gcc task_queue.c -shared -fPIC -o $@

main_process.o: libtask_queue.so
	@gcc ./example.c -ltask_queue -L . -o main_process.o