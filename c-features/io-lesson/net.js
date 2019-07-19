const net = require('net');
const CRLF = '\r\n';


const server = net.createServer((socket) => {
    socket.on('data', (buf) => {
        console.log(buf.toString());
        const status = 200;
        const header = {
            'Content-Type': 'text/html;charset=utf-8'
        };
        const str = Object.keys(header).map((headerKey) => {
            return `${headerKey}: ${header[headerKey]}`
        }).join(CRLF);
        const headers = "HTTP/1.1 200 OK\r\nContent-Type: text/html;charset=utf-8\r\n\r\n<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\" /><title>Document</title></head><body><p>this is http response</p></body></html>"

        socket.write(
            headers + ``
        );

        socket.end();
    });
});


server.listen(9999);