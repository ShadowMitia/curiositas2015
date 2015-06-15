#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    /*
    //ofSetLogLevel(OF_LOG_VERBOSE);

    ofEnableAlphaBlending();
    ofSetCircleResolution(100);

    width = 300;
    height = 600;

    // Initial Allocation
    //
    fluid.allocate(width, height, 0.5);

    // Seting the gravity set up & injecting the background image
    //
    fluid.dissipation = 0.99;
    fluid.velocityDissipation = 0.99;

    fluid.setGravity(ofVec2f(0.0,0.0));
//    fluid.setGravity(ofVec2f(0.0,0.0098));

    //  Set obstacle
    //
    fluid.begin();
    ofSetColor(0,0);
    ofSetColor(255);
    ofCircle(width*0.5, height*0.35, 40);
    fluid.end();
    fluid.setUseObstacles(false);

    // Adding constant forces
    //
    fluid.addConstantForce(ofPoint(width*0.5,height*0.85), ofPoint(0,-2), ofFloatColor(0.5,0.1,0.0), 10.f);

    ofSetWindowShape(width, height);
    */

    fluid.allocate(width,height);
    fluid.dissipation = 0.99;
    fluid.velocityDissipation = 0.99;
    fluid.setGravity(ofPoint(0,0));
}

//--------------------------------------------------------------
void ofApp::update(){
    /*
    // Adding temporal Force
    //
    ofPoint m = ofPoint(mouseX,mouseY);
    ofPoint d = (m - oldM)*10.0;
    oldM = m;
    ofPoint c = ofPoint(640*0.5, 480*0.5) - m;
    c.normalize();
    fluid.addTemporalForce(m, d, ofFloatColor(c.x,c.y,0.5)*sin(ofGetElapsedTimef()),3.0f);

    //  Update
    //
    fluid.update();

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    */
    /// Fuild Rebond delect ///



    posFluid=ofPoint(sphere->getPosition().z+width/2,sphere->getPosition().x+height/2);


    fluid.update();






}

//--------------------------------------------------------------
void testApp::draw(){

    ofSetColor(255, 0, 0);
    ofFill();

	/*

    //draw red circles for found blobs
	for (int i=0; i<contoursKinect1.nBlobs; i++) {
		ofCircle(contoursKinect1.blobs[i].centroid.x, contoursKinect1.blobs[i].centroid.y, 20);
    }
	    //draw red circles for found blobs
	for (int i=0; i<contoursKinect2.nBlobs; i++) {
		ofCircle(contoursKinect2.blobs[i].centroid.x, contoursKinect2.blobs[i].centroid.y, 20);
    }
	*/

    ofSetColor(255,255,255);

	if (drawDebug) {
		world.drawDebug();
	}

	//Camera

	ofSetColor(0, 0, 0);

    //light.setOrientation(ofVec3f(x,y,z));
    if (numberCamera == 1){

	cam[numberCamera].begin();

    ofSetColor(0, 100, 0, 255);
	ground.draw();

    ofSetColor(225, 0, 225, 255);
	sphere->draw();

	/*
	areaWalls[0].draw();
	areaWalls[1].draw();
	*/

	ofSetColor(0, 0, 255, 255);
	racketPlayer1->draw();
	ofSetColor(255,0,0);
	racketPlayer2->draw();

	areaWalls[0].draw();
	areaWalls[1].draw();


	cam[numberCamera].end();}

    if(numberCamera==0){
      fluid.draw();
	  ofSetColor(255,0,0);
	 // ofCircle (sphere->getPosition().z+width/2,sphere->getPosition().x+height/2,sphere->getPosition().y*-45/1000+5); //ivi
    }

	//////////////////////////////////////////////////////


	/*
	stringstream ss;
	btVector3 vec = sphere->getRigidBody()->getLinearVelocity();

	//ss << "ball: velocity (x,y,z): " << vec.getX() << " " << vec.getY() << " " << vec.getZ() << endl;
    //ss << endl;

	ss << "framerate " << ofToString(ofGetFrameRate(), 0) << endl;
	ss << "racket 1: " << racketPlayer1->getPosition() <<endl;
	ss << " angle hori " << racket1AngleHori << " offset " << offsetAngleH << endl;
	ss << " angle verti " << racket1AngleVerti << endl;
	ss << endl << "centroid: " << positionKinect1 << endl;
	ss << "delta 1"<< racketPlayer1->getPosition()-positionKinect1 << endl;
	ss << endl;
	ss << "racket 2: " << racketPlayer2->getPosition() <<endl;
	ss << "sphere: " << sphere->getPosition() << endl;
	//ss << "areaWall 0 " << areaWalls[0].getPosition() << endl;
	//ss << "areaWall 1 " << areaWalls[1].getPosition() << endl;
	//ss << endl;
	ss << endl << "centroid 2: " << positionKinect2 << endl;
	ss << "delta 2"<< racketPlayer2->getPosition()-positionKinect2 << endl;
	ss << "sphere velocity " << sphere->getRigidBody()->getLinearVelocity().getX() << " "
		<< sphere->getRigidBody()->getLinearVelocity().getY()
		<< sphere->getRigidBody()->getLinearVelocity().getZ()
		<< endl;
	ss << endl;

	//ss << endl << endl << "speed (x, y, z) " << speed.getX() << " " << speed.getY() << " " << speed.getZ() << endl;


	//ss << endl << "old " << oldPositionKinect1 << endl;

	//ss << endl << "angle hori" << racket1AngleHori << endl;
	//ss << endl << "angle verti" << racket1AngleVerti << endl;

	//ss << endl << "old 2 " << oldPositionKinect2 << endl;
	//ss << endl << "delta 2 " << racketPlayer2->getPosition().z - positionKinect2.z << endl;
	//ss << endl << "angle hori 2 " << racket2AngleHori << endl;
	//ss << endl << "angle verti 2 " << racket2AngleVerti << endl;

    ofSetColor(255, 0, 0);
	ofDrawBitmapString(ss.str().c_str(), 10, 10);
	ofDrawBitmapString(speedy.str(), 100, 10);
	*/
}

void testApp::keyPressed(int key) {
	switch (key) {

	// Camera 0
    case OF_KEY_F1:
        numberCamera=0;
        break;

	// Camera 1
	case OF_KEY_F2:
        numberCamera=1;
        break;

	case 'f':
		offsetAngleH += 2;
		break;

	case 'g':
		offsetAngleH -= 2;
		break;



	case OF_KEY_RETURN:
		createSphere(!player1TouchedBallLast);
	 break;

	case 'd':
		//debug stuff
		drawDebug = ! drawDebug;
		break;
	}
}

void testApp::onCollision(ofxBulletCollisionData& cdata){
	if (*sphere == cdata){
		cout << "sphere collision" << endl;
	}

	if (*racketPlayer1 == cdata) {
		cout << "racket 1 collision" << endl;
		player1TouchedBallLast = true;

	}

	if (*racketPlayer2 == cdata){
		cout << "racket 2 collision" << endl;
		player1TouchedBallLast = false;
	}

	if (ground == cdata) {
		cout << "ground collision" << endl;
	}

	if (ground == cdata && *sphere == cdata) {
		cout << " ground + sphere " << endl;

        /// Creat Rose Fluid ///
        rose.clear();

        rose.push_back(ofGetElapsedTimef());
        rose.push_back(sphere->getPosition().z+width/2);
        rose.push_back(sphere->getPosition().x+height/2);

        rose.push_back((float) rand() / (float)RAND_MAX);
        rose.push_back((float) rand() / (float)RAND_MAX);
        rose.push_back((float) rand() / (float)RAND_MAX);

        rose.push_back(2*PI*(float) rand() / (float)RAND_MAX) ;
        rose.push_back(2*PI*(float) rand() / (float)RAND_MAX) ;



        posRose.push_back(rose);


    }

	if ( (*racketPlayer1 == cdata && *sphere == cdata) || (*racketPlayer2 == cdata && *sphere == cdata) ) {
		cout << "racket + sphere " << endl;
		service = false;
	}

	if (areaWalls[0] == cdata || areaWalls[1] == cdata ) {
		cout << "wall + sphere collision " << endl;

		btVector3 velocity = sphere->getRigidBody()->getLinearVelocity();
		velocity.setZ( velocity.getZ() * 3);
		/*	float norm = sqrt( velocity.getX() * velocity.getX() +  velocity.getZ() * velocity.getZ());
		if (norm !=0)  {
				velocity.setX( ( velocity.getX() * (500 / norm ) ) );
				velocity.setZ( ( velocity.getZ()  * (500 / norm) ));
		}*/
		sphere->getRigidBody()->setLinearVelocity(velocity);


	}

	if (areaWalls[0] == cdata) {
		cout << "wall 0 collision " << endl;
	}

	if (areaWalls[1] == cdata) {
		cout << "wall 1 collision " << endl;
	}
}

void testApp::createSphere(bool playerOne){

	   sphere->remove();
	   delete sphere;
		sphere = new ofxBulletSphere();

		if (playerOneServed && !playerTwoServed) {
			sphere->create(world.world, ofVec3f(0, -300, 400 ), 50, 30);
			sphere->getRigidBody()->setLinearVelocity(btVector3(0, 0, -500 ));
		}
		if (!playerOneServed && playerTwoServed) {
			sphere->create(world.world, ofVec3f(0, -300, -400 ), 50, 30);
			sphere->getRigidBody()->setLinearVelocity(btVector3(0, 0, 500));
		}

		sphere->setProperties(5, 0);
		sphere->add();



}

        if ((rose[0]+10<ofGetElapsedTimef() || (abs(rose[1]-(sphere->getPosition().z+width/2))< 20 && abs(rose[2]-(sphere->getPosition().x+height/2))< 20)) && rose[0]+1< ofGetElapsedTimef())
        {


            posRose.erase(range_begin);
        }
    }


    posFluid=ofPoint(sphere->getPosition().z+width/2,sphere->getPosition().x+height/2);


                                            fluid.update();



                                    ////// Fin Fuild ALEX   //////
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::gray, ofColor::black, OF_GRADIENT_LINEAR);

    fluid.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'p')
        bPaint = !bPaint;
    if( key == 'o')
        bObstacle = !bObstacle;
    if( key == 'b')
        bBounding = !bBounding;
    if( key == 'c')
        bClear = !bClear;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
