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
}

void ofApp::draw() {
    //ofSetColor(255);
	//cam.draw(0, 0);
	ofSetLineWidth(2);
	tracker.draw();
    
    auto featurePolyline = tracker.getImageFeature(ofxFaceTracker::OUTER_MOUTH);

//    feature position
//    ofPolyline noseBase = tracker.getImageFeature(ofxFaceTracker::NOSE_BASE);
//    ofSetColor(ofColor::red);
//    noseBase.draw();
//    ofDrawCircle(noseBase.getCentroid2D(), 8 * tracker.getScale());

    drawFeature(0, 0, ofxFaceTracker::OUTER_MOUTH);

	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
}

void ofApp::drawFeature(int x, int y, ofxFaceTracker::Feature feature, float scaleX, float scaleY){

    auto featurePolyline = tracker.getImageFeature(feature);
    if(featurePolyline.size() > 3){
        ofRectangle boundingBox = featurePolyline.getBoundingBox();
        ofTexture tex = grabFeature(featurePolyline, boundingBox);
        tex.draw(x, y, boundingBox.width * scaleX, boundingBox.height * scaleY);
    };
};

ofTexture ofApp::grabFeature(ofPolyline featureProfile, ofRectangle bBox){
    ofPixels pixels;
    ofPixels alphaPixels;
    ofTexture featureTexture;

    // sample the poliline
    featureProfile.getSmoothed(100);

    cam.getTexture().readToPixels(pixels);

    // get the box containing the feature
    pixels.crop(bBox.x,bBox.y,bBox.width,bBox.height);

    //allocate the texture and the pixels with the alpha transparency
    featureTexture.allocate(bBox.width, bBox.height, GL_RGBA);
    alphaPixels.allocate(pixels.getWidth(), pixels.getHeight(), OF_IMAGE_COLOR_ALPHA);

    int totalPixels = pixels.getWidth()*pixels.getHeight();

    for (int x = 0; x < pixels.getWidth(); x++){
        for (int y = 0; y < pixels.getHeight(); y++){
            ofPoint checkpoint = ofPoint(x+bBox.x,y+bBox.y);
            if (featureProfile.inside(checkpoint)) {
                ofColor c = pixels.getColor(x,y);
                alphaPixels.setColor(x,y,c);
            } else {
                //make transparent the discarded pixels
                alphaPixels.setColor(x,y, ofColor(0,0,0,0));
            }
        }
    }

    featureTexture.loadData(alphaPixels);
    return featureTexture;
}


void ofApp::keyPressed(int key) {
    if(key == 'r') {
        tracker.reset();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
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
