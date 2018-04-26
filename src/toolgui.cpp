#include "toolgui.h"
#include <string>

//*** GETTERS ***//

ofColor ToolGui::GetColor() {
    return color_;
}

DrawingTool ToolGui::GetTool() {
    return current_tool_;
}

int ToolGui::GetRadius() {
    return radius_;
}



//*** OPENFRAMEWORKS METHODS ***//

void ToolGui::setup() {
    // Using ofParameter (see .h):
	//parameters.add(radius.set("radius", 50, 1, 100));
	//parameters.add(color.setHsb("color (hsba)", 100, 200, 100, 255));
    // compare to rsb: parameters.add(color.set("color",100,ofColor(0,0),255));
    //gui.setup(parameters);
    // NOTE: USE PARAMETERS IF CREATE OWN HSBACOLOR OBJECT
    // ^SAME FOR DRAWING TOOL?
    // Also note using ofParameter will allow changes in range (https://forum.openframeworks.cc/t/dynamic-range-in-ofxslider-ofxgui/15424)

    gui_.setup();   

    // set resolution
    //ofSetCircleResolution(100);

    // add set line roundness?

    // Add listeners to simulate radio buttons
    pencil_.addListener(this, &ToolGui::ChoosePencil);
    pen_.addListener(this, &ToolGui::ChoosePen);
    eraser_.addListener(this, &ToolGui::ChooseEraser);
    gui_.add(pencil_.setup("pencil", false));
    gui_.add(pen_.setup("pen", true));
    gui_.add(eraser_.setup("eraser", false));

    // Add radius slider
    gui_.add(radius_.setup("radius", 2, .5, 5));
    // Add color sliders
    gui_.add(hue_.setup("hue", 150, 0, 255));
    gui_.add(saturation_.setup("saturation", 255, 0, 255));
    gui_.add(brightness_.setup("brightness", 255, 0, 255));
    gui_.add(alpha_.setup("alpha", 255, 0, 255));

    // NOTE: create method to reset gui (so that different tools have 
    // different ranges for color, alpha, size, etc.)
    // ^ or connect gui w tool object

    gui_.add(clear_.setup("clear canvas"));
    clear_.addListener(this, &ToolGui::ClearPressed);

    gui_.add(undo_.setup("undo"));
    undo_.addListener(this, &ToolGui::UndoPressed);

    gui_.add(redo_.setup("redo"));
    redo_.addListener(this, &ToolGui::RedoPressed);

    gui_.add(save_.setup("'S' in cavas to save"));
    //save_.addListener(this,  &ToolGui::savePressed);
}

void ToolGui::update() {
    // update color based off of sliders
    color_.setHsb(hue_, saturation_, brightness_, alpha_);
}

void ToolGui::draw() {
    ofSetColor(color_);
    ofDrawCircle(ofGetWidth()/2, 0.85*ofGetHeight(), radius_);
	gui_.draw();    // NOTENOTENOTE: USE ENUM TO DETERMINE WHICH GUI TO DRAW
}


//*** PRIVATE METHODS ***//

void ToolGui::UpdateGui() {
    switch (current_tool_) {
        case PENCIL: 
            hue_ = 0;
            hue_.setMax(0);
            saturation_ = 0;
            saturation_.setMax(0);
            brightness_ = 0;
            brightness_.setMax(255);
            alpha_ = 255;
            alpha_.setMax(255);
            break;
        case PEN:
            hue_ = 150;
            hue_.setMax(255);
            saturation_ = 255;
            saturation_.setMax(255);
            brightness_ = 255;
            brightness_.setMax(255);
            alpha_ = 255;
            alpha_.setMax(255);
            break;
        case ERASER:
            hue_ = canvas->background_.getHue();
            hue_.setMin(canvas->background_.getHue());
            hue_.setMax(canvas->background_.getHue());
            saturation_ = canvas->background_.getSaturation();
            saturation_.setMin(canvas->background_.getSaturation());
            saturation_.setMax(canvas->background_.getSaturation());
            brightness_ = canvas->background_.getBrightness();
            brightness_.setMin(canvas->background_.getBrightness());
            brightness_.setMax(canvas->background_.getBrightness());
            alpha_ = 255;
            alpha_.setMax(255);
            break;
    }
}


// NOTE FOR CASES: CREATE VECTOR OF TOGGLES TO LOOP THRU 
// ALL INSTEAD OF HARD CODING?
void ToolGui::DisableCurrent() {
    switch (current_tool_) {
        case PENCIL: 
            pencil_ = false;
            break;
        case PEN:
            pen_ = false;
            break;
        case ERASER:
            eraser_ = false;
            break;
    }
}

void ToolGui::DisableAll() {
    pencil_ = false;
    pen_ = false;
    eraser_ = false;
}


// Functions to help simulate radio buttons

void ToolGui::ChoosePencil(bool& pressed) {
    if (!pressed && current_tool_ != PENCIL) {
        return;
    }
    DisableAll();
    pencil_ = true;
    current_tool_ = PENCIL;
    UpdateGui();
}

void ToolGui::ChoosePen(bool& pressed) {
    if (!pressed) {
        return;
    }
    DisableAll();
    pen_ = true;
    current_tool_ = PEN;
    UpdateGui();
}

void ToolGui::ChooseEraser(bool& pressed) {
    if (!pressed) {
        return;
    }
    DisableAll();
    eraser_ = true;
    current_tool_ = ERASER;
    UpdateGui();
}

void ToolGui::ClearPressed() {
    (*canvas).ClearCanvas();
}

void ToolGui::UndoPressed() {
    (*canvas).Undo();
}

void ToolGui::RedoPressed() {
    (*canvas).Redo();
}