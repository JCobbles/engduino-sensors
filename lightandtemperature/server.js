var express = require('express');
var app = express();

app.get('/', function(req, res) {
  res.send('Hello Jacob!');
});

app.use(express.static('public'));


app.listen(process.env.port || 3000, function() {
  console.log('app listening');
});
