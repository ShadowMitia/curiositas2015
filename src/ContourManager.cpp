#include "ContourManager.h"

ContourManager::ContourManager() {
    oscMessage = "";
    leftRightMinLimitValue = 1.0 - 1/10000;
    upDownMinLimitValue = 1.0;
    maxDistance = 5;
    totalContours = 0;
}

void ContourManager::trackObjects() {

    // For every point, calculate which point is it closest to in previous frame
    for (int i = 0; i < centroids.size(); i++) {
	int pos = 0;
	float temp = -1;
	for (int j = 0; j < oldCentroids.size(); j++) {
	    temp = blobs[i].centroid.squareDistance(oldCentroids[0]);
	    float d = centroids[i].squareDistance(oldCentroids[j]);
	    if (d > temp) {
		temp = d;
		pos = j;
	    }
	}

	// If distance is too big
	if (temp < maxDistance && temp >= 0) {
	    ContourInfo tempC = contourInfos[pos];
	    contourInfos[pos] = contourInfos[i];
	    contourInfos[i] = tempC;
	    contourInfos[i].isRecentlyUpdated = true;
	} else { // change point position in list, to have tag at same position as the point detected
	    ContourInfo contour;
	    contour.tag = totalContours;
	    contour.startTime = ofGetElapsedTimef();
	    contour.isRecentlyUpdated = true;
	    contourInfos.push_back(contour);
	    totalContours++;
	}
    }
    
    for (int i = 0; i < contourInfos.size(); i++) {
	if (contourInfos[i].isRecentlyUpdated){
	    contourInfos[i].isRecentlyUpdated = false;
	} else {
	    contourInfos.erase(contourInfos.begin() + i);
	}
    }

    totalContours = contourInfos.size();
    
}

void ContourManager::processContours(vector<ofxCvBlob> _blobs) {
    blobs = _blobs;
    oldCentroids = centroids;
    centroids.clear();
    goingLeft.clear();


    for (int i = 0; i < blobs.size(); i++){
	centroids.push_back(blobs[i].centroid);
    }

    trackObjects();

    for (int i = 0; i < centroids.size(); i++){
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
	for (int i = 0; i < blobs.size(); i++) {
	    polyContour[i].addVertices(blobs[i].pts);
	    polyContour[i].setClosed(true);
	}
    }
    tess.tessellateToMesh(polyContour, OF_POLY_WINDING_POSITIVE, contourMesh);
}
