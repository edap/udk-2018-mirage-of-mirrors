#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    vidGrabber.setVerbose(true);
    vidGrabber.setup(gWidth, gHeigth);
    colorImg.allocate(gWidth, gHeigth);
    grayImage.allocate(gWidth, gHeigth);
    grayBg.allocate(gWidth, gHeigth);
    grayDiff.allocate(gWidth, gHeigth);

    bLearnBackground = true;
    gui.setup("press 0 1 2");
    gui.add(trs.set("treshold", 80, 0, 255));
    gui.add(contourSize.set("c size", 20, 5, 100));
    gui.add(contourTot.set("contour tot", 20, 10, 80));
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    if(vidGrabber.isFrameNew()){
        colorImg.setFromPixels(vidGrabber.getPixels());
        // we copy all the color pixel so the gray one
        grayImage = colorImg;

        if (bLearnBackground == true){
            grayBg = grayImage;
            bLearnBackground = false;
        }

        // take the abs value of the diff, between bg and the threshold
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(trs);

        auto maxContourSize = (gWidth*gHeigth)/3;
        contourFinder.findContours(grayDiff, contourSize, maxContourSize, contourTot, true);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    if(sceneId == 0){
       colorImg.draw(0,0);
    }
    if(sceneId == 1){
        grayDiff.draw(0,0);
    }
    if(sceneId == 2){
        contourFinder.draw(0,0);
    }

    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //ofLog() << key;
    if(key == '1'){
        sceneId = 1;
    }
    if(key == '0'){
        sceneId = 0;
    }
    if(key == '2'){
        sceneId = 2;
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
