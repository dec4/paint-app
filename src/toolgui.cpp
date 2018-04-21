#include "toolgui.h"


void ToolGui::setup() {
    // Using sliders (see .h)
	//parameters.add(radius.set("radius", 50, 1, 100));
	//parameters.add(color.setHsb("color (hsba)", 100, 200, 100, 255));
    // compare to rsb: parameters.add(color.set("color",100,ofColor(0,0),255));
    //gui.setup(parameters);
    // NOTE: USE PARAMETERS IF CREATE OWN HSBACOLOR OBJECT
    // ^SAME FOR DRAWING TOOL?

    gui_.setup();   
    gui_.add(radius_.setup("radius", 75, 10, 150));
    gui_.add(hue_.setup("hue", 125, 0, 255));
    gui_.add(saturation_.setup("saturation", 255, 0, 255));
    gui_.add(brightness_.setup("brightness", 255, 0, 255));
    gui_.add(alpha_.setup("alpha", 255, 0, 255));

    // NOTE: create method to reset gui (so that different tools have 
    // different ranges for color, alpha, size, etc.)


    // Add listener (below) to all tools then add method so that if tool changes, 
    // all other tools are disabled.
    // ex: circleResolution.addListener(this, &ToolGui::circleResolutionChanged);
    // and use myToggle.set(false);
    gui_.add(pencil_.setup("pencil", true));
    gui_.add(pen_.setup("pen", false));
    gui_.add(eraser_.setup("eraser", false));

    // Add listeners
    pencil_.addListener(this, &ToolGui::choosePencil);
    pen_.addListener(this, &ToolGui::choosePen);
    eraser_.addListener(this, &ToolGui::chooseEraser);

    ofBackground(background_);

}

void ToolGui::update() {
    // update color
    color_.setHsb(hue_, saturation_, brightness_, alpha_);
}

void ToolGui::draw() {
    ofSetColor(color_);
    ofDrawCircle(0.7*ofGetWidth(), ofGetHeight()/2, radius_);
	gui_.draw();
}


// NOTE FOR CASES: CREATE VECTOR OF TOGGLES TO LOOP THRU 
// ALL INSTEAD OF HARD CODING?
void ToolGui::disableCurrent() {
    switch (current_tool_) {
        case PENCIL: 
            pencil_ = false;
        case PEN:
            pen_ = false;
        case ERASER:
            eraser_ = false;
    }
}


// Functions to help simulate radio buttons

void ToolGui::choosePencil(bool& pressed) {
    if (!pressed) {
        return;
    }
    // Some tool must always be active, so don't deactivate current tool
    // CURRENTLY **NOT** WORKING FOR ALL THREE TOOLS
    if (current_tool_ == PENCIL) {
        //disableCurrent();
        pencil_ = true;
    } else {
        disableCurrent();
        current_tool_ = PENCIL;
        pencil_ = true;
    }
}

void ToolGui::choosePen(bool& pressed) {
    if (!pressed) {
        return;
    }
    // Some tool must always be active, so don't deactivate current tool
    if (current_tool_ == PEN) {
        pen_ = true;
    } else {
        disableCurrent();
        current_tool_ = PEN;
        pen_ = true;
    }
}

void ToolGui::chooseEraser(bool& pressed) {
    if (!pressed) {
        return;
    }
    // Some tool must always be active, so don't deactivate current tool
    if (current_tool_ == ERASER) {
        eraser_ = true;
    } else {
        disableCurrent();
        current_tool_ = ERASER;
        eraser_ = true;
    }
}
