#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#include "ofxFaceTracker.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    ofVideoGrabber cam;
    ofxFaceTracker tracker;
    glm::vec2 leftEye;
    glm::vec2 rightEye;
};

/*
 Available features:

      LEFT_EYE_TOP, RIGHT_EYE_TOP,
        LEFT_EYEBROW, RIGHT_EYEBROW,
        LEFT_EYE, RIGHT_EYE,
        LEFT_JAW, RIGHT_JAW, JAW,
        OUTER_MOUTH, INNER_MOUTH,
        NOSE_BRIDGE, NOSE_BASE,
        FACE_OUTLINE, ALL_FEATURES
 */
