#ifndef OPENCVFILTER_H
#define OPENCVFILTER_H

#include "ofMain.h"
#include "ofxOpenCv.h"

class OpenCvFilter {

    public:
        OpenCvFilter() {}
        void setup(int imageWidth, int imageHeight, int screenWidth, int screenHeight);
        void update(unsigned char* depthPixels);
        void draw();

        ofxCvGrayscaleImage& getThreshImage() { return grayImage; }


    private:
        ofxCvGrayscaleImage grayImage; // grayscale depth image
        ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
        ofxCvGrayscaleImage grayThreshFar; // the far thresholded image

        int w;
        int h;
        int s_w;
        int s_h;

        int nearThreshold;
        int farThreshold;
};


#endif // OPENCVFILTER_H
