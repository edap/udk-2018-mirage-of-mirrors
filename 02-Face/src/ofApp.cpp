#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    camWidth = 320;  // try to grab at this size.
    camHeight = 240;

    //sub selection part
    subSelWidth = 100;
    subSelHeight = 100;
    fbo.allocate(subSelWidth, subSelHeight);
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();

    // set the plane on which the texture will be binded
    videoTexture.allocate(camWidth, camHeight, GL_RGBA);
    plane.set(camWidth, camHeight, 2, 2);
    plane.setPosition(glm::vec3(40+camWidth/2, 500, 1));
    plane.mapTexCoords(0, 0, camWidth, camHeight);

    // se the sphere
    sphere.set(100, 32);
    sphere.setPosition(glm::vec3(480, -150, 1));
    sphere.mapTexCoords(0, 0, camWidth, camHeight);

    // Camera grabbing
    //get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();

    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            //log the device
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            //log the device and note it as unavailable
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }

    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.initGrabber(camWidth, camHeight);

    ofSetVerticalSync(true);
}


//--------------------------------------------------------------
void ofApp::update(){
    //plane.rotateDeg(0.3, glm::vec3(0,0,1));
    sphere.rotateDeg(1., glm::vec3(0,1,0));

    ofBackground(180, 200, 50);
    vidGrabber.update();

    if(vidGrabber.isFrameNew()){
        ofPixels & pixels = vidGrabber.getPixels();
        videoTexture.loadData(pixels);
    }

    // prepare a subselection
    fbo.begin();
    ofClear(255,255,255, 0);
    // have a look at the doc of drawSubsection
    videoTexture.drawSubsection(0, 0, subSelWidth, subSelHeight, mouseX, mouseY);
    ofPopStyle();
    fbo.end();

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetHexColor(0xffffff);

    // draw the camera output
    vidGrabber.draw(vidGrabber.getWidth(), 0, -vidGrabber.getWidth(), vidGrabber.getHeight());
    // try to uncomment this line and move your head from
    // left to right, did you noticed something?
    // vidGrabber.draw(0, 0, vidGrabber.getWidth(), vidGrabber.getHeight());

    // flip the image vertically
    // vidGrabber.draw(0, vidGrabber.getHeight(), vidGrabber.getWidth(), -vidGrabber.getHeight());

    // draw the texture on the geometry
    videoTexture.bind();
    plane.draw();
    videoTexture.unbind();

    // draw a subselection
    auto t = fbo.getTexture();
    t.draw(600, 520, subSelWidth, subSelHeight);

    // texture on a 3d object
    cam.begin();
    ofEnableDepthTest();
    videoTexture.bind();
    sphere.draw();
    videoTexture.unbind();
    ofDisableDepthTest();
    cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
