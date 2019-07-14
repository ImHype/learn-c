## PIPE

Using `pipe` we could tranfer the data from parent process to child process, or from the child process to the parent process. But there are some bad points:

* The pipe the `half-duplex` data flowing. It means that you only could flow the data from the parent to the child, or from the child to the parent. But we have solution for it. We could create two pipes to flow two directions.
* The data flowing only could be between the parent and child. If you need build the communication with the any two process. You need use the `named-pipe`.


### some cases
#### pipe.c

I built two pipes and forked two processes from the main function. 

I use the pipe to help us to flow the data from child to parent.

And the result looks fine.
```console
> from child process 1
> from child process 2
> from child process 1
> from child process 2
> from child process 1
> from child process 2
```

#### pipe-pending.c

But if one pipe's write is slow than other one. The blocking may be appeared.

Like the `pipe-pending.c`.

```
> from child process 1
> read child1 message pending 0s
> from child process 2
> read child2 message pending 0s
> from child process 1
> read child1 message pending 1s
> from child process 2
> read child2 message pending 2s
> from child process 1
> read child1 message pending 0s
> from child process 2
> read child2 message pending 3s
```


So we need think some solutions to make the child2 reciever don't pending the child1 reciever.

#### pipe-nonblocing.c
Also we could use the non-blocking `API` to read the message

```console
> from child process 1
> read child1 message pending 0s
> from child process 1
> read child1 message pending 0s
> from child process 2
> read child2 message pending 0s
> from child process 1
> read child1 message pending 0s
> from child process 2
> read child2 message pending 0s
> from child process 2
> read child2 message pending 0s
```

But the cpu will be busy.


We could add a `sleep(1)` in the loop.
```c
    while(1) {
        ...
        sleep(1); // 让出 CPU，避免CPU长时间空转
    }
```

But it may be not realtime.