#ifndef OF_APP
#define OF_APP


#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "Smoke.h"

#define WIDTH 1280
#define HEIGHT 800

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

    // ofxKinect
    int camWidth;
    int camHeight;

    std::deque<ofPolyline> polyContour;

    ofShader blackHandShader;
    int nearThreshold;
    int farThreshold;

    bool showDebugVideo;

    ofFbo buffer;

    Smoke smoke;
};



#endif // OF_APP
