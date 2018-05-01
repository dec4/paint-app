#include "ofApp.h"
#include <sstream>
#include <iostream>



//*** OPENFRAMEWORKS METHODS ***/

void ofApp::setup() {
	ofBackground(background_);  // Set background color
	canvas_width_ = ofGetWidth();
	canvas_height_ = ofGetHeight();

	// Get point for instructions_icon_ position
	//ofPoint pt;
	//pt.set(canvas_width_-20, 0);
	//instructions_icon_ = ofRectangle(pt, 20, 20);
	SetupInstructions();
	help_button_.load("cooperBlack.ttf", 12, true, true, true);
}

void ofApp::update() {	
	ofBackground(background_);
	ofPoint pt;
	pt.set(canvas_width_-30, 0);
	instructions_icon_ = ofRectangle(pt, 20, 20);
}

void ofApp::draw() {
	if (print_q) {
		//ofSetColor(0,0,0);
		//ofDrawBitmapString("?", canvas_width_-20, 20);
		//ofSetColor(255);
		//ofEnableAlphaBlending();
		//qmark.draw(canvas_width_/2, canvas_height_/2);
		//ofDisableAlphaBlending();
		ofSetColor(0);
		ofFill();
		help_button_.drawString("?", canvas_width_-20, 20);
	}
	if (print_instructions_) {
		ofSetColor(0);
		ofDrawBitmapString(instructions_.str(), 20, 20);
		return;
	}

	DrawCanvas();
	if (drawing) {  // Draw current line since it hasn't been added to canvas_lines_ yet
		float width = current_line_->GetWidth();
		ofSetColor(current_line_->GetColor());
		ofSetLineWidth(width);
		(current_line_->GetLine()).draw();
		/*
		if (current_line_->IsThick()) {
			ofTranslate(-width/2, -width/2);
			(current_line_->GetLine()).draw();
			ofTranslate(width, width);
			(current_line_->GetLine()).draw();
		}
		*/
	}
}

void ofApp::mousePressed(int x, int y, int button) {
	ofPoint pt;
	pt.set(x,y);

	// If instructions are still being drawn, stop
	if (print_instructions_) {
		print_instructions_ = false;
		return;
	}

	if (!drawing && instructions_icon_.inside(pt)) {
		print_instructions_ = true;
		return;
	}
	// Create new line
	else if (!drawing) { 
		drawing = true;
		redo_allowed_ = false;
		ofColor color = (*tools).GetColor();
		float radius = (*tools).GetRadius();
		current_line_ = new AppLine(pt, color, radius, thicken_);
		ClearUndoHistory();
	}
	// Add to current line
	else { 
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
		if (bounded_) {
			canvas_lines_.push_back(current_line_); 
			drawing = false;
		}
	}
}

void ofApp::windowResized(int w, int h) {
	canvas_width_ = w;
	canvas_height_ = h;
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


//*** MY METHODS ***//

void ofApp::DrawCanvas() {
	for (auto line : canvas_lines_) {
		float width = line->GetWidth();
		ofSetColor(line->GetColor());
		ofSetLineWidth(width);
		(line->GetLine()).draw();
		/*
		if (line->IsThick()) {
			ofTranslate(-width/2, -width/2);
			(current_line_->GetLine()).draw();
			ofTranslate(width, width);
			(current_line_->GetLine()).draw();
		}
		*/
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

// https://forum.openframeworks.cc/t/saving-a-fbo-to-an-image/10747
// https://forum.openframeworks.cc/t/ofxfenster-addon-to-handle-multiple-windows-rewrite/6499/60
void ofApp::SaveImage() {
	// Don't save with question mark
	print_q = false;

	// Create fbo
	canvas_fbo_.allocate(canvas_width_, canvas_height_, GL_RGB);
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
		// NOTE: warning says ofImageCompressionType says only applies to JPEGs, 
		// but OF documentation for ofSaveImage() implies you can use it with png ???
		// (so instead saves with default: OF_IMAGE_QUALITY_BEST)
	// Print save message in toolgui
	ofResetElapsedTimeCounter();
	print_save_message_ = true;

	// Put back question mark
	print_q = true;
}

void ofApp::SetupInstructions() {
	instructions_ << "DRAWING INSTRUCTIONS:" << std::endl << std::endl;
	instructions_ << "1) Click once to put down pen" << std::endl;
	instructions_ << "2) Move mouse to draw" << std::endl;
	instructions_ << "3) Click once more to pick up pen (stop drawing)" << std::endl;
	instructions_ << "Want straight lines? Try clicking and dragging!" << std::endl << std::endl;
	instructions_ << "Use the tools panel to change color, size, and more!" << std::endl << std::endl;
	instructions_ << "Changeable parameters for each tool:" << std::endl;
	instructions_ << "pen: hue, saturation, brightness, and alpha" << std::endl;
	instructions_ << "pencil: brightness, alpha" << std::endl;
	instructions_ << "eraser: alpha" << std::endl << std::endl;
	instructions_ << "'bounded' determines whether or not the line will" << std::endl;
	instructions_ << "end once the mouse exits the canvas window" << std::endl << std::endl;
	instructions_ << "Keyboard shortcuts available (see tools panel for keys):" << std::endl;
	instructions_ << "clear, undo, redo, save" << std::endl << std::endl;
	instructions_ << "Some Notes:" << std::endl;
	instructions_ << "-clear canvas CANNOT be undone!" << std::endl;
	instructions_ << " Likewise, when you overwrite something that has" << std::endl;
	instructions_ << " been undone, you cannot redo it!" << std::endl;
	instructions_ << "-Resizing the window resizes the canvas" << std::endl << std::endl;
	instructions_ << "Click to close instructions.";
}