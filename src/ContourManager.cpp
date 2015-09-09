#include "ContourManager.h"

ContourManager::ContourManager() {
    oscMessage = "";
    leftRightMinLimitValue = 1.0 - 1/10000;
    upDownMinLimitValue = 1.0;
}

void ContourManager::processContours(vector<ofxCvBlob> blobs) {
    oldCentroids = centroids;
    centroids.clear();
    goingLeft.clear();
    for (int i = 0; i < blobs.size(); i++){
        centroids.push_back(blobs[i].centroid);
        if (oldCentroids.size() > 0 ){
            std::cout << "diff: " << centroids[i].y - oldCentroids[i].y << /*" y: " << centroids[i].y << " old y: " << oldCentroids[i].y <<*/ std::endl;
            if ( abs( centroids[i].y - oldCentroids[i].y ) > leftRightMinLimitValue ){
                goingLeft.push_back( centroids[i].y > oldCentroids[i].y ? 1 : -1);
                std::cout << "Going left: " << goingLeft[i] << std::endl;
            } else {
                goingLeft.push_back(0);
            }

            //if ( abs( centroids[i].y - oldCentroids[i].y) > upDownMinLimitValue))
        }
    }
}
