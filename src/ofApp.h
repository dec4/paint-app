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

		ofColor background_ = ofColor(255, 255, 255);

		shared_ptr<ToolGui> tools;

		// Line storage variaables
		std::vector<AppLine*> canvas_lines_; 
		std::stack<AppLine*> undo_lines_;
		AppLine* current_line_;

		bool drawing = false;
		void DrawCanvas();  // Helper method: draws all lines in canvas_lines_

		// Click once to put down pen, move to draw, click again to release
		void mousePressed(int x, int y, int button);
		void mouseMoved(int x, int y );
		void mouseExited(int x, int y);  // Line ends if mouse goes out of window

		// Tool functions
		void ClearCanvas();
		void Undo();
		void Redo();
		bool redo_allowed_ = false;  // Can't redo something that was overwritten

		// For saving image to file
		ofImage img;
		void keyPressed(int key);
};