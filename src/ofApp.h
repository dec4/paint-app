#pragma once

#include "ofMain.h"
#include "ofxGui.h"

enum DrawingTool {
	PENCIL,
	PEN,
	ERASER
};

class ofApp : public ofBaseApp {

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

		void updateColor();

		void choosePencil(bool& pressed);
		void choosePen(bool& pressed);
		void chooseEraser(bool& pressed);
		void disableCurrent();

		DrawingTool current_tool_ = PENCIL;
};

/* STARTER CODE

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};

*/
