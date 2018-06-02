#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ray.setup(glm::vec2(100,100), glm::vec2(0,1));

    blur.setupRGB(ofGetWindowWidth(), ofGetWindowHeight());
    blur.setMode(3);
    parameters.setName("settings");
    parameters.add(blur.parametersRGB);
    parameters.add(freq.set("freq",0.5,0.1, 3.0));
    gui.setup(parameters);
    gui.loadFromFile("settings.xml");

    bypass = false; //bypass shader;
}

//--------------------------------------------------------------
void ofApp::update(){
    auto orig = glm::vec2(ofGetWidth()/2, ofGetHeight()/2);
    ray.setOrigin(orig);

    float sinedT;
    float cosinedT;
    if (rotateRay){
        sinedT = sin(ofGetElapsedTimef() * freq);
        cosinedT = cos(ofGetElapsedTimef() * freq);
    } else {
        sinedT = sin(oldTime * freq);
        cosinedT = cos(oldTime * freq);
    }

    ray.setDirection(glm::vec2(sinedT, cosinedT));
}

//--------------------------------------------------------------
void ofApp::draw(){
    blur.begin();
    //ray.draw();

    if (drawSegments) {
        for(auto s:segments){
            ofPushStyle();
            ofSetColor(s.color);
            ofDrawLine(s.a, s.b);
            ofPopStyle();
        }
    }

    int maxBounces = 30;
    drawBouncingRay(ray,maxBounces);

    if (isDrawing) {
        auto mouse = glm::vec2(ofGetMouseX(), ofGetMouseY());
        ofDrawLine(startPoint, mouse);
    }
    blur.endRGB();

    if(drawGui){
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
            //drawLineAsRect(myRay.getOrigin(), intersectionPoint, color, 7.);
            //drawLineAsRectRounded(myRay.getOrigin(), intersectionPoint, color, 10.);

            // the direction of the ray will be the direction of the reflected light
            auto segmentDir = tmpSegment.a - tmpSegment.b;
            auto segmentSurfaceNormal = glm::vec2(segmentDir.y, -segmentDir.x);
            auto reflectDir = glm::reflect(myRay.getDirection(), segmentSurfaceNormal);

            // the origin of the new ray is the intersection point moved a bit along the
            // reflected direction. This is to avoid to have a new ray that intersect with the segment
            // on which its origin lays.

            myRay.setup(intersectionPoint +reflectDir*eps,reflectDir);
            //myRay.draw(); try to draw the ray to understand what is happening
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
    if(key == 'g'){
        drawGui = !drawGui;
    }
    if (key == 'c') {
        segments.clear();
    }
    if (key == 's') {
        drawSegments = !drawSegments;
    }
    if (key == 'r') {
        oldTime = ofGetElapsedTimef();
        rotateRay = !rotateRay;
    }

    if(key == ' '){
        bypass = !bypass;
        blur.setBypass(bypass);
    }
    else if(key == '0'){
        blur.setMode(0);
    }
    else if(key == '1'){
        blur.setMode(1);
    }
    else if(key == '2'){
        blur.setMode(2);
    }
    else if(key == '3'){
        blur.setMode(3);
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
