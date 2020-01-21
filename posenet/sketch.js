let video;
let posenet;
let pose;

function setup() {
  createCanvas(640, 480);
  video = createCapture(VIDEO);
  video.hide();
  
  posenet = ml5.poseNet(video, modelLoadCallback);
  posenet.on('pose', poseUpdateCallback);
}

function poseUpdateCallback(poses) {
  if (poses.length > 0) {
    pose = poses[0].pose;
    // console.log(pose);
  }
}

function modelLoadCallback() {
  console.log('model ready');
}

function drawSkele(p) {
  if (p !== undefined) {
    strokeWeight(10);
    point(p.nose.x, p.nose.y);
    point(p.leftEye.x, p.leftEye.y);
    point(p.rightEye.x, p.rightEye.y);
    point(p.leftEar.x, p.leftEar.y);
    point(p.rightEar.x, p.rightEar.y);
    
    point(p.leftShoulder.x, p.leftShoulder.y);
    point(p.rightShoulder.x, p.rightShoulder.y);
    point(p.leftElbow.x, p.leftElbow.y);
    point(p.rightElbow.x, p.rightElbow.y);
    point(p.leftWrist.x, p.leftWrist.y);
    point(p.rightWrist.x, p.rightWrist.y);
    point(p.leftHip.x, p.leftHip.y);
    point(p.rightHip.x, p.rightHip.y);
    point(p.leftKnee.x, p.leftKnee.y);
    point(p.rightKnee.x, p.rightKnee.y);
    point(p.leftAnkle.x, p.leftAnkle.y);
    point(p.rightAnkle.x, p.rightAnkle.y);
    
    strokeWeight(5);
    line(p.nose.x, p.nose.y, p.rightEye.x, p.rightEye.y);
    line(p.nose.x, p.nose.y, p.leftEye.x, p.leftEye.y);
    line(p.rightEar.x, p.rightEar.y, p.rightEye.x, p.rightEye.y);
    line(p.leftEar.x, p.leftEar.y, p.leftEye.x, p.leftEye.y);
    
    line(p.leftShoulder.x, p.leftShoulder.y, p.rightShoulder.x, p.rightShoulder.y);
    line(p.leftShoulder.x, p.leftShoulder.y, p.leftElbow.x, p.leftElbow.y);
    line(p.leftElbow.x, p.leftElbow.y, p.leftWrist.x, p.leftWrist.y);
    line(p.rightShoulder.x, p.rightShoulder.y, p.rightElbow.x, p.rightElbow.y);
    line(p.rightElbow.x, p.rightElbow.y, p.rightWrist.x, p.rightWrist.y);
    line(p.leftShoulder.x, p.leftShoulder.y, p.leftHip.x, p.leftHip.y);
    line(p.rightShoulder.x, p.rightShoulder.y, p.rightHip.x, p.rightHip.y);
    line(p.leftKnee.x, p.leftKnee.y, p.leftHip.x, p.leftHip.y);
    line(p.rightKnee.x, p.rightKnee.y, p.rightHip.x, p.rightHip.y);
    line(p.leftKnee.x, p.leftKnee.y, p.leftAnkle.x, p.leftAnkle.y);     
    line(p.rightKnee.x, p.rightKnee.y, p.rightAnkle.x, p.rightAnkle.y);
    
  }
}

function draw() {
  
  if (pose === undefined)
    return;
  
  // get transformation
  push();
  
  // translate(width/2, height/2);
  
  // next scale the video
  // let dx = pose.leftEye.x - pose.rightEye.x;
  // let dy = pose.leftEye.y - pose.rightEye.y;
  // let dd = dx * dx + dy * dy;
  // let s = map(dd, 30000, 5000, 0.8, 2.0)
  // scale(s);
  
  // first get the midpoint between eyes and fix it to the middle of the screen
  let mx = 0.5 * (pose.leftEye.x + pose.rightEye.x);
  let my = 0.5 * (pose.leftEye.y + pose.rightEye.y);
  translate(width/2 - mx * s, height/2 - my * s);
  
  // next, get the rotation of eyes
  let dangle = atan2(pose.leftEye.y - pose.rightEye.y, pose.leftEye.x, pose.rightEye.x);
  rotate(dangle);
  // console.log(dd);
  
  image(video, 0, 0);
  
  pop();
  
  // drawSkele(pose);
}