#include "ofApp.h"


void ofApp::setup() {
	ofBackground(background_);  // Set background color
	canvas_width_ = ofGetWidth();
	canvas_height_ = ofGetHeight();
}

void ofApp::update() {	

}

void ofApp::draw() {
	DrawCanvas();
	if (drawing) {  // Draw current line since it hasn't been added to canvas_lines_ yet
		ofSetColor(current_line_->GetColor());
		ofSetLineWidth(current_line_->GetWidth());
		(current_line_->GetLine()).draw();
	}
}

void ofApp::mousePressed(int x, int y, int button) {
	ofPoint pt;
	pt.set(x,y);

	if (!drawing) {  // Create new line
		drawing = true;
		redo_allowed_ = false;
		ofColor color = (*tools).GetColor();
		float radius = (*tools).GetRadius();
		current_line_ = new AppLine(pt, color, radius);
		ClearUndoHistory();
	} else {  // Add to current line
		current_line_->AddPoint(pt);
		canvas_lines_.push_back(current_line_); 
		current_line_ = nullptr;
		drawing = false;
	}
}

void ofApp::mouseMoved(int x, int y ) {	
	if (drawing) {
		ofPoint pt;
		pt.set(x,y);
		current_line_->AddPoint(pt);
	}
}

void ofApp::mouseExited(int x, int y) {
	if (drawing) {
		ofPoint pt;
		pt.set(x,y);
		current_line_->AddPoint(pt);
		canvas_lines_.push_back(current_line_); 
		drawing = false;
	}
}

void ofApp::DrawCanvas() {
	for (auto line : canvas_lines_) {
		ofSetColor(line->GetColor());
		ofSetLineWidth(line->GetWidth());
		(line->GetLine()).draw();
	}
}

void ofApp::ClearCanvas() {
	// NOTE due to limitations of objects and design, this will NOT be able to be undone
	while (!canvas_lines_.empty()) {
		delete canvas_lines_.back();
		canvas_lines_.pop_back();
	}
	ClearUndoHistory();
}

void ofApp::ClearUndoHistory() {
	while (!redo_lines_.empty()) {
		delete redo_lines_.top();
		redo_lines_.pop();
	}
}

void ofApp::Undo() {
	if (canvas_lines_.empty()) {
		return;
	}
	auto temp = canvas_lines_.back();
	canvas_lines_.pop_back();
	redo_lines_.push(temp);
	redo_allowed_ = true;
}

void ofApp::Redo() {
	if (redo_allowed_ && !(redo_lines_.empty())) {
		auto temp = redo_lines_.top();
		redo_lines_.pop();
		canvas_lines_.push_back(temp);
	}
}

void ofApp::keyPressed(int key) {
	int upper_key = toupper(key);

	if (upper_key == 'C') {
		ClearCanvas();
	}
	else if (upper_key == 'U') {
		Undo();
	}
	else if (upper_key == 'R') {
		Redo();
	}
	else if (upper_key == 'S') {
		SaveImage();
	}
}

// https://forum.openframeworks.cc/t/saving-a-fbo-to-an-image/10747
// https://forum.openframeworks.cc/t/ofxfenster-addon-to-handle-multiple-windows-rewrite/6499/60
void ofApp::SaveImage() {
	// Create fbo
	canvas_fbo_.allocate(canvas_width_, canvas_height_, GL_RGBA);
	canvas_fbo_.begin();
		ofBackground(background_);
		draw();
	canvas_fbo_.end();
	// Get the frame buffer pixels  
	ofPixels pixels;
    canvas_fbo_.readToPixels(pixels);
    // Save  
	std::string default_filename = "img" + ofGetTimestampString("%m-%d-%H-%M-%S-%i") + ".png"; 
    ofSaveImage(pixels, default_filename, OF_IMAGE_QUALITY_BEST); 
	// Print save message in toolgui
	ofResetElapsedTimeCounter();
	print_save_message_ = true;
}

void ofApp::windowResized(int w, int h) {
	canvas_width_ = w;
	canvas_height_ = h;
}