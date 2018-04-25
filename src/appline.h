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
    //explicit AppLine(ofPolyline& line, ofColor color, int radius) :
    //         line_(line), color_(color), radius_(radius) {};
    explicit AppLine(ofPoint& start_point, ofColor& color, float radius) {
        color_ = color;
        radius_ = radius;
        line_ = new ofPolyline();
        line_->addVertex(start_point);
    };

    // GETTERS // TODO: NAMING STYLE
    ofPolyline getLine();
    ofColor getColor();
    float getWidth();
    //DrawingTool getTool();  Tool should only determine possible settings (color, size)

    // OTHER
    void add_point(ofPoint& pt);

private:
    ofPolyline* line_;
    ofColor color_;
    float radius_;
    //DrawingTool tool_;  (see getter)
};
