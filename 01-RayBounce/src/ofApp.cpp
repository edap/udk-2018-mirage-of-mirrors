#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ray = Ray(glm::vec2(200, 400), glm::vec2(1, -0.5));
    plane.setup(glm::vec2(700, 400), glm::vec2(-1.,-0.25));
}

//--------------------------------------------------------------
void ofApp::update(){;
    float sinedTime = sin(ofGetElapsedTimef()* 0.2);
    ray.setDirection(glm::vec2(1, sinedTime));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ray.draw();
    plane.draw();

    glm::vec2 intersection; // store the intersection value
    bool intersects; // store a boolean to check if there is an intersection
    ray.intersectsPlane(plane, intersection, intersects);

    ofPushStyle();
    // is there an intersection between the plane and the ray?
    if (intersects) {
        // draw the ray that hit the plane
        ofSetColor(100,0,100);
        ofDrawLine(ray.getOrigin(), intersection);
        // draw the reflection
        // https://glm.g-truc.net/0.9.4/api/a00131.html
        ofSetColor(60,200,200);
        auto reflectDirection = glm::reflect(ray.getDirection(), plane.getNormal());
        ofDrawLine(intersection, intersection+reflectDirection*ofGetWidth());

        // draw the refraction
        // https://glm.g-truc.net/0.9.4/api/a00131.html
        float ratio = 0.5;
        auto refractedDirection = glm::refract(ray.getDirection(), plane.getNormal(), ratio);
        ofSetColor(10,200,100);
        ofDrawLine(intersection, intersection + refractedDirection*ofGetWidth());
    }
    ofPopStyle();

    drawLegend(ray.getOrigin(), plane.getOrigin(), intersection, intersects);
}


// This method just add a description to each element of the sketch
void ofApp::drawLegend(glm::vec2 rayOrig, glm::vec2 planeOrig, glm::vec2 intersection,bool intersects){

    ofPushStyle();
    // ray
    ofSetColor(255,0,0);
    ofDrawBitmapString("Origin of the ray", rayOrig.x-200, rayOrig.y);
    ofSetColor(0,0,255);
    ofDrawBitmapString("Direction of the ray", rayOrig.x+30, rayOrig.y+10);

    //plane
    ofSetColor(0,255,0);
    ofDrawBitmapString("Origin of the plane", planeOrig.x+30, planeOrig.y);
    ofSetColor(0,0,255);
    ofDrawBitmapString("Normal of the plane", planeOrig.x-200, planeOrig.y+10);

    if (intersects) {
        //intersection, reflected light
        ofSetColor(100,0,100);
        ofDrawCircle(intersection, 10);
        ofDrawBitmapString("intersection point", intersection.x+30, intersection.y+10);
        // reflection
        ofSetColor(60,200,200);
        ofDrawBitmapString("reflected light", intersection.x-100, intersection.y -20);
        // refraction
        ofSetColor(10,200,100);
        ofDrawBitmapString("refracted light", intersection.x+100, intersection.y -20);
    }
    ofPopStyle();
};

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
