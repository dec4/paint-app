#pragma once

#include "ofxGui.h"
//#include "ofMain.h"

class CanvasObject {
private:
    ofColor color_;
public:
    virtual void drawObject() = 0;
};

