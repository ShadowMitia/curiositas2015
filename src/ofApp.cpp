#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);

	camWidth = kinect.width;
	camHeight = kinect.height;

	// enable depth->video image calibration
	kinect.setRegistration(true);

	kinect.init();
	//kinect.init(true); // shows infrared instead of RGB video image
	//kinect.init(false, false); // disable video image (faster fps)

	kinect.open();		// opens first available kinect
	//kinect.open(1);	// open a kinect by id, starting with 0 (sorted by serial # lexicographically))
	//kinect.open("A00362A08602047A");	// open a kinect using it's unique serial #

	// print the intrinsic IR sensor values
	if(kinect.isConnected()) {
		ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
		ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
		ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
		ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
	}

	colorImg.allocate(kinect.width, kinect.height);
	depthImage.allocate(kinect.width, kinect.height);

    fluid.allocate(WIDTH, HEIGHT, 0.5);

    fluid.dissipation = 0.99;
    fluid.velocityDissipation = 0.99;

    fluid.setGravity(ofVec2f(0.0,0.0));

    /*
    fluid.begin();
    ofSetColor(0,0);
    ofSetColor(255);
    ofCircle(WIDTH*0.5, HEIGHT*0.35, 40);
    fluid.end();
    */

    fluid.addConstantForce(ofPoint(WIDTH / 2, 0), ofPoint(0,2), ofFloatColor(0.5,0.1,0.0), 10.f);

	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofBackground(100, 100, 100);



	kinect.update();

	if (kinect.isFrameNew()){
        colorImg.setFromPixels(kinect.getPixels(), camWidth, camHeight);
        depthImage.setFromPixels(kinect.getDepthPixels(), camWidth, camHeight);
		depthImage.threshold(threshold);
		contourFinder.findContours(depthImage, 50, (camWidth*camHeight), 5, false, true);
	}

    if (contourFinder.nBlobs > 0) {
        fluid.begin();
        ofSetColor(0,0);
        ofSetColor(255);
        //ofCircle(WIDTH*0.5, HEIGHT*0.35, 40);
        /*
        ofRectangle rectBlob = contourFinder.blobs[0].boundingRect;
        ofRect(rectBlob);
        */
        polyContour.clear();
        polyContour.resize(contourFinder.nBlobs);
        for (int i = 0; i < contourFinder.blobs.size(); i++){
            polyContour[i].addVertices(contourFinder.blobs[i].pts);
            polyContour[i].draw();
        }
        fluid.end();
        fluid.setUseObstacles(true);
    }


	fluid.update();

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw() {
    fluid.draw();
    colorImg.draw(0, 0, 400, 300);
    contourFinder.draw(10, 320, 400, 300);

    //
}


//--------------------------------------------------------------
void ofApp::exit() {
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();
}

//--------------------------------------------------------------
void ofApp::keyPressed (int key) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{}
