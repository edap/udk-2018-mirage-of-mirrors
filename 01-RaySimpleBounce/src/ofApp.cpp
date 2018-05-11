#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ray.setup(glm::vec2(100,100), glm::vec2(0,1));

    s1.a = glm::vec2(600, 10);
    s1.b = glm::vec2(800, 200);
    s1.color = ofColor(255,0,0);

    s2.a = glm::vec2(200, 700);
    s2.b = glm::vec2(600, 700);
    s2.color = ofColor(00,255,100);

}

//--------------------------------------------------------------
void ofApp::update(){
    if(rotate){
        auto sineT = sin(ofGetElapsedTimef() * freq);
        auto cosT = cos(ofGetElapsedTimef() * freq);
        ray.setDirection(glm::vec2(sineT, cosT));
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ray.draw();
    drawLine(s1.a, s1.b, s1.color);
    drawLine(s2.a, s2.b, s2.color);

    float distance;
    if(ray.intersectsSegment(s1.a, s1.b, distance)){
        auto firstIntersection = ray.getOrigin() + ray.getDirection() * distance;
        drawLine(ray.getOrigin(),firstIntersection, ofColor(s1.color));

        //we need the reflected dir to calculate the bounce!
        glm::vec2 segmentDir = glm::normalize(s1.a - s1.b);
        // and then we use as normal a vector orthogonal to direction.
        glm::vec2 segmentSurfaceNormal = glm::vec2(segmentDir.y, -segmentDir.x);
        auto firstReflectedDir = glm::reflect(ray.getDirection(), segmentSurfaceNormal);


        //update the previous ray and check for intersections
        ray2.setup(firstIntersection, firstReflectedDir);




        if(ray2.intersectsSegment(s2.a, s2.b, distance)){
            auto secondIntersection = ray2.getOrigin() + ray2.getDirection() * distance;
            drawLine(ray2.getOrigin(),secondIntersection, ofColor(s1.color));

            //calculate the reflected dir for the second ray
            glm::vec2 segmentDir = glm::normalize(s2.a - s2.b);
            // and then we use as normal a vector orthogonal to direction.
            glm::vec2 segmentSurfaceNormal = glm::vec2(segmentDir.y, -segmentDir.x);
            auto secondReflectedDir = glm::reflect(ray2.getDirection(), segmentSurfaceNormal);

            auto farAway = secondIntersection + secondReflectedDir * 10000;
            drawLine(secondIntersection,farAway, ofColor(s2.color));
        }else{
            auto farAway =firstIntersection + firstReflectedDir * 10000;
            drawLine(firstIntersection, farAway, ofColor(s1.color));
        }
    }


}

void ofApp::drawLine(glm::vec2 o, glm::vec2 e, ofColor col){
    ofPushStyle();
    ofSetColor(col);
    ofSetLineWidth(10);
    ofDrawLine(o, e);
    ofPopStyle();
};

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r'){
        rotate = !rotate;
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
