#ifndef OF_APP
#define OF_APP


#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxFluid.h"

#define WIDTH 1024
#define HEIGHT 768


class ofApp : public ofBaseApp {
public:

	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	void setupKinect();
	void setupOpenCv();
	void setupSmokeFluid();

	void updateKinect();
    void updateOpenCv();
    void updateFluid();

    void updateCvImages();
    void collectContours();

	void drawDebug();

	ofxKinect kinect;

	ofxCvColorImage colorImg;

	ofxCvGrayscaleImage grayImage; // grayscale depth image
	ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
	ofxCvGrayscaleImage grayThreshFar; // the far thresholded image

	ofxCvContourFinder contourFinder;

	int threshold = 200;

    // ofxKinect
    int camWidth;
    int camHeight;

    ofxFluid fluid;

    std::deque<ofPolyline> polyContour;

    ofShader blackHandShader;
    int nearThreshold;
    int farThreshold;

    bool showDebugVideo;
};



#endif // OF_APP
