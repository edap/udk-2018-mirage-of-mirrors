#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setup(1280, 720);
    shader.load("shaders/vert.glsl", "shaders/frag.glsl");

    int planeWidth = ofGetWidth();
    int planeHeight = ofGetHeight();
    int planeGridSize = 1;
    int planeColumns = planeWidth / planeGridSize;
    int planeRows = planeHeight / planeGridSize;

    plane.set(planeWidth, planeHeight, planeColumns, planeRows, OF_PRIMITIVE_TRIANGLES);
    plane.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    plane.mapTexCoordsFromTexture(cam.getTexture());
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.getTexture().bind();
    shader.begin();
    // pass a uniform with mouse pos.
    shader.setUniform2f("uMousePos", mouseX, mouseY);
    shader.setUniform2f("uResolution", ofGetWidth(), ofGetHeight());
    plane.draw();
    shader.end();
    cam.getTexture().unbind();
}

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
