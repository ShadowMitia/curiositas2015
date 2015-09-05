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
    for (int i = 4; i < WIDTH; i += 100){
            smoke.addSmokePoint(ofPoint(i, 0), ofFloatColor(0.5, 0.1, 0.0));
    }


    // load shader to blackout the hand
	blackHandShader.load("", "shader.frag");

    // debug HUD boolean
	showDebugVideo = false;

	buffer.allocate(WIDTH, HEIGHT, GL_RGBA);

	buffer.begin();
	ofClear(0,0,0,0);
	buffer.end();

}

//--------------------------------------------------------------
void ofApp::update() {

	ofBackground(100, 100, 100);

	kinect.update();
	smoke.update();

    if (kinect.isFrameNew()) {
        updateCvImages();
        cvfilter.update(kinect.getDepthPixels());

        contourFinder.findContours(cvfilter.getThreshImage(), 100, (kinect.width*kinect.height) / 2, 5, false, true);
        collectContours();
    }

	// show framerate in titlebar
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(255, 255, 255);


    buffer.begin();
    // draw the contours, and make the smoke see it as an obstacle
    smoke.begin();
    for (int i = 0; i < contourFinder.blobs.size(); i++){
        polyContour[i].draw();
    }
    smoke.end();

    // draw the smoke
    smoke.draw();

    buffer.end();

    //buffer.draw(0, 0);

    /* contour shader */
    blackHandShader.begin();

    blackHandShader.setUniformTexture("tex", cvfilter.getThreshImage().getTextureReference(), 0);
    blackHandShader.setUniformTexture("fbo", buffer.getTextureReference(), 1);

    //contourFinder.draw(0, 0);
    cvfilter.draw();
    blackHandShader.end();

    // show debug HUD
    if (showDebugVideo){
        drawDebug();
    }
}


//--------------------------------------------------------------

void ofApp::exit() {
	kinect.setCameraTiltAngle(0); // zero the tilt angle on exit
	kinect.close(); // close the kinect
}

//--------------------------------------------------------------
void ofApp::keyPressed (int key) {
    switch (key) {
        case '>':
		case '.':
		    if (showDebugVideo){
                farThreshold ++;
                if (farThreshold > 255) farThreshold = 255;
		    }
			break;
		case '<':
		case ',':
		    if (showDebugVideo){
                farThreshold --;
                if (farThreshold < 0) farThreshold = 0;
		    }
			break;

		case '+':
		case '=':
		    if (showDebugVideo){
                nearThreshold ++;
                if (nearThreshold > 255) nearThreshold = 255;
		    }
			break;

		case '-':
		    if (showDebugVideo){
                nearThreshold --;
                if (nearThreshold < 0) nearThreshold = 0;
		    }
			break;
        case ' ':
            showDebugVideo = !showDebugVideo;
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
    kinect.draw(0, 0, 400, 300);
    // show contours found bw contourFinder
    contourFinder.draw(0, 320);
    // Show debug info
    stringstream ss;
    ss << "Far threshold " << farThreshold << " \nNear Threshold " << nearThreshold << " \nKinect width " << kinect.width << " \nKinect height " << kinect.height;
    ofDrawBitmapString(ss.str(), 0, HEIGHT - 100);
}

void ofApp::updateCvImages() {
	if (kinect.isFrameNew()) {
        colorImg.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
	}
}

void ofApp::collectContours(){
    if (contourFinder.nBlobs > 0) {
        polyContour.clear();
        polyContour.resize(contourFinder.nBlobs);
        for (int i = 0; i < contourFinder.blobs.size(); i++){
            polyContour[i].addVertices(contourFinder.blobs[i].pts);
            polyContour[i].setClosed(true);
        }

    }
}
