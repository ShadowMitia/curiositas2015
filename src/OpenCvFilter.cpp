#include "OpenCvFilter.h"

void OpenCvFilter::setup(int imageWidth, int imageHeight, int screenWidth, int screenHeight){
	// allocate the grayscale image holder for the kinect feed
	grayImage.allocate(imageWidth, imageHeight);
	// these are used to make the grawscale with the points we want
	grayThreshNear.allocate(imageWidth, imageHeight);
	grayThreshFar.allocate(imageWidth, imageHeight);
	w = imageWidth;
	h = imageHeight;
	s_w = screenWidth;
	s_h = screenHeight;

	    // values for near and far threshold
    // these values the points which are interesting
    nearThreshold = 241;
	farThreshold = 230;

	depthPixels = 0;
}


void OpenCvFilter::update(unsigned char* _depthPixels){
    depthPixels = _depthPixels;
}

void OpenCvFilter::threadedFunction() {
    while (isThreadRunning()){
        lock();
        grayImage.resize(w, h );
        grayImage.setFromPixels(depthPixels, w, h );

        grayThreshNear = grayImage;
        grayThreshFar = grayImage;
        grayThreshNear.threshold(nearThreshold, true);
        grayThreshFar.threshold(farThreshold);
        cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        grayImage.mirror(false, true);
        grayImage.resize(s_w, s_h);
        unlock();
        ofSleepMillis(10);
    }
}


void OpenCvFilter::draw(){
    grayImage.draw(0, 0);
}
