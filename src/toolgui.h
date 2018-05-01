#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofApp.h"
#include "drawingtool.h"

class ofApp;

class ToolGui : public ofBaseApp {

	public:

		// Main OpenFrameworks loop
		void setup();
		void update();
		void draw();

		// Getters for access in ofApp
		ofColor GetColor();
		float GetRadius();

		// Pointer to app in ofApp window (canvas)
		shared_ptr<ofApp> canvas;

	private:

		// Window width and height 
		// Initialized in setup()
		int tool_gui_width_;
		int tool_gui_height_;

		// Wave preview
		ofPolyline wave_;
		void InitializeWave();

		// For keyboard shortcuts
		// Shortcuts for actions only (clear, undo, redo, save)
		void keyPressed(int key);

		ofxPanel settings_gui_;
		// Drawing tool toggles
		ofxToggle pen_toggle_;
		ofxToggle pencil_toggle_;
		ofxToggle eraser_toggle_;
		// Size modifier
		ofxFloatSlider radius_;
		// Color sliders
		ofxIntSlider hue_;
		ofxIntSlider saturation_;
		ofxIntSlider brightness_;
		ofxIntSlider alpha_;
		// Toggle to allow exit without ending line
		ofxToggle bounded_;
		// Buttons for other functions
		ofxButton background_;
		ofxButton clear_;
		ofxButton undo_;
		ofxButton redo_;
        ofxButton save_;

		// Keep track of current color for easy access
		// Updated using hsba slider info in update()
		ofColor color_;

		//ToolType current_tool_ = PEN;
		// Create instance of each tool
		Pen* pen_;
		Pencil* pencil_;
		Eraser* eraser_;
		// Track current tool using a pointer
		DrawingTool* current_tool_;
		// Tool toggle listeners
		void ChoosePencil(bool& pressed);
		void ChoosePen(bool& pressed);
		void ChooseEraser(bool& pressed);
		// Helper function for simulating radio buttons
		void DisableAll();
		// Change slider parameters depending on selected tool
		void UpdateGui();

		// Other listeners
		void BoundedPressed(bool& active);
		void BackgroundPressed();
		void ClearPressed();
		void UndoPressed();
		void RedoPressed();
		void SavePressed();
};

