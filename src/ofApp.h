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
		void setup();
		void update();
		void draw();

		//ofPath all_lines_;
		std::vector<AppLine*> canvas_lines_;	// USE STACK TO HOLD SEPARATE LINES
												// Note: when change is done, all_lines_ should not
												// be used anywhere
												// Note 2: canvas changed to vectors to loop through
		std::stack<AppLine*> undo_lines_;
		AppLine* current_line_;

		// Click once to put down pen, drag, click again to release
		bool drawing = false;

		void mousePressed(int x, int y, int button);
		void mouseMoved(int x, int y );
		void mouseExited(int x, int y);

		void drawCanvas();
		void clearCanvas();
		void undo();
		void redo();

	    shared_ptr<ToolGui> tools;

		bool redo_allowed_ = false;

		ofColor background_ = ofColor(255, 255, 255);

		ofImage img;
		//void saveImage(std::string& filename);
		void keyPressed(int key);

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