#include "ContourManager.h"

ContourManager::ContourManager() {
    oscMessage = "";
    leftRightMinLimitValue = 1.0 - 1/10000;
    upDownMinLimitValue = 1.0;
    maxDistance = 100;
    totalContours = 0;

    contourInfos.resize(10);
}

void ContourManager::trackObjects() {
    if (centroids.size() > 0){
        vector<int> updated;
	for (unsigned int j = 0; j < centroids.size(); j++) {	
	    bool isClosePoint = false;       
  	    for (unsigned int i = 0; i < contourInfos.size(); i++) {	
		if ( centroids[j].distance(contourInfos[i].point) < 50 ) {
		    contourInfos[i].point = centroids[j];
		    updated.push_back(i);
		    isClosePoint = true;
		    break;
     		}
	    }

	    if (!isClosePoint) {
		for (unsigned int i = 0; i < contourInfos.size(); i++) {
		    if ( contourInfos[i].point.x == 25000 && contourInfos[i].point.y == 25000){
			contourInfos[i].point = centroids[j];
			contourInfos[i].startTime = ofGetElapsedTimef();
			updated.push_back(i);
			break;
		    }
		}
	    }
	}
	
	for (unsigned int i = 0; i < contourInfos.size(); i++) {
	    bool trouve = false;
	    for (unsigned int j = 0; j < updated.size(); j++) {
		if (i == updated[j]) {
		    trouve = true;
		    break;
		}
	    }

	    if (!trouve){
		contourInfos[i].point.x = 25000;
		contourInfos[i].point.y = 25000;
		contourInfos[i].startTime = -1;
	    }
	}
    }
}


void ContourManager::processContours(vector<ofxCvBlob> _blobs) {
    blobs = _blobs;
    oldCentroids = centroids;
    centroids.clear();
    goingLeft.clear();


    for (unsigned int i = 0; i < blobs.size(); i++){
	centroids.push_back(blobs[i].centroid);
    }

    trackObjects();

    for (unsigned int i = 0; i < centroids.size(); i++){
	if (oldCentroids.size() == centroids.size() ){
	    //std::cout << "diff: " << centroids[i].y - oldCentroids[i].y << /*" y: " << centroids[i].y << " old y: " << oldCentroids[i].y <<*/ std::endl;
	    if ( abs( centroids[i].y - oldCentroids[i].y ) > leftRightMinLimitValue ){
		goingLeft.push_back( centroids[i].y > oldCentroids[i].y ? 1 : -1);
	    } else {
		goingLeft.push_back(0);
	    }

	    if ( abs( centroids[i].x - oldCentroids[i].x)  > upDownMinLimitValue ) {
		goingUp.push_back( centroids[i].x > oldCentroids[i].x ? 1 : -1);
	    } else {
		goingUp.push_back(0);
	    }

	}
    }
}

void ContourManager::setLeftRightErrorValue(float newValue) {
    leftRightMinLimitValue = newValue;
}

void ContourManager::collectContours() {
    if (blobs.size() > 0) {
	polyContour.clear();
	polyContour.resize(blobs.size());
	for (unsigned int i = 0; i < blobs.size(); i++) {
	    polyContour[i].addVertices(blobs[i].pts);
	    polyContour[i].setClosed(true);
	}
    }
    tess.tessellateToMesh(polyContour, OF_POLY_WINDING_POSITIVE, contourMesh);
}
