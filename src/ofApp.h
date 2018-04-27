#pragma once

#include "ofMain.h"
#include "toolgui.h"
#include "appline.h"
#include <stack>
#include <vector>
#include <string>

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

		ofColor background_ = ofColor(255, 255, 255);

		shared_ptr<ToolGui> tools;

		// Line storage variaables
		std::vector<AppLine*> canvas_lines_; 
		std::stack<AppLine*> redo_lines_;
		AppLine* current_line_;

		bool drawing = false;
		void DrawCanvas();  // Helper method: draws all lines in canvas_lines_

		// Click once to put down pen, move to draw, click again to release
		void mousePressed(int x, int y, int button);
		void mouseMoved(int x, int y );
		void mouseExited(int x, int y);  // Line ends if mouse goes out of window

		// Tool functions
		void ClearCanvas();
		void ClearUndoHistory();
		void Undo();
		void Redo();
		bool redo_allowed_ = false;  // Can't redo something that was overwritten

		// For keyboard shortcuts of some tools
		void keyPressed(int key);

		// For saving image to file
		ofFbo canvas_fbo_;
		bool print_save_message_ = false;
		void SaveImage();
};