#pragma once

#include "ofMain.h"

class Utils{
public:
    static void drawLine(glm::vec2 _start, glm::vec2 _end, ofColor col){
        ofPushStyle();
        ofSetColor(cor);
        ofDrawLine(_start, _end);
        ofPopStyle();
    }

    static void drawEllips(glm::vec2 _start, glm::vec2 _end){
        ofPushStyle();
        ofSetColor(cor);
        ofDrawEllipse();
        ofPopStyle();
    }
};
