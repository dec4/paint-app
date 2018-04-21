#pragma once

#include "ofMain.h"
#include "ofxGui.h"

enum DrawingTool {
	PENCIL,
	PEN,
	ERASER
};

class ToolGui : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		// Using sliders instead of parameter in order to implement hsba
		//ofParameterGroup parameters;
	    //ofParameter<float> radius;
	    //ofParameter<ofColor> color;
		ofxFloatSlider radius_;
		ofxIntSlider hue_;
		ofxIntSlider saturation_;
		ofxIntSlider brightness_;
		ofxIntSlider alpha_;
		ofxToggle pen_;
		ofxToggle pencil_;
		ofxToggle eraser_;

        
	    ofxPanel gui_;

		ofColor color_;	// updated by sliders above (hsba)
		ofColor background_ = ofColor(255, 255, 255);


		void choosePencil(bool& pressed);
		void choosePen(bool& pressed);
		void chooseEraser(bool& pressed);
		void disableCurrent();

		DrawingTool current_tool_ = PENCIL;
};

