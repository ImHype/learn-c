all:
	@$(MAKE) main_process.o;

libtask_queue.so: task_queue.c
	@gcc task_queue.c -shared -fPIC -o $@

main_process.o: libtask_queue.so example.c
	@gcc ./example.c -ltask_queue -L . -o main_process.o