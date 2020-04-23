// Type "Hello World" then press enter.
var robot = require("robotjs");
const {exec} = require('child_process');

function pullZoom() {
  exec('/home/mamacker/tools/ZoomAuto/pullforward.sh', (err, stdout, stderr) => {
    if (err) {
      //some err occurred
      console.error(err)
    } else {
     // the *entire* stdout and stderr (buffered)
     console.log(`stdout: ${stdout}`);
     console.log(`stderr: ${stderr}`);
    }
  });
}

const express = require('express')
const app = express()
const port = 3000

app.get('/', (req, res) => {
  res.sendfile("index.html");
})

app.get('/aud', (req, res) => {
  pullZoom();
  res.send('altA');
  console.log("Audio");
  // Press enter.
  robot.keyTap("a", "alt");
  robot.keyTap("d", "control");
})

app.get('/cam', (req, res) => {
  pullZoom();
  res.send('altV');

  console.log("Camera");
  // Press enter.
  robot.keyTap("v", "alt");
  robot.keyTap("e", "control");
})

let lastPress = new Date().getTime();
app.get('/hang', (req, res) => {
  pullZoom();
  res.send('altq-enter');
  console.log("Hangup");
  let curPress = new Date().getTime();

  if (curPress - lastPress > 10000) {
    // Press enter.
    robot.keyTap("q", "alt");
    robot.keyTap("enter");
  } else {
    // Press enter.
    robot.keyTap("w", "control");
  }

  lastPress = curPress;
})

app.listen(port, () => console.log(`Example app listening at http://localhost:${port}`))
