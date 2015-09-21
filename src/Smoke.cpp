#include "Smoke.h"


Smoke::Smoke() {

}

Smoke::~Smoke()
{
    //dtor
}

void Smoke::setup(int screen_width, int screen_height, float scale, bool HD) {
    //std::cout << "setup" << std::endl;
    // allocate the size need to show the smoke
    fluid.allocate(screen_width, screen_height, scale, HD);

    // some values to get some nice smoke
    fluid.dissipation = 0.97;
    fluid.velocityDissipation = 0.995;

    // We don't want any default gravity values
    fluid.setGravity(ofVec2f(0.0,0.0));
}

void Smoke::addSmokePoint(ofPoint position, ofFloatColor color) {
    origins.push_back(position);
    smokeColors.push_back(color);
    int index = origins.size() - 1;
    fluid.addConstantForce(origins[index], ofPoint(1,0), smokeColors[index], 1.7f);
}

void Smoke::update() {
    fluid.update();
}

void Smoke::begin(){
    fluid.begin();
}

void Smoke::end(){
    fluid.end();
}

void Smoke::draw() {
    //std::cout << "draw" << std::endl;
    fluid.draw();
}
