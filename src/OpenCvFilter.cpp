#include "OpenCvFilter.h"

void OpenCvFilter::setup(int imageWidth, int imageHeight, int screenWidth, int screenHeight){
	// allocate the grayscale image holder for the kinect feed
	grayImage.allocate(screenWidth, screenHeight);
	// these are used to make the grawscale with the points we want
	grayThreshNear.allocate(screenWidth, screenHeight);
	grayThreshFar.allocate(screenWidth, screenHeight);

	temp.allocate(imageWidth, imageHeight);

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
    temp.setFromPixels(depthPixels, w, h);
    grayImage.setROI(0, 0, w, h);
    cvAnd(grayImage.getCvImage(), temp.getCvImage(), grayImage.getCvImage(), NULL);

    grayThreshNear = grayImage;
    grayThreshNear.setROI(0, 0, w, h);
    grayThreshFar = grayImage;
    grayThreshFar.setROI(0, 0, w, h);
    grayThreshNear.threshold(nearThreshold, true);
    grayThreshFar.threshold(farThreshold);
    cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
    grayImage.mirror(false, true);
}


void OpenCvFilter::draw(){
    grayImage.draw(0, 0);
}
