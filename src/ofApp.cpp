#include "ofApp.h"


void ofApp::setup() {
    // Using sliders (see .h)
	//parameters.add(radius.set("radius", 50, 1, 100));
	//parameters.add(color.setHsb("color (hsba)", 100, 200, 100, 255));
    // compare to rsb: parameters.add(color.set("color",100,ofColor(0,0),255));
    //gui.setup(parameters);
    // NOTE: USE PARAMETERS IF CREATE OWN HSBACOLOR OBJECT
    // ^SAME FOR DRAWING TOOL?

    gui_.setup();   
    gui_.add(radius_.setup("radius", 140, 10, 150));
    gui_.add(hue_.setup("hue", 140, 0, 255));
    gui_.add(saturation_.setup("saturation", 200, 0, 255));
    gui_.add(brightness_.setup("brightness", 140, 0, 255));
    gui_.add(alpha_.setup("alpha", 200, 0, 255));


    // Add listener (below) to all tools then add method so that if tool changes, 
    // all other tools are disabled.
    // ex: circleResolution.addListener(this, &ofApp::circleResolutionChanged);
    // and use myToggle.set(false);
    gui_.add(pencil_.setup("pencil", true));
    gui_.add(pen_.setup("pen", false));
    gui_.add(highlighter_.setup("highlighter", false));
    gui_.add(eraser_.setup("eraser", false));

    ofBackground(background_);

}

void ofApp::update() {
    updateColor();
    updateTool();
}

void ofApp::draw() {
    ofSetColor(color_);
    ofDrawCircle((5*ofGetWidth())/8, ofGetHeight()/2, radius_);
	gui_.draw();
}

void ofApp::updateColor() {
    color_.setHsb(hue_, saturation_, brightness_, alpha_);
}

void ofApp::updateTool() {
    
}

/* STARTER CODE

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

*/