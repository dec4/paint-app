//  custom line class so that they can be drawn 
//  individually with different properties

#pragma once

#include "ofxGui.h"

class AppLine {
public:
    // Constructors (and initializations)
    AppLine() {
        line_ = new ofPolyline();
    }
    explicit AppLine(ofPoint& start_point, ofColor& color, float& radius) {
        color_ = color;
        radius_ = radius;
        line_ = new ofPolyline();
        line_->addVertex(start_point);
    };

    // Getters
    ofPolyline GetLine();
    ofColor GetColor();
    float GetWidth();

    // Add point to this ofPolyline
    void AddPoint(ofPoint& pt);

private:
    ofPolyline* line_;
    ofColor color_;
    float radius_;
};
