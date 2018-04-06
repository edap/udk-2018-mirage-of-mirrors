#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    fbo.allocate(ofGetWidth() / 2., ofGetHeight(), GL_RGBA);
    fbo.begin();
    ofClear(255, 255, 255, 0);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    if (ofGetElapsedTimef() < 5) {
        ofDrawBitmapString("click and drag on the left side of the screen", 10, 20);
    }

    // draw on the left side of the screen
    fbo.draw(0,0);

    // draw what the user is drawing
    if (drawing) {
        drawCircle();
    }

    // draw the same texture flipped horizontally, in the right
    // side of the screen
    ofTexture flipped = fbo.getTexture();
    float pos = ofGetWidth() / 2.;
    flipped.draw(ofGetWidth(), 0, -pos, ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'c') {
        fbo.begin();
        ofClear(255, 255, 255, 0);
        fbo.end();
    }

    if (key == 'f') {
        fill = !fill;
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
    toCenter = glm::vec2(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    drawing = true;
    toCenter = glm::vec2(x,y);
    center = glm::vec2(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    fbo.begin();
    drawCircle();
    fbo.end();
    drawing = false;
}

ofColor ofApp::pickColor(){
    int saturation = 255;
    int brightness = 255;
    int alpha = 200;
    float sinOfTime = sin(ofGetElapsedTimef()*0.5);
    float hue = ofMap(sinOfTime, -1, 1, 0, 255);
    ofColor c = ofColor::fromHsb(hue, saturation, brightness);
    c.a = alpha;
    return c;
}

void ofApp::drawCircle(){
    ofPushStyle();
    //auto c = pickColor();
    auto c = ofColor(255,0,0);
    ofSetColor(c);
    ofSetCircleResolution(resolution);
    if (!fill) {
        ofSetLineWidth(ofMap(sin(ofGetElapsedTimef()*1.5), -1, 1, 1, 10));
        ofNoFill();
    }
    ofDrawCircle(center, glm::distance(center, toCenter));
    ofPopStyle();
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
