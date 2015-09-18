#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
  ofEnableAlphaBlending();
  //ofSetLogLevel(OF_LOG_VERBOSE);

  // call setup methods
  setupKinect();
  setupOpenCv();
  cvfilter.setup(kinect.width, kinect.height, WIDTH, HEIGHT);
  //cvfilter.startThread();

  smoke.setup(WIDTH, HEIGHT);
  /*
    for (int i = 4; i < WIDTH; i += 100){
    smoke.addSmokePoint(ofPoint(i, 0), ofFloatColor(0.5, 0.1, 0.0));
    }
  */
  for (int i = 50; i < HEIGHT; i += 100){
    smoke.addSmokePoint(ofPoint(0, i), ofFloatColor(0.5, 0.1, 0.0));
  }


  // debug HUD boolean
  showDebugVideo = false;

  //kinect.setCameraTiltAngle(9.0);
  //kinect.setCameraTiltAngle(-8.0);
  kinect.setCameraTiltAngle(0.0);

  
  oscSender.setup("localhost", 2000);

}

//--------------------------------------------------------------
void ofApp::update() {

  ofBackground(100, 100, 100);

  kinect.update();
  smoke.update();

  if (kinect.isFrameNew()) {
    updateCvImages();
    cvfilter.update(kinect.getDepthPixels());

    contourFinder.findContours(cvfilter.getThreshImage(), 500, (kinect.width*kinect.height) / 2, 5, false, true);
    contoursManager.processContours(contourFinder.blobs);
	
    contoursManager.collectContours();

    colorImg.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
  }

  // draw the contours, and make the smoke see it as an obstacle
  smoke.begin();

  ofPushMatrix();

  ofScale(WIDTH / (float)kinect.width, HEIGHT / (float)kinect.height);

  contourMesh.draw();

  ofPopMatrix();

  smoke.end();

  // show framerate in titlebar
  ofSetWindowTitle(ofToString(ofGetFrameRate()));


  sendOsc();
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofBackground(0, 0, 0);

  // draw the smoke
  //smoke.draw();

  ofPushMatrix();
  ofSetColor(0);

  ofScale(WIDTH / (float)kinect.width, HEIGHT / (float)kinect.height);

  contourMesh.draw();

  ofSetColor(255);
  contourMesh.drawVertices();

  ofSetColor(255, 0, 0);
  
  for (int i = 0; i < contoursManager.centroids.size(); i++) {
    //ofSetColor((int)ofRandom(0, 256), (int)ofRandom(0, 256), (int)ofRandom(0, 256));
    int tempX = contoursManager.centroids[i].x;
    int tempY = contoursManager.centroids[i].y;
    ofCircle(tempX, tempY, 5);
    stringstream ss;
    ss << contoursManager.contourInfos[i].tag << endl;
    ss << ofGetElapsedTimef() - contoursManager.contourInfos[i].startTime;
    ofDrawBitmapStringHighlight(ss.str(), tempX, tempY);

  }

  ofPopMatrix();

  // show debug HUD
  if (showDebugVideo){
    drawDebug();
  }

  angle = 0;
}


//--------------------------------------------------------------

void ofApp::exit() {
  kinect.setCameraTiltAngle(0); // zero the tilt angle on exit
  kinect.close(); // close the kinect
}

//--------------------------------------------------------------
void ofApp::keyPressed (int key) {
  int tempF = cvfilter.getFarThreshold();
  int tempN = cvfilter.getNearThreshold();
  switch (key) {
  case '>':
  case '.':
    if (showDebugVideo){
      cvfilter.setFarThreshold(tempF + 1);
      if (cvfilter.getFarThreshold() > 255) cvfilter.setFarThreshold(255);
    }
    break;
  case '<':
  case ',':
    if (showDebugVideo){
      cvfilter.setFarThreshold(tempF - 1);
      if (cvfilter.getFarThreshold() < 0) cvfilter.setFarThreshold(0);
    }
    break;

  case '+':
  case '=':
    if (showDebugVideo){
      cvfilter.setNearThreshold(tempN + 1);
      if (cvfilter.getNearThreshold() > 255) cvfilter.setNearThreshold(255);
    }
    break;

  case '-':
    if (showDebugVideo){
      cvfilter.setNearThreshold(tempN - 1);
      if (cvfilter.getNearThreshold() < 0) cvfilter.setNearThreshold(0);
    }
    break;
  case ' ':
    showDebugVideo = !showDebugVideo;
    break;
  case 'p':
    angle++;
    if (angle < 45) angle = 0;
    break;
  case 'o':
    break;
  }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{}

//-------------------------------contourFinder.findContours(grayImage, 100, (kinect.width*kinect.height), 5, false, true);-------------------------------
void ofApp::windowResized(int w, int h)
{}

void ofApp::setupKinect() {

  // calibrates the depth image with the rgb image
  kinect.setRegistration(true);

  // init kinect and open the first one found
  kinect.init();
  kinect.open();

  // make sure the kinect is horizontal
  kinect.setCameraTiltAngle(0);


}

void ofApp::setupOpenCv() {
  // allocates the rgb image holder for the kinect feed
  colorImg.allocate(kinect.width, kinect.height);
}


void ofApp::drawDebug() {
  // show rgb feed
  kinect.draw(0, 0);
  // show contours found bw contourFinder
  contourFinder.draw(0, 0, 400, 300);
  // Show debug info
  stringstream ss;
  ss << "Far threshold " << cvfilter.getFarThreshold() << " \nNear Threshold " << cvfilter.getNearThreshold() << " \nKinect width " << kinect.width << " \nKinect height " << kinect.height;
  ofDrawBitmapString(ss.str(), 0, HEIGHT - 100);
}

void ofApp::updateCvImages() {
  if (kinect.isFrameNew()) {
    colorImg.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
  }
}

// void ofApp::collectContours(){

//     if (contourFinder.nBlobs > 0) {
//         polyContour.clear();
//         polyContour.resize(contourFinder.nBlobs);
//         for (int i = 0; i < contourFinder.blobs.size(); i++){
//             polyContour[i].addVertices(contourFinder.blobs[i].pts);
//             polyContour[i].setClosed(true);
//         }
//     }

//     tess.tessellateToMesh(polyContour, OF_POLY_WINDING_POSITIVE, contourMesh);

// }

void ofApp::sendOsc() {

  ofxOscMessage oscMessage;
  int test = (int)ofRandom(0, 127);
  stringstream ss;
  ss << test;
  oscMessage.addStringArg(ss.str());
  oscSender.sendMessage(oscMessage);

}
