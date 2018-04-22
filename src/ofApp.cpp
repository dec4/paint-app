#include "ofApp.h"


void ofApp::setup() {
	all_lines_.setMode(ofPath::POLYLINES);
	ofColor black(0,0,0);  // -------------- DELETE LATER
	all_lines_.setStrokeColor((*gui).getColor());  // -- REPLACE WITH COLOR FROM TOOLGUI 
	all_lines_.setFilled(false);  // ------- KEEP
	all_lines_.setStrokeWidth((*gui).getRadius());  // ------ REPLACE WITH RADIUS FROM TOOLGUI
	all_lines_.setCurveResolution(500); //-- replace later??
	all_lines_.newSubPath();
}

void ofApp::update() {
	// updates based on toolgui
	all_lines_.setStrokeColor( (*gui).getColor() );
	all_lines_.setStrokeWidth( ((*gui).getRadius())*2 );
}

void ofApp::draw() {
	all_lines_.draw();
}

void ofApp::mousePressed(int x, int y, int button) {
	ofPoint pt;
	pt.set(x,y);

	if (!drawing) {
		drawing = true;
		all_lines_.lineTo(pt);
	} else {
		drawing = false;
		all_lines_.lineTo(pt);
		all_lines_.newSubPath();
	}
}

void ofApp::mouseMoved(int x, int y ) {	
	if (!drawing) {
		return;
	} else {
		ofPoint pt;
		pt.set(x,y);
		all_lines_.lineTo(pt);
	}
}

void ofApp::mouseExited(int x, int y) {
	if (!drawing) {
		return;
	} else {
		drawing = false;
		ofPoint pt;
		pt.set(x,y);
		all_lines_.lineTo(pt);
		all_lines_.newSubPath();
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