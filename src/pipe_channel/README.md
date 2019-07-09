## pipe_channel

It's sp difficult to use the `PIPE` in C.

So I create this SDK to use it in simple way.

### steps
#### 1. create the pipe_channel
```c
pipe_channel_t * pipe_channel = fork_with_pipe_channel();
```
#### 2. then you could transfer message by the `pipe_channel`:
* int read_pipe_channel(pipe_channel_t*, char *, int);
* void write_pipe_channel(pipe_channel_t*, char *, int);
* void end_pipe_channel(pipe_channel_t*);
* char *read_until_end(pipe_channel_t *);


### showcase
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "pipe_channel.h"


int main(void)
{
    pipe_channel_t * pipe_channel = fork_with_pipe_channel();
    pid_tt pid = *pipe_channel->pid;

    if (pid == 0) {
        char * buffer = read_until_end(pipe_channel);
        printf("message from child:\n\n%s", buffer);

        char new_buffer[4][100] = {"Hello Parent\n", "I'm Child Process\n", "Here is my message to you:\n", "I want to exit(0)\n"};
        for (int i = 0; i < 4; i++)
        {
            write_pipe_channel(pipe_channel, new_buffer[i], strlen(new_buffer[i]));
        }
        end_pipe_channel(pipe_channel);
        close_pipe_channel(pipe_channel);
        exit(0);
    } else if (pid > 0)
    {
        char buffer[4][100] = {"Hello Child\n", "I'm Parent Process\n", "Here is my message to you:\n", "Keep down and carry on\n"};

        for (int i = 0; i < 4; i++)
        {
            write_pipe_channel(pipe_channel, buffer[i], strlen(buffer[i]));
        }

        end_pipe_channel(pipe_channel);
        wait(NULL);

        char * res = read_until_end(pipe_channel);

        printf("\nmessage from parent:\n\n%s", res);

        close_pipe_channel(pipe_channel);

        exit(0);
    }

    return 0;
}
```

#### the output
```bash
gcc ./src/pipe_channel/*.c && ./a.out
message from child:

Hello Child
I'm Parent Process
Here is my message to you:
Keep down and carry on

message from parent:

Hello Parent
I'm Child Process
Here is my message to you:
I want to exit(0)
```
