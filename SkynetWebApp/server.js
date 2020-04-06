// Use Express as app, then set resources directory (static files)
let express = require('express');
let app = express();
app.use(express.static('public'))

// Http server and socket io
const SERVERPORT = 80;
let server = app.listen(SERVERPORT);
let io = require('socket.io')(server);
let MLDataParseRegex = /(?:Type|type)\s*:\s*([^,]+)\s*,\s*(?:Width|width)\s*:\s*(\d+)\s*,\s*(?:Height|height)\s*:\s*(\d+)\s*,\s*[xX]\s*:\s*([\d.]+)\s*,\s*[yY]\s*:\s*([\d.]+)/m

// Set up connections when socket connects
io.on('connection', (socket) => {

  // Acknowlege connection (debug)
  console.log('New connection');

  // Receiving image from Python program
  socket.on('PY_IMG_DATA', (imageData) => {
    socket.broadcast.emit('SRV_IMG_DATA', imageData);
  });

  // Receiving ml result from Python program
  socket.on('PY_ML_RESULT', (result) => {

    // Use regex to parse string data into javascript object and pass that to client
    let MLDataMatch = MLDataParseRegex.exec(result);
    if (MLDataMatch !== null) {
      socket.broadcast.emit('SRV_ML_RESULT', {
        type: MLDataMatch[1],
        w: MLDataMatch[2],
        h: MLDataMatch[3],
        x: MLDataMatch[4],
        y: MLDataMatch[5]
      });
    } else{
              console.log("Result: " + result)
    }
    

  });

  socket.on('PY_ML_CLEAR', ()=> {
    socket.broadcast.emit('ML_CLEAR');
  })

  // Changing settings from webapp
  //gs_threshold, gs_mode, bounding box
  socket.on('WEB2SRV_threshold_val', (value) => {
    console.log("Threshold Value Updated to " + value)
    socket.broadcast.emit('gs_threshold', value);

    // Emit ack back to sender
    socket.emit('gs_threshold_ack', value);
  });

  socket.on('WEB2SRV_detect_obj', (array) => {
    if (array[1] == "1") {
      console.log("Object Detection changed to " + array[0]);
    }
    socket.broadcast.emit('gs_mode', array);
    socket.emit('gs_mode_ack', array[0]);
  });

  // delete if original option not chosen
  // socket.on('WEB2SRV_detect_obj_on', (value) => {
  //   console.log(value + " detection turned on");
  //   socket.broadcast.emit('SRV2RPI_detect_obj_on', value);
  // });

  // socket.on('WEB2SRV_detect_obj_off', (value) => {
  //   console.log(value + " detection turned off");
  //   socket.broadcast.emit('SRV2RPI_detect_obj_off', value);

  // });
});

