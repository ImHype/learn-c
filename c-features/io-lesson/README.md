# IO-LESSON

## The problem

In last lesson, we create a program which could process the tcp connection by the socket.

Now we use `ab` to measure the performance.

The results is:
```console
Requests per second:    475.93 [#/sec] (mean)
Time per request:       2.101 [ms] (mean)
Time per request:       2.101 [ms] (mean, across all concurrent requests)
Transfer rate:          102.72 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    1   1.0      1      33
Processing:     0    0   0.8      0      48
Waiting:        0    0   0.8      0      48
Total:          0    1   1.3      1      53
```

It's too slow.

