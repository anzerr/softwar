
var a = function () {
    var s = require('net').Socket();
    s.connect(1337, '127.0.0.1');
    s.write('GET http://www.google.com/ HTTP/1.1\n\n');

    s.on('data', function(d){
	console.log(d.toString());
    });

    s.on('close', function() {
	setTimeout(a, 1000);
    });

    s.on('error', function(e) {
	console.log(e);
	setTimeout(a, 1000);
    });
    
    s.end();
};
a();
