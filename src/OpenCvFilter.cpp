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
    nearThreshold = 200;
	farThreshold = 180;

	depthPixels = 0;

}


void OpenCvFilter::update(unsigned char* _depthPixels){
    depthPixels = _depthPixels;
    grayImage.setFromPixels(depthPixels, w, h);
    grayImage.rotate(-90, w/2, h/2);
    grayThreshNear = grayImage;
    grayThreshFar = grayImage;
    grayThreshNear.threshold(nearThreshold, true);
    grayThreshFar.threshold(farThreshold);
    cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
    grayImage.mirror(true, true);
}


void OpenCvFilter::draw(){
    grayImage.draw(0, 0);
}

void OpenCvFilter::setFarThreshold(int newVal) {
    farThreshold = newVal;
}

void OpenCvFilter::setNearThreshold(int newVal) {
    nearThreshold = newVal;
}
