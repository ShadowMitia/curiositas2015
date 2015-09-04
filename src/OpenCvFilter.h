#ifndef OPENCVFILTER_H
#define OPENCVFILTER_H

#include "ofMain.h"
#include "ofxOpenCv.h"

class OpenCvFilter : public ofThread {

    public:
        OpenCvFilter() {}
        void setup(int imageWidth, int imageHeight, int screenWidth, int screenHeight);
        void update(unsigned char* _depthPixels);
        void threadedFunction();
        void draw();

        ofxCvGrayscaleImage& getThreshImage() { return grayImage; }


    private:
        ofxCvGrayscaleImage grayImage; // grayscale depth image
        ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
        ofxCvGrayscaleImage grayThreshFar; // the far thresholded image

        unsigned char * depthPixels;

        int w;
        int h;
        int s_w;
        int s_h;

        int nearThreshold;
        int farThreshold;
};


#endif // OPENCVFILTER_H
