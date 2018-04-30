//  custom line class so that they can be drawn 
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
    explicit AppLine(ofPoint& start_point, ofColor& color, float& radius, bool& thicken) {
        color_ = color;
        radius_ = radius;
        thick_ = thicken;
        line_ = new ofPolyline();
        line_->addVertex(start_point);
    };

    // GETTERS
    ofPolyline GetLine();
    ofColor GetColor();
    float GetWidth();
    bool IsThick();

    // MODIFIERS
    void AddPoint(ofPoint& pt);

private:
    ofPolyline* line_;
    ofColor color_;
    float radius_;
    bool thick_;
};
