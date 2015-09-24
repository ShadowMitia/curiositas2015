#ifndef SMOKE_H
#define SMOKE_H

#include "ofMain.h"
#include "ofxFluid.h"

class Smoke
{
    public:
        Smoke();
        virtual ~Smoke();
        void draw();
        void update();
        void addSmokePoint(ofPoint position, ofFloatColor color);
        void setSmokeConstantForce(float radius, ofPoint vel);
        void setup(int screen_width, int screen_height, float scale = 0.5, bool HD = true);
        void begin();
        void end();



    protected:
    private:

        ofxFluid fluid;

            // list of all the points of origin of the different smoke points
        std::vector<ofPoint> origins;
        // for each point we define a color
        std::vector<ofFloatColor> smokeColors;
};

#endif // SMOKE_H
