#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
    cam.setup(1280, 720);
    tracker.setup();
}

void ofApp::update() {
    cam.update();
    if(cam.isFrameNew()) {
        tracker.update(toCv(cam));
    }
    leftEye = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE_TOP).getCentroid2D();
    rightEye = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE_TOP).getCentroid2D();

}

void ofApp::draw() {
    ofSetColor(255);
    cam.draw(0, 0);
    ofSetLineWidth(2);

    ofDrawCircle(leftOuterObj.x, leftOuterObj.y, 3 * tracker.getScale());
    ofDrawCircle(rightInnerObj.x, rightInnerObj.y, 2 * tracker.getScale());

    //draw the frame rate
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
    tracker.draw();
}

void ofApp::keyPressed(int key) {
    if(key == 'r') {
        tracker.reset();
    }
}
