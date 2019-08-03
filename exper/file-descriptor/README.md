# FD


File Descriptor


likes the `API` in Javascript:

### 1. Write API

```js
fs.write(fd, some_buffer)
```


### 2. Process API
```js
child_process.spawn({
    // stdio: 'ipc'
    stdio: [0, 1, 2]
})
```

if use the `IPC`, current Process will create pipe new Channels.