#pragma once

#include "ofMain.h"
#include "toolgui.h"
#include "appline.h"
#include "randomnoun.h"
#include <stack>
#include <vector>
#include <string>
#include <sstream>

class ToolGui;

class ofApp : public ofBaseApp {

	// enum to track which screen to draw
	// Note: difference between TIMED and FREE
	//	TIMED: generates random noun and times how long you take to draw it
	//	FREE: same drawing canvas, no time, no prompt
	enum DisplayMode {
		START,
		TIMED,
		FREE,
		TIMED_END,
		FREE_END
	};

	// Track current display mode
	DisplayMode current_display_ = START;

public:
	// Main OpenFrameworks loop
	void setup();
	void update();
	void draw();

	// Store window size in variables
	void windowResized(int w, int h);
	float canvas_width_;
	float canvas_height_;

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
	// Shortcuts for actions only
	// clear (c), undo (u), redo (r), save (s)
	void keyPressed(int key);

	// Determines whether or not to end line when mouse exits window
	bool bounded_ = true;

	// For saving image to file:
	ofFbo canvas_fbo_;
	void SaveImage();

	// For printing drawing instructions:
	void SetupInstructions(); //---------- Set up instructions stringstream
										// Tried hard coding string, but it wasn't working...
	ostringstream instructions_; //------- Stringstream of instructions
	ofTrueTypeFont help_button_; //------- "?"
	ofRectangle help_click_zone_; //------ Area that when clicked inside, draws instructions
	bool print_instructions_ = false; //-- Determine whether or not to print instructions
	bool print_q = true; //--------------- Determine whether or not to print ICON ("?")



	/**
	 * NOTE: everything below this point is an addition to original project proposal
	 */


	// SetupStart allocates and loads font info for the text being displayed in START
	void SetupStart();
	ofTrueTypeFont welcome_;
	ofTrueTypeFont choose_mode_;
	ofTrueTypeFont time_;
	ofTrueTypeFont free_;
	// Updated in DrawStart
	ofRectangle time_click_zone_;
	ofRectangle free_click_zone_;

	// SetupEnd, like SetupStart, allocates and loads font info for the text 
	// being displayed in both TIMED_END and FREE_END
	void SetupEnd();
	ofTrueTypeFont image_saved_;
	ofTrueTypeFont restart_;
	ofTrueTypeFont draw_more_;
	// Updated in DrawTimedEnd and DrawFreeEnd
	ofRectangle restart_click_zone_;
	ofRectangle draw_more_click_zone_;

	// Draw functions for each display mode
	// Note some rely on each other (especially on DrawFree) because
	// they are all very similar, just with slight adjustments
	void DrawStart();
	void DrawFree();
	void DrawTimed();
	void DrawTimedEnd();
	void DrawFreeEnd();

	// Act as listener functions for when the mouse is clicked in 
	// the respective display mode
	void PressedInStart(ofPoint& point);
	void PressedInTimedEnd(ofPoint& point);
	void PressedInFreeEnd(ofPoint& point);

	// Used for timed mode
	RandomNoun random_noun_;
	void SetupRandomNoun(); // called when timed is pressed in START
	float time_to_complete_;

	// Starts as false so that when the image is saved, it doesn't save
	// with reset buttons on top (is set to true at end of SaveImage)
	bool draw_reset_buttons_ = false;

	// Draw certain reset buttons (depends on display mode). i.e. DrawTimedEnd
	// does not have "draw more", but DrawFreeEnd does
	void DrawImageSaved();
	void DrawRestart();
	void DrawDrawMore();

	// Helper method called when the ToolGui button 'exit_' is pressed
	void ResetToStart();
};