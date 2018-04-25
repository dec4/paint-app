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
        
	    ofxPanel gui_;

		ofColor color_;	// updated by sliders above (hsba)
		ofColor background_ = ofColor(255, 255, 255);


		void choosePencil(bool& pressed);
		void choosePen(bool& pressed);
		void chooseEraser(bool& pressed);
		void disableCurrent();

		DrawingTool current_tool_ = PENCIL;

		void clearPressed();
		void undoPressed();
		void redoPressed();
};

