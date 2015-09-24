#ifndef OF_APP
#define OF_APP

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxOsc.h"
#include "ofxDmx.h"

#include <vector>

#include "Smoke.h"
#include "OpenCvFilter.h"
#include "ContourManager.h"

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

  void sendOsc();

  void drawDebug();

  ofxKinect kinect;

  ofxCvColorImage colorImg;
  ofxCvContourFinder contourFinder;

  std::vector<ofPolyline> polyContour;
  ofPath pathContour;

  int nearThreshold;
  int farThreshold;

  bool showDebugVideo;
  bool showDebug;

  Smoke smoke;
  OpenCvFilter cvfilter;

  ofTessellator tess;
  ofMesh contourMesh;

  int angle;

  ofxOscSender oscSender;

  ContourManager contoursManager;

  ofxDmx dmxLightsAndSmoke;
  int dmxLightsAndSmokeModules, dmxLightsAndSmokeChannelsPerModule;
  std::vector<int> dmxLightsAndSmokeMessage;
  float dmxLightsAndSmokeTimer;
  bool isDmxLightAndSmokeTimerStarted;

  string dmxPort;
  
};



#endif // OF_APP
