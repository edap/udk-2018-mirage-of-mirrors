#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#include "ofxFaceTracker.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void drawFeature(int x, int y, ofxFaceTracker::Feature feature, float scaleX = 1.0, float scaleY = 1.0);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);


    ofTexture grabFeature(ofPolyline featureProfile, ofRectangle bBox);
	
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
};
