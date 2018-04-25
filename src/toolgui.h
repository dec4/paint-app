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
		void setup();
		void update();
		void draw();

		ofColor getColor();
		DrawingTool getTool();
		int getRadius();

		shared_ptr<ofApp> canvas;

	private:

		// Using sliders for now instead of parameter in order to implement hsba
		//ofParameterGroup parameters;
	    //ofParameter<float> radius;
	    //ofParameter<ofColor> color;
		ofxToggle pen_;
		ofxToggle pencil_;
		ofxToggle eraser_;
		ofxFloatSlider radius_;
		ofxIntSlider hue_;
		ofxIntSlider saturation_;
		ofxIntSlider brightness_;
		ofxIntSlider alpha_;
		ofxButton clear_;
		ofxButton undo_;
		ofxButton redo_;
        
		ofColor color_;	// updated by sliders above (hsba)

		ofxPanel gui_;
	    //ofxPanel pen_gui_;
		//ofxPanel pencil_gui_;
		//ofxPanel eraser_gui_;

		void choosePencil(bool& pressed);
		void choosePen(bool& pressed);
		void chooseEraser(bool& pressed);
		void disableCurrent();
		void disableAll();

		DrawingTool current_tool_ = PEN;

		void clearPressed();
		void undoPressed();
		void redoPressed();

		void updateGui();
};

