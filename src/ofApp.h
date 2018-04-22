#pragma once

#include "ofMain.h"
#include "toolgui.h"
#include <stack>

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		ofPath all_lines_;
		std::stack<ofPolyline> canvas_lines_;
		std::stack<ofPolyline> undo_lines_;
		ofPolyline* current_line_;

		// Click once to put down pen, drag, click again to release
		bool drawing = false;

		void mousePressed(int x, int y, int button);
		void mouseMoved(int x, int y );
		void mouseExited(int x, int y);

	    shared_ptr<ToolGui> gui;
		
};


/* STARTER CODE

class ToolGui : public ofBaseApp {

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

/* DRAWING REFERENCE: http://openframeworks.cc/ofBook/chapters/lines.html

void ofApp::setup(){
    ofBackground(0,0,0);
}

void ofApp::draw(){
    line.draw();
}

void ofApp::mouseDragged(int x, int y, int button){
    ofPoint pt;
    pt.set(x,y);
    line.addVertex(pt);
}

void ofApp::mousePressed(int x, int y, int button){
    line.clear();
}

*/