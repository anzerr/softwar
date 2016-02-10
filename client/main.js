
var a = function () {
    var s = require('net').Socket();
    s.connect(1337, '127.0.0.1');
    s.write('cat\r\n', function(e, r) {
	console.log('send msg', e, r);
    });
    
    s.on('data', function(d) {
	console.log('--', d.toString());
    });

    s.on('connect', function() {
	console.log('connected');
    });
    
    s.on('close', function() {
	console.log('closed');
	setTimeout(a, 5000);
    });

    s.on('error', function(e) {
	console.log('e', e);
    });
};
a();
