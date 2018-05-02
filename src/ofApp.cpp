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

	// Set up fonts for start and end display
	SetupStart();
	SetupEnd();

	// Set up instructions stringstream
	SetupInstructions();

	// Set up help icon
	help_button_.load("Condition.ttf", 16, true, true, true);

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
	switch (current_display_) {
		case START:
			DrawStart();
			break;
		case FREE:
			DrawFree();
			break;
		case TIMED:
			DrawTimed();
			break;
		case TIMED_END:
			DrawTimedEnd();
			break;
		case FREE_END:
			DrawFreeEnd();
			break;
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

	// Different displays have different results when clicked

	if (current_display_ == START) {
		PressedInStart(pt);
		return;
	}

	if (current_display_ == TIMED_END) {
		PressedInTimedEnd(pt);
		return;
	}

	if (current_display_ == FREE_END) {
		PressedInFreeEnd(pt);
		return;
	}

	// If not START, TIMED_END, or FREE_END, then use original code 
	// for drawing on plain canvas

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
	// If current_display_ is not TIMED or FREE, then don't save 
	// Either it should already be saved, or it's the start 
	// screen and there's nothing to save
	// Change state to saved display
	if (current_display_ == TIMED) {
		current_display_ = TIMED_END;
	} else if (current_display_ == FREE) {
		current_display_ = FREE_END;
	} else {
		return;
	}

	time_to_complete_ = ofGetElapsedTimef();

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
	std::string default_filename = "savedimages/img" + ofGetTimestampString("%m-%d-%H-%M-%S-%i") + ".png"; 
    ofSaveImage(pixels, default_filename, OF_IMAGE_QUALITY_BEST);
		// NOTE: wanted to change quality but then there's a warning that says 
		// ofImageCompressionType only applies to JPEGs, but OF documentation 
		// for ofSaveImage() implies you can use it with png ???

	// Put back question mark
	print_q = true;

	// Now that image is saved, allow reset buttons to show
	draw_reset_buttons_ = true;
}

/**
 * Exit method: changes display to START, essentially resetting app.
 */
void ofApp::ResetToStart() {
	ClearCanvas();
	ClearUndoHistory();
	current_display_ = START;
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



/**
 * NOTE: everything below this point is an addition to original project proposal
 * (plus some code integrated above is a part of this)
 */


//----- SETUP METHODS -----//

/**
 * Set up ofTrueTypeFont objects for Start display.
 */
void ofApp::SetupStart() {
	welcome_.load("Condition.ttf", 52, true, true, true);
	choose_mode_.load("Condition.ttf", 52, true, true, true);
	time_.load("Condition.ttf", 35, true, true, true);
	free_.load("Condition.ttf", 35, true, true, true);
}

/**
 * Set up ofTrueTypeFont objects for End displays.
 */
void ofApp::SetupEnd() {
	restart_.load("Condition.ttf", 52, true, true, true);
	draw_more_.load("Condition.ttf", 52, true, true, true);
	image_saved_.load("Condition.ttf", 35, true, true, true);
}


//----- START DISPLAY METHODS -----//	

/**
 * Draw Start display (text and click zones).
 */
void ofApp::DrawStart() {
	(background_.getLightness() > 130) ? ofSetColor(0) : ofSetColor(255);
	welcome_.drawString("WELCOME!", canvas_width_/2 - (welcome_.stringWidth("WELCOME!")/2), canvas_height_/4);
	choose_mode_.drawString("CHOOSE MODE!", canvas_width_/2 - (choose_mode_.stringWidth("CHOOSE MODE!")/2), canvas_height_*((float)3/4));
	ofSetColor(153, 0, 76);
	time_.drawString("TIMED", canvas_width_*((float)1/4) - (time_.stringWidth("TIMED")/2), canvas_height_/2);
	time_click_zone_ = time_.getStringBoundingBox("TIMED", canvas_width_*((float)1/4) - (time_.stringWidth("TIMED")/2), canvas_height_/2);
	ofSetColor(0, 153, 153);
	free_.drawString("FREE", canvas_width_*((float)3/4) - (free_.stringWidth("FREE")/2), canvas_height_/2);
	free_click_zone_ = free_.getStringBoundingBox("FREE", canvas_width_*((float)3/4) - (free_.stringWidth("FREE")/2), canvas_height_/2);
}

/**
 * Acts as a listener method to determine what to do when mouse is clicked.
 */
void ofApp::PressedInStart(ofPoint& point) {
	if (time_click_zone_.inside(point)) {
		random_noun_ = RandomNoun();
		ofResetElapsedTimeCounter();
		current_display_ = TIMED;
	} else if (free_click_zone_.inside(point)) {
		current_display_ = FREE;
	}
}


//----- FREE DISPLAY METHODS -----//

/**
 * Draw Free display; acts like original draw on simple canvas.
 */
void ofApp::DrawFree() {
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


//----- TIMED DISPLAY METHODS -----//

/**
 * Draw Free display; acts like original draw on simple canvas with the addition of
 * a rectangle at the bottom with random noun prompt and timer.
 */
void ofApp::DrawTimed() {
	// Draw canvas
	DrawFree();
	// Draw rectangle at bottom
	ofSetColor(200);
	ofFill();
	ofDrawRectangle(0, 0.94*canvas_height_, canvas_width_, canvas_height_ - 0.94*canvas_height_);
	ofSetColor(0);
	ofDrawBitmapString("Your word is " + random_noun_.GetWord(), 0.1*canvas_width_, 0.98*canvas_height_);
	// float -> string doesn't work, so I'm using stringstream for text
	std::ostringstream temp_stream;
	temp_stream << ofGetElapsedTimef();
	std::string time_string(temp_stream.str());
	ofDrawBitmapString("Timer : " + time_string, 0.8*canvas_width_, 0.98*canvas_height_);
}

// Initialize new random_noun_
void ofApp::SetupRandomNoun() {
	random_noun_ = RandomNoun();	
}


//----- TIMED_END DISPLAY METHODS -----//

/**
 * Draw End display for Timed mode.
 */
void ofApp::DrawTimedEnd() {
	// Draw Canvas
	DrawFree();
	// Draw rectangle at bottom
	ofSetColor(200);
	ofFill();
	ofDrawRectangle(0, 0.94*canvas_height_, canvas_width_, canvas_height_ - 0.94*canvas_height_);
	ofSetColor(0);
	// float -> string doesn't work, so I'm using stringstream to print text
	std::ostringstream temp_stream;
	temp_stream << time_to_complete_;
	std::string time_string(temp_stream.str());
	std::string finished_message = "You drew a(n) " + random_noun_.GetWord() + " in " + time_string + " sec";
	ofDrawBitmapString(finished_message, 0.3*canvas_width_, 0.98*canvas_height_);
	// Check first so that reset buttons don't appear on saved image
	if (draw_reset_buttons_) {
		DrawRestart();
		DrawImageSaved();
	}
}

/**
 * Determines next action when mouse is clicked in TIMED_END display.
 */
void ofApp::PressedInTimedEnd(ofPoint& point) {
	if (restart_click_zone_.inside(point)) {
		// Reset to false until image is saved again
		draw_reset_buttons_ = false;
		// Clear everything and change display to START
		ResetToStart();
	}
}


//----- FREE_END DISPLAY -----//

/**
 * Draw End display for Free mode.
 */
void ofApp::DrawFreeEnd() {
	DrawFree();
	if (draw_reset_buttons_) {
		DrawRestart();
		DrawImageSaved();
		DrawDrawMore();
	}
}

/**
 * Determines next action when mouse is clicked in FREE_END display.
 */
void ofApp::PressedInFreeEnd(ofPoint& point) {
	if (restart_click_zone_.inside(point)) {
		// Reset to false until image is saved again
		draw_reset_buttons_ = false;
		// Clear everything and change display to START
		ResetToStart();
	} else if (draw_more_click_zone_.inside(point)) {
		// Reset to false until image is saved again
		draw_reset_buttons_ = false;
		// Go back to drawing on same canvas (does not clear)
		current_display_ = FREE;
	}
}


//----- USED IN BOTH END DISPLAYS -----//

/**
 * Draws text "IMAGE SAVED!".
 */
void ofApp::DrawImageSaved() {
	(background_.getLightness() > 130) ? ofSetColor(0) : ofSetColor(255);
	image_saved_.drawString("IMAGE SAVED!", canvas_width_/2 - (image_saved_.stringWidth("IMAGE SAVED!")/2), canvas_height_/2);
}

/**
 * Draws text "RESTART".
 */
void ofApp::DrawRestart() {
	ofSetColor(153, 0, 76);
	restart_.drawString("RESTART", canvas_width_/2 - (restart_.stringWidth("RESTART")/2), canvas_height_*((float)3/4));
	restart_click_zone_ = restart_.getStringBoundingBox("RESTART", canvas_width_/2 - (restart_.stringWidth("RESTART")/2), canvas_height_*((float)3/4));
}

/**
 * Draws text "DRAW MORE".
 */
void ofApp::DrawDrawMore() {
	ofSetColor(0, 153, 153);
	draw_more_.drawString("DRAW MORE", canvas_width_/2 - (draw_more_.stringWidth("DRAW MORE")/2), canvas_height_*((float)1/4));
	draw_more_click_zone_ = draw_more_.getStringBoundingBox("DRAW MORE", canvas_width_/2 - (draw_more_.stringWidth("DRAW MORE")/2), canvas_height_*((float)1/4));
}

