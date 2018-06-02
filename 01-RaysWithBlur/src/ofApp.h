#pragma once

#include "ofMain.h"
#include "ofxRaycaster.h"
#include "ofxBlurUtils.h"
#include "ofxGui.h"

class Segment {
public:
    glm::vec2 a;
    glm::vec2 b;
    ofColor color;
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void drawBouncingRay(ofxraycaster::Ray<glm::vec2>& myRay, int& limit);
        void drawLine(glm::vec2 o, glm::vec2 e, ofColor col);

    vector<Segment> segments;
    ofxraycaster::Ray<glm::vec2> ray;
    glm::vec2 startPoint;
    glm::vec2 endPoint;

    // blur effect
    ofxBlurUtils blur;
    bool bypass;
    int mode;

    //gui
    bool drawGui = true;
    bool drawSegments = true;
    bool isDrawing = false;
    bool rotateRay = true;
    float oldTime = 0;

    ofxPanel gui;
    ofParameter <float> freq;
    ofParameterGroup parameters;
    ofXml settings;

};
