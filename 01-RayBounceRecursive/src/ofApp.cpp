#include "ofApp.h"
#include "utils.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    gui.add(limit.setup("n rays", 140, 10, 5000));
    gui.add(freq.setup("freq", 1, 0.1, 10));
    gui.add(color.setup("color", ofColor(240, 255, 255), ofColor(0, 0), ofColor(255, 255)));
}

//--------------------------------------------------------------
void ofApp::update(){
    // in this sketch, the function drawBounces is changing the position and the direction of the ray at each bounce.
    // that's why we need to reposition the ray and reset the direction in the update method
    auto orig = glm::vec2(ofGetWidth()/2, ofGetHeight()/2);
    ray.setOrigin(orig);
    auto sinedT = sin(ofGetElapsedTimef() * freq);
    auto cosinedT = cos(ofGetElapsedTimef() * freq);
    ray.setDirection(glm::vec2(sinedT, cosinedT));
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
    int maxBounces = 30;
    drawBouncingRay(ray,maxBounces);

    if (isDrawing) {
        auto mouse = glm::vec2(ofGetMouseX(), ofGetMouseY());
        ofDrawLine(startPoint, mouse);
    }

    if (drawGui) {
        gui.draw();
    }

}

// this function is taking as argument a & myRay, not a myRay. The & is important
// we will discuss it friday
void ofApp::drawBouncingRay(ofxraycaster::Ray<glm::vec2>& myRay, int& limit){
    float eps = 0.00001;
    while(limit > 0){
        limit--;
        float distance = std::numeric_limits<float>::infinity();
        float tmpDistance;
        bool intersection = false;
        Segment tmpSegment;
        //find the closest segment that intersect with the ray
        // save it into tmpSegment, and save the distance too.
        for (auto s:segments) {
            if (myRay.intersectsSegment(s.a, s.b, tmpDistance)) {
                if (intersection == false) { intersection = true;};
                if (tmpDistance < distance){
                    distance = tmpDistance;
                    tmpSegment = s;
                }
            }
        }

        if (intersection) {
            auto intersectionPoint = myRay.getOrigin() + myRay.getDirection() * distance;
            auto color = tmpSegment.color;
            drawLine(myRay.getOrigin(), intersectionPoint, color);

            // the direction of the ray will be the direction of the reflected light
            auto segmentDir = tmpSegment.a - tmpSegment.b;
            auto segmentSurfaceNormal = glm::vec2(segmentDir.y, -segmentDir.x);
            auto reflectDir = glm::reflect(myRay.getDirection(), segmentSurfaceNormal);

            // the origin of the new ray is the intersection point moved a bit along the
            // reflected direction. This is to avoid to have a new ray that intersect with the segment
            // on which its origin lays.

            myRay.setup(intersectionPoint +reflectDir*eps,reflectDir);
            myRay.draw(); //try to draw the ray to understand what is happening
            drawBouncingRay(myRay, limit); // recursive function, a function that call itself
        }
    }
}

void ofApp::drawLine(glm::vec2 o, glm::vec2 e, ofColor c){
    ofPushStyle();
    ofSetColor(c);
    ofDrawLine(o,e);
    ofPopStyle();

};

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'g') {
        drawGui = !drawGui;
    }

    if (key == 'c') {
        segments.clear();
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
