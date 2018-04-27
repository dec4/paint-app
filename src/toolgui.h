#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofApp.h"

class ofApp;

enum DrawingTool {  // TODO: SHOULD BE INSIDE A CLASS
	PENCIL,
	PEN,
	ERASER
};

class ToolGui : public ofBaseApp {

	public:

		// Main OpenFrameworks loop
		void setup();
		void update();
		void draw();

		// Getters for access in ofApp
		ofColor GetColor();
		DrawingTool GetTool();
		float GetRadius();

		shared_ptr<ofApp> canvas;

	private:

		ofxPanel gui_;
		// Drawing tool toggles
		ofxToggle pen_;
		ofxToggle pencil_;
		ofxToggle eraser_;
		// Color sliders
		ofxFloatSlider radius_;
		ofxIntSlider hue_;
		ofxIntSlider saturation_;
		ofxIntSlider brightness_;
		ofxIntSlider alpha_;
		// Buttons for other functions
		ofxButton clear_;
		ofxButton undo_;
		ofxButton redo_;
        ofxButton save_;

		ofColor color_;	// current color (hsba) - updated in update()
		DrawingTool current_tool_ = PEN;

		// Tool toggle listeners
		void ChoosePencil(bool& pressed);
		void ChoosePen(bool& pressed);
		void ChooseEraser(bool& pressed);
		// Helper function for simulating radio buttons
		void DisableAll();

		// Button listeners
		void ClearPressed();
		void UndoPressed();
		void RedoPressed();

		void SavePressed();

		void UpdateGui();  // Changes parameters depending on selected tool

		int tool_gui_width_;
		int tool_gui_height_;
};

