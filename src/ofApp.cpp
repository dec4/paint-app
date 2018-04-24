#include "ofApp.h"


void ofApp::setup() {
	//current_line_ = new AppLine();
}

void ofApp::update() {	

}

void ofApp::draw() {
	drawCanvas();
	// Draw current line since it is not added to canvas_lines_ yet
	if (drawing) {
		ofSetColor(current_line_->getColor());
		ofSetLineWidth(current_line_->getWidth());
		(current_line_->getLine()).draw();
	}
}

void ofApp::mousePressed(int x, int y, int button) {
	// when mouse is pressed, record color and radius
	ofPoint pt;
	pt.set(x,y);

	if (!drawing) {
		drawing = true;
		ofColor color = (*gui).getColor();
		int radius = (*gui).getRadius();
		current_line_ = new AppLine(pt, color, radius);
	} else {
		current_line_->add_point(pt);
		canvas_lines_.push_back(*current_line_); 
		current_line_ = nullptr;
		drawing = false;
	}
}

void ofApp::mouseMoved(int x, int y ) {	
	if (!drawing) {
		return;
	} else {
		ofPoint pt;
		pt.set(x,y);
		current_line_->add_point(pt);
	}
}

void ofApp::mouseExited(int x, int y) {
	if (!drawing) {
		return;
	} else {
		ofPoint pt;
		pt.set(x,y);
		current_line_->add_point(pt);
		canvas_lines_.push_back(*current_line_); 
		drawing = false;
	}
}

void ofApp::drawCanvas() {
	for (auto line : canvas_lines_) {
		ofSetColor(line.getColor());
		ofSetLineWidth(line.getWidth());
		(line.getLine()).draw();
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