//  custom line class so that they can be drawn 
//  individually with different properties

#pragma once

#include "ofxGui.h"

class AppLine {
public:
    // Constructors (and initializations)
    AppLine();
    AppLine(ofPoint& start_point, ofColor& color, float& radius);

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
