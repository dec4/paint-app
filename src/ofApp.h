#pragma once

#include "ofMain.h"
#include "toolgui.h"
#include "appline.h"
#include <stack>
#include <vector>
#include <string>
#include <sstream>

class ToolGui;

class ofApp : public ofBaseApp {
public:
	// Main OpenFrameworks loop
	void setup();
	void update();
	void draw();

	// Store window size in variables
	void windowResized(int w, int h);
	int canvas_width_;
	int canvas_height_;

	// Store background color
	ofColor background_ = ofColor(255, 255, 255);

	// Pointer to app in tool gui window
	shared_ptr<ToolGui> tools;
 
	// Line storage variaables
	std::vector<AppLine*> canvas_lines_; //--- Lines currently on canvas (drawn)
	std::stack<AppLine*> redo_lines_; //------ Recently undone lines (not drawn)
											// Note: clears when new lines are drawn because
											// it overwrites recently undone lines
	AppLine* current_line_; //---------------- Pointer to current line being drawn

	// Track drawing state
	bool drawing = false;

	// Helper function to draw a line to canvas
	void DrawLine(AppLine&);

	// Click once to put down pen, move to draw, click again to release
	void mousePressed(int x, int y, int button);
	void mouseMoved(int x, int y );
	void mouseExited(int x, int y);  // Depending on bounded_, line ends if mouse goes out of window

	// ToolGui actions
	void ClearCanvas();
	void ClearUndoHistory();
	void Undo();
	void Redo();
	bool redo_allowed_ = false;  // Can't redo something that was overwritten

	// For keyboard shortcuts
	// Shortcuts for actions only (clear, undo, redo, save)
	void keyPressed(int key);

	// Determines whether or not to end line when mouse exits window
	bool bounded_ = true;

	// For saving image to file:
	ofFbo canvas_fbo_;
	bool print_save_message_ = false;
	void SaveImage();

	// For printing drawing instructions:
	void SetupInstructions(); //---------- Set up instructions stringstream
										// Tried hard coding string, but it wasn't working...
	ostringstream instructions_; //------- Stringstream of instructions
	ofTrueTypeFont help_button_; //------- "?"
	ofRectangle help_click_zone_; //------ Area that when clicked inside, draws instructions
	bool print_instructions_ = false; //-- Determine whether or not to print instructions
	bool print_q = true; //--------------- Determine whether or not to print ICON ("?")
};