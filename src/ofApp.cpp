#include "ofApp.h"
#include <sstream>
#include <iostream>


//----- MAIN OPENFRAMEWORKS LOOP -----//

void ofApp::setup() {
	// Set Background Color
	ofBackground(background_);

	// Store width and height of canvas
	canvas_width_ = ofGetWidth();
	canvas_height_ = ofGetHeight();

	// Set up instructions stringstream
	SetupInstructions();

	// Set up help icon
	help_button_.load("cooperBlack.ttf", 12, true, true, true);
}

void ofApp::update() {	
	// Update Background
	ofBackground(background_);

	// Update location of help click zone
	// Necessary because window size may change
	// Need point because of ofRectangle parameter
	ofPoint pt;
	pt.set(canvas_width_-30, 0);
	help_click_zone_ = ofRectangle(pt, 20, 20);
}

void ofApp::draw() {
	// Print instructions; returns when done so that drawing does not block words
	if (print_instructions_) {
		// Depending on background lightness, make text white or black for readability
		(background_.getLightness() > 130) ? ofSetColor(0) : ofSetColor(255);
		ofDrawBitmapString(instructions_.str(), 20, 20);
		return;
	}

	// Draw lines on canvas
	for (auto line : canvas_lines_) {
		DrawLine(*line);
	}
	// Draw current_line_ separately because each line is not added 
	// to canvas_lines_ until user is finished drawing
	if (drawing) {
		DrawLine(*current_line_);
	}

	// Even though the question mark will always be visible while using the app, this
	// section is controlled by a boolean so that it does not draw on saved image
	if (print_q) {
		// Depending on background lightness, make text white or black for readability
		(background_.getLightness() > 130) ? ofSetColor(0) : ofSetColor(255);
		ofFill();
		help_button_.drawString("?", canvas_width_-20, 20);
		ofNoFill();
	}
}


//----- OTHER OPENFRAMEWORKS METHODS -----//

/**
 * Possible actions when mouse is pressed:
 * 1) Start drawing
 * 2) End drawing
 * 3) Print instructions if clicked help icon
 * 4) Stop printing instructions (go back to canvas)
 */
void ofApp::mousePressed(int x, int y, int button) {
	// Get point of click
	ofPoint pt;
	pt.set(x,y);

	// If instructions are still being drawn, stop on click press
	// return so that it doesn't start drawing a line
	if (print_instructions_) {
		print_instructions_ = false;
		return;
	}

	// Draw instructions if clicked on help icon
	if (!drawing && help_click_zone_.inside(pt)) {
		print_instructions_ = true;
		return;
	}

	// Create new line if not already drawing
	else if (!drawing) { 
		drawing = true;
		redo_allowed_ = false; // Can't redo if there's nothing to redo
		ofColor color = (*tools).GetColor();
		float radius = (*tools).GetRadius();
		current_line_ = new AppLine(pt, color, radius);
		ClearUndoHistory();
	}
	// Add to current line if drawing
	else { 
		current_line_->AddPoint(pt);
		canvas_lines_.push_back(current_line_); 
		current_line_ = nullptr;
		drawing = false;
	}
}

/**
 * Track mouse movement; only matters if drawing.
 */
void ofApp::mouseMoved(int x, int y ) {	
	// Only matters if drawing
	if (drawing) {
		ofPoint pt;
		pt.set(x,y);
		current_line_->AddPoint(pt);
	} 
}

/**
 * Use bounded_ to determine action upon exit; only matters if drawing.
 */
void ofApp::mouseExited(int x, int y) {
	if (drawing) {
		ofPoint pt;
		pt.set(x,y);
		current_line_->AddPoint(pt);
		// Determine whether or not to end line upon exit
		if (bounded_) {
			canvas_lines_.push_back(current_line_); 
			drawing = false;
		}
	}
}

/**
 * Update variables that store window size
 */
void ofApp::windowResized(int w, int h) {
	canvas_width_ = w;
	canvas_height_ = h;
}

/**
 * Used for keyboard shortcuts.
 * Contains shortcuts for ACTIONS only (not settings)
 */
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


//----- MY METHODS -----//

/**
 * Helper method to draw (display) a line on canvas.
 */
void ofApp::DrawLine(AppLine& line) {
	float width = line.GetWidth();
	ofSetColor(line.GetColor());
	ofSetLineWidth(width);
	(line.GetLine()).draw();
}

/**
 * Clears (i.e. erases) the whole canvas.
 * NOTE: due to limitations of objects and design, 
 * this will NOT be able to be undone
 */
void ofApp::ClearCanvas() {
	while (!canvas_lines_.empty()) {
		delete canvas_lines_.back();
		canvas_lines_.pop_back();
	}
	ClearUndoHistory();
}

/**
 * Helper method to clear the lines in redo_lines_.
 * Prevents lines from being saved after they're overwritten
 */
void ofApp::ClearUndoHistory() {
	while (!redo_lines_.empty()) {
		delete redo_lines_.top();
		redo_lines_.pop();
	}
}

/**
 * Undo method: moves top line from canvas_lines_ to redo_lines_.
 */
void ofApp::Undo() {
	if (canvas_lines_.empty()) {
		return;
	}
	auto temp = canvas_lines_.back();
	canvas_lines_.pop_back();
	redo_lines_.push(temp);
	redo_allowed_ = true;  // Can only redo if something has been undone
}

/**
 * Redo method: moves top line from redo_lines_ to canvas_lines_.
 */
void ofApp::Redo() {
	if (redo_allowed_ && !(redo_lines_.empty())) {
		auto temp = redo_lines_.top();
		redo_lines_.pop();
		canvas_lines_.push_back(temp);
	}
}

/**
 * Save method: draws to frame buffer (fbo), then saves pixels from fbo.
 * Help reference:
 * https://forum.openframeworks.cc/t/saving-a-fbo-to-an-image/10747
 * https://forum.openframeworks.cc/t/ofxfenster-addon-to-handle-multiple-windows-rewrite/6499/60
 */
void ofApp::SaveImage() {
	// Don't save with question mark
	// Need boolean because draw() is called for fbo
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
    // Save (using timestamp for unique filename)
	std::string default_filename = "img" + ofGetTimestampString("%m-%d-%H-%M-%S-%i") + ".png"; 
    ofSaveImage(pixels, default_filename, OF_IMAGE_QUALITY_BEST);
		// NOTE: wanted to change quality but then there's a warning that says 
		// ofImageCompressionType only applies to JPEGs, but OF documentation 
		// for ofSaveImage() implies you can use it with png ???
	
	// Print save message in toolgui
	ofResetElapsedTimeCounter();
	print_save_message_ = true;

	// Put back question mark
	print_q = true;
}

/**
 * Used to set up the instructions.
 * Note: tried to just initialize string, but it wasn't compiling, so this 
 * uses a stringstream
 */
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
	instructions_ << "bounded: determines whether or not the line will" << std::endl;
	instructions_ << "end once the mouse exits the canvas window" << std::endl << std::endl;
	instructions_ << "set background color: changes background color of canvas to the" << std::endl;
	instructions_ << "current hsb settings in the tool panel (alpha = 255)" << std::endl << std::endl;
	instructions_ << "Keyboard shortcuts available (see tools panel for keys):" << std::endl;
	instructions_ << "clear, undo, redo, save" << std::endl << std::endl;
	instructions_ << "Some Notes:" << std::endl;
	instructions_ << "-clear canvas CANNOT be undone!" << std::endl;
	instructions_ << " Likewise, when you overwrite something that has" << std::endl;
	instructions_ << " been undone, you cannot redo it!" << std::endl;
	instructions_ << "-Resizing the window resizes the canvas" << std::endl << std::endl;
	instructions_ << "Click to close instructions.";
}