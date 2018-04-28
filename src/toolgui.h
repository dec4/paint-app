#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofApp.h"

class ofApp;

class ToolGui : public ofBaseApp {

	enum DrawingTool {
		PENCIL,
		PEN,
		ERASER
	};

	public:

		// Main OpenFrameworks loop
		void setup();
		void update();
		void draw();

		// Getters for access in ofApp
		ofColor GetColor();
		float GetRadius();

		shared_ptr<ofApp> canvas;

	private:

		// Window width and height 
		// Initialized in setup()
		int tool_gui_width_;
		int tool_gui_height_;

		// For keyboard shortcuts
		void keyPressed(int key);

		ofxPanel gui_;
		// Drawing tool toggles
		ofxToggle pen_;
		ofxToggle pencil_;
		ofxToggle eraser_;
		// Radius slider
		ofxFloatSlider radius_;
		// Color sliders
		ofxIntSlider hue_;
		ofxIntSlider saturation_;
		ofxIntSlider brightness_;
		ofxIntSlider alpha_;
		// Buttons for other functions
		ofxButton clear_;
		ofxButton undo_;
		ofxButton redo_;
        ofxButton save_;

		// Keep track of current color for easy access
		// Updated using hsba slider info in update()
		ofColor color_;

		DrawingTool current_tool_ = PEN;
		// Tool toggle listeners
		void ChoosePencil(bool& pressed);
		void ChoosePen(bool& pressed);
		void ChooseEraser(bool& pressed);
		// Helper function for simulating radio buttons
		void DisableAll();
		// Change slider parameters depending on selected tool
		void UpdateGui();

		// Button listeners
		void ClearPressed();
		void UndoPressed();
		void RedoPressed();
		void SavePressed();
};

