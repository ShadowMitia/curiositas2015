#ifndef CONTOURMANAGER_H
#define CONTOURMANAGER_H

#include "ofMain.h"

#include <string>
#include <vector>

#include "ofxOpenCv.h"

class ContourManager {
public:

    ContourManager();
    void processContours(vector<ofxCvBlob> blobs);
    string generateOscMessage();
    void setLeftRightErrorValue(float newValue) { leftRightMinLimitValue = newValue; }

public:
    string oscMessage;
    vector<ofPoint> centroids;
    vector<ofPoint> oldCentroids;
    vector<int> goingLeft;
    vector<int> goingUp;
    int leftRightMinLimitValue;
    int upDownMinLimitValue;

};

#endif // CONTOURMANAGER_H
