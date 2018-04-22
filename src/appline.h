/*  custom line class so that they can be printed 
    individually with different properties

#pragma once;

class AppLine {
public:
    AppLine(ofPolyline line, ofColor color, int radius, DrawingTool tool) :
            line_(line), ofColor_(color), radius_(radius), tool_(tool) {};
    ofPolyline getLine();
    ofColor getColor();
    int getWidth();
    DrawingTool getTool();

private:
    ofPolyline line_;
    ofColor color_;
    int radius_;
    DrawingTool tool_;
};

*/