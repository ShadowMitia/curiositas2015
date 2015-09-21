
#ifndef CONTOURMANAGER_H
#define CONTOURMANAGER_H

#include "ofMain.h"

#include <string>
#include <list>
#include <vector>
#include <cmath>

#include "ofxOpenCv.h"


class ContourInfo {
 public:
  int tag;
  ofPoint point;
  float startTime;
  bool isRecentlyUpdated;
ContourInfo() : tag(-1), point(-1,-1), startTime(-1), isRecentlyUpdated(false) {    
  }
};

class ContourManager {
public:

    ContourManager();
    void processContours(vector<ofxCvBlob> _blobs);
    string generateOscMessage();
    void setLeftRightErrorValue(float newValue);

    void trackObjects();
    void collectContours();

public:
    string oscMessage;
    vector<ofPoint> centroids;
    vector<ofPoint> oldCentroids;
    vector<int> goingLeft;
    vector<int> goingUp;
    int leftRightMinLimitValue;
    int upDownMinLimitValue;

    vector<ofxCvBlob> blobs; 

    ofTessellator tess;
    ofMesh contourMesh;
    std::vector<ofPolyline> polyContour;


    float maxDistance;

    int totalContours;


    // tracker stuff
    vector<ContourInfo> contourInfos;
};



#endif // CONTOURMANAGER_H
