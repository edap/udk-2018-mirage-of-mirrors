#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    gui.add(limit.setup("n rays", 140, 10, 5000));
    gui.add(freq.setup("freq", 1, 0.1, 10));
    gui.add(color.setup("color", ofColor(240, 255, 255), ofColor(0, 0), ofColor(255, 255)));

    auto orig = glm::vec2(ofGetWidth()/2, ofGetHeight()/2);
    ray.setup(orig, glm::vec2(1,1));
}

//--------------------------------------------------------------
void ofApp::update(){
    auto sinedT = sin(ofGetElapsedTimef() * freq);
    auto cosinedT = cos(ofGetElapsedTimef() * freq);
    ray.setDirection(glm::vec2(sinedT, cosinedT));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(color);
    //ray.draw();

    for(auto s:segments){
        ofPushStyle();
        ofSetColor(s.color);
        ofDrawLine(s.a, s.b);
        ofPopStyle();

        doesItIntersect = ray.intersectsSegment(s.a, s.b, distance);
        // is there an intersection? add a new ray
        if(doesItIntersect){
            // keep the rays number under the limit
            if (rays.size() < limit) {
                auto intersection = ray.getOrigin() + ray.getDirection() * distance;
                Segment tmpSegment;
                tmpSegment.a = ray.getOrigin();
                tmpSegment.b = intersection;
                tmpSegment.color = s.color;
                rays.push_back(tmpSegment);
            } else {
                rays.erase(rays.begin());
            }
        }
    }

    for (auto r:rays) {
        ofPushStyle();
        ofSetColor(r.color);
        ofDrawLine(r.a, r.b);
        ofPopStyle();
    }

    if (isDrawing) {
        auto mouse = glm::vec2(ofGetMouseX(), ofGetMouseY());
        ofDrawLine(startPoint, mouse);
    }

    if (drawGui) {
        gui.draw();
    }

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'g') {
        drawGui = !drawGui;
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
