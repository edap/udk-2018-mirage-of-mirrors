#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    gui.add(limit.setup("n rays", 140, 10, 5000));
    gui.add(freq.setup("freq", 1, 0.1, 10));
    gui.add(velocity.set("velocity", 2.5, 0.1, 10));
    gui.add(color.setup("color", ofColor(240, 255, 255), ofColor(0, 0), ofColor(255, 255)));
    orig = glm::vec2(ofGetWidth()/2, ofGetHeight()/2);
    auto sinedT = sin(ofGetElapsedTimef() * freq);
    auto cosinedT = cos(ofGetElapsedTimef() * freq);
    startDir = glm::vec2(sinedT, cosinedT);

    ray.init(orig, startDir, 500);
}

//--------------------------------------------------------------
void ofApp::update(){
    // in this sketch, the function drawBounces is changing the position and the direction of the ray at each bounce.
    // that's why we need to reposition the ray and reset the direction in the update method
    //orig = glm::vec2(ofGetWidth()/2, ofGetHeight()/2);
    //ray.setOrigin(orig);

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(color);

    ray.draw();

    for(auto s:segments){
        ofPushStyle();
        ofSetColor(s.color);
        ofDrawLine(s.a, s.b);
        ofPopStyle();
    }

    ray.bounce(segments, velocity);

    if (isDrawing) {
        auto mouse = glm::vec2(ofGetMouseX(), ofGetMouseY());
        ofDrawLine(startPoint, mouse);
    }

    if (drawGui) {
        gui.draw();
    }

}

void ofApp::drawLine(glm::vec2 o, glm::vec2 e, ofColor c){
    ofPushStyle();
    ofSetColor(c);
    ofDrawLine(o,e);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'g') {
        drawGui = !drawGui;
    }

    if (key == 'c') {
        segments.clear();
        ray.reset();
    }

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
    startPoint = glm::vec2(x, y);
    isDrawing = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    endPoint = glm::vec2(x, y);
    // sined color
    auto sinedCol = abs(sin(ofGetElapsedTimef()) * 255);
    auto col = ofColor::fromHsb(sinedCol, 255, 255);

    Segment segTemp;
    segTemp.a = startPoint;
    segTemp.b = endPoint;
    segTemp.color = col;
    segments.push_back(segTemp);
    isDrawing = false;
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
