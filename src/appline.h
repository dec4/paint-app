//  custom line class so that they can be printed 
//  individually with different properties

#pragma once

#include "ofxGui.h"
//#include "ofMain.h"

class AppLine {
public:
    // CONSTRUCTORS (ADD INITIALIZATIONS)
    AppLine() {
        line_ = new ofPolyline();
    }
    explicit AppLine(ofPoint& start_point, ofColor& color, float& radius) {
        color_ = color;
        radius_ = radius;
        line_ = new ofPolyline();
        line_->addVertex(start_point);
    };

    // GETTERS
    ofPolyline GetLine();
    ofColor GetColor();
    float GetWidth();

    // MODIFIERS
    void AddPoint(ofPoint& pt);

private:
    ofPolyline* line_;
    ofColor color_;
    float radius_;
};
