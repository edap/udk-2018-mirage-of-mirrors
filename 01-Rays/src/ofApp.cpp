#include "ofApp.h"
// From https://forum.openframeworks.cc/t/drawing-a-circle-with-lots-of-lines/18063/4
//--------------------------------------------------------------
void ofApp::setup(){

    ofSetBackgroundAuto(false);
    ofBackground(0,0,0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

bool ofApp::bIntersects(ofPoint a, ofPoint b, ofPolyline poly){

    int res = 100;
    ofPoint step = (b-a) / res;
    bool bInside = false;
    for (int i = 0; i < res; i++){
        ofPoint temp = a + i * step;
        if (poly.inside(temp)){
            bInside = true;
            return true;
        }
    }
    return false;


}

ofPoint ofApp::randomPtForSize(ofRectangle rect, int side){

    ofPoint aa = ofPoint(rect.x, rect.y);
    ofPoint bb = ofPoint(rect.x + rect.width, rect.y);
    ofPoint cc = ofPoint(rect.x + rect.width, rect.y + rect.height);
    ofPoint dd = ofPoint(rect.x, rect.y + rect.height);

    if (side == 0){
        return aa + ofRandom(0,1) * (bb-aa);
    } else if (side == 1){
        return bb + ofRandom(0,1) * (cc-bb);
    } else if (side == 2){
        return cc + ofRandom(0,1) * (dd-cc);
    } else {
        return dd + ofRandom(0,1) * (aa-dd);
    }
    return ofPoint(0,0);


}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255,255,255,10);
    ofPolyline temp;
    float circleRes = 40;
    float circleRadius = 80;
    for (int i = 0; i < circleRes; i++){
        float x = ofGetWidth()/2 + circleRadius * cos(i/float(circleRes) * TWO_PI);
        float y = ofGetHeight()/2 + circleRadius * sin(i/float(circleRes) * TWO_PI);
        temp.addVertex(ofPoint(x,y));
    }

    ofRectangle rect(0,0,ofGetWidth(), ofGetHeight());

    for (int i = 0; i < 100; i++){
        int side = ofRandom(0,4);
        int sideb = ofRandom(0,4);
        if (side != sideb){
            ofPoint a =randomPtForSize(rect, side);
            ofPoint b =randomPtForSize(rect, sideb);
            if (!bIntersects(a,b, temp)){
                ofDrawLine(a,b);
            }
        }
    }
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
