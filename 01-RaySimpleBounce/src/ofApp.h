#pragma once

#include "ofMain.h"
#include "ofxRaycaster.h"

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

    void drawLine(glm::vec2 o, glm::vec2 e, ofColor col);

    ofxraycaster::Ray<glm::vec2> ray;
    ofxraycaster::Ray<glm::vec2> ray2;
    Segment s2;
    Segment s1;
    float freq = .5;

    bool rotate = true;


};
