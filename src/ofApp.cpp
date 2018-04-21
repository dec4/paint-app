#include "ofApp.h"


void ofApp::setup() {
	all_lines_.setMode(ofPath::POLYLINES);
	all_lines_.newSubPath();
}

void ofApp::update() {

}

void ofApp::draw() {
	all_lines_.draw();
}

void ofApp::mousePressed(int x, int y, int button) {
	if (!drawing) {
		drawing = true;

		ofPoint pt;
		pt.set(x,y);
		all_lines_.lineTo(pt);
	} else {
		drawing = false;
		all_lines_.close();
	}
}

void ofApp::mouseMoved(int x, int y ){
	if (!drawing) {
		return;
	} else {
		ofPoint pt;
		pt.set(x,y);
		all_lines_.lineTo(pt);
	}
}


/* STARTER CODE

//--------------------------------------------------------------
void ToolGui::setup(){

}

//--------------------------------------------------------------
void ToolGui::update(){

}

//--------------------------------------------------------------
void ToolGui::draw(){

}

//--------------------------------------------------------------
void ToolGui::keyPressed(int key){

}

//--------------------------------------------------------------
void ToolGui::keyReleased(int key){

}

//--------------------------------------------------------------
void ToolGui::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ToolGui::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ToolGui::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ToolGui::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ToolGui::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ToolGui::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ToolGui::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ToolGui::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ToolGui::dragEvent(ofDragInfo dragInfo){ 

}

*/