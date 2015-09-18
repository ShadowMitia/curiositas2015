
#ifndef CONTOURMANAGER_H
#define CONTOURMANAGER_H

#include "ofMain.h"

#include <string>
#include <vector>

#include "ofxOpenCv.h"


class ContourInfo {
 public:
  int tag;
  unsigned long long startTime;
  bool isRecentlyUpdated;
ContourInfo() : tag(-1), startTime(-1), isRecentlyUpdated(false) {
      
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

    std::vector<ContourInfo> contourInfos;

    ofTessellator tess;
    ofMesh contourMesh;
    std::vector<ofPolyline> polyContour;


    float maxDistance;

    int totalContours;
};



#endif // CONTOURMANAGER_H
