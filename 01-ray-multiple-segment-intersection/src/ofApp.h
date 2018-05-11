#pragma once

#include "ofMain.h"
#include "Segment.h"
#include "ofxRaycaster.h"
#include "ofxGui.h"

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

    vector<Segment> segments;
    ofxraycaster::Ray<glm::vec2> ray;

    glm::vec2 startPoint;
    glm::vec2 endPoint;

    float distance;
    bool doesItIntersect = false;

    vector<Segment> rays;

    bool isDrawing = false;

    // position the ray
    // introduce the segment class
    // add mouse interaction, click&release to create a new segment
    // draw the rays when there is an intersection
    // collect the rays and draw them
    // add a gui

    ofxPanel gui;
    ofxIntSlider limit;
    ofxFloatSlider freq;
    ofxColorSlider color;
    bool drawGui = false;

		
};
