src="http://localhost:8080/socket.io/socket.io.js "
window.onload = function(){
    var input = document.getElementById('input');
    var output = document.getElementById('output');

    var socket = io.connect('localhost',{port: 8080});

    socket.on("connect",function(){
        console.log("Connected to the server");
        socket.send("Hello world");
        });
    socket.on('message',function(data) {
        output.innerHTML = '=' + data;
        // socket.send("Hello world");
    });
    socket.on('error', function (data) {
        console.log("error:",data);
    });

    window.sendMessage = function(){
        socket.send(input.value);
    };
}