#include "toolgui.h"
#include <string>


//*** GETTERS ***//

ofColor ToolGui::GetColor() {
    return color_;
}

float ToolGui::GetRadius() {
    return radius_;
}


//*** OPENFRAMEWORKS METHODS ***//

void ToolGui::setup() {
    // Initialize width and height variables
    tool_gui_width_ = ofGetWindowWidth();
    tool_gui_height_ = ofGetWindowHeight();

    // Initialize background color to match canvas
    //ofBackground(canvas->background_);
    // TODO: decide: use default so that eraser preview can be seen?

    // Initialize drawing tools
    pen_ = new Pen();
    pencil_ = new Pencil();
    eraser_ = new Eraser(&(canvas->background_));
    current_tool_ = pen_;

    gui_.setup();  // Everything below is for setting up gui:

    // Drawing Tools
    gui_.add(pencil_toggle_.setup("pencil", false));
    gui_.add(pen_toggle_.setup("pen", true));
    gui_.add(eraser_toggle_.setup("eraser", false));
    // Listeners used to simulate radio buttons
    pencil_toggle_.addListener(this, &ToolGui::ChoosePencil);
    pen_toggle_.addListener(this, &ToolGui::ChoosePen);
    eraser_toggle_.addListener(this, &ToolGui::ChooseEraser);

    // Size parameters
    gui_.add(radius_.setup("radius", 2, .5, 5));
    gui_.add(thick_.setup("thicken stroke", false));
    thick_.addListener(this, &ToolGui::ThickPressed);

    // Color parameters
    gui_.add(hue_.setup("hue", 150, 0, 255));
    gui_.add(saturation_.setup("saturation", 255, 0, 255));
    gui_.add(brightness_.setup("brightness", 255, 0, 255));
    gui_.add(alpha_.setup("alpha", 255, 0, 255));

    // Clear
    gui_.add(clear_.setup("clear canvas (c)"));
    clear_.addListener(this, &ToolGui::ClearPressed);

    // Undo
    gui_.add(undo_.setup("undo (u)"));
    undo_.addListener(this, &ToolGui::UndoPressed);

    // Redo
    gui_.add(redo_.setup("redo (r)"));
    redo_.addListener(this, &ToolGui::RedoPressed);

    // Save
    gui_.add(save_.setup("save image (s)"));
    save_.addListener(this,  &ToolGui::SavePressed);
}

void ToolGui::update() { 
    // Update color based off of sliders
    color_.setHsb(hue_, saturation_, brightness_, alpha_);
        // Note: using update instead of listeners because then it's 
        // one line vs setting color in four different listeners
}

void ToolGui::draw() {
    ofSetColor(color_);
    ofDrawCircle(0.5*tool_gui_width_, 0.85*tool_gui_height_, radius_);
	gui_.draw();
    if (canvas->print_save_message_) {
        ofSetColor(0, 0, 0);
	    ofDrawBitmapString("Image Saved!", 0.3*tool_gui_width_, 0.95*tool_gui_height_);
        if (ofGetElapsedTimeMillis() > 2000) {
            canvas->print_save_message_ = false;
        }
    }
}

void ToolGui::keyPressed(int key) {
	int upper_key = toupper(key);

	if (upper_key == 'C') {
		canvas->ClearCanvas();
	}
	else if (upper_key == 'U') {
		canvas->Undo();
	}
	else if (upper_key == 'R') {
		canvas->Redo();
	}
	else if (upper_key == 'S') {
		canvas->SaveImage();
	}
}


//*** PRIVATE METHODS ***//

void ToolGui::UpdateGui() {
    hue_ = current_tool_->LastHue();
    hue_.setMin(current_tool_->HueMin());
    hue_.setMax(current_tool_->HueMax());
    saturation_ = current_tool_->LastSaturation();
    saturation_.setMin(current_tool_->SaturationMin());
    saturation_.setMax(current_tool_->SaturatinMax());
    brightness_ = current_tool_->LastBrightness();
    brightness_.setMin(current_tool_->BrightnessMin());
    brightness_.setMax(current_tool_->BrightnessMax());
    alpha_ = current_tool_->LastAlpha();
    alpha_.setMin(current_tool_->AlphaMin());
    alpha_.setMax(current_tool_->AlphaMax());
}

void ToolGui::DisableAll() {
    pencil_toggle_ = false;
    pen_toggle_ = false;
    eraser_toggle_ = false;
}


//*** LISTENER FUNCTIONS ***//

// Note for toggle functions: bool& active = toggle state AFTER pressed

void ToolGui::ChoosePencil(bool& active) {
    if (active) {
        current_tool_->SaveLastState(hue_, saturation_, brightness_, alpha_);
        current_tool_ = pencil_;
        DisableAll();
        pencil_toggle_ = true;
        UpdateGui();
    } else if (!active && current_tool_ == pencil_) {
        pencil_toggle_ = true;
    }
}

void ToolGui::ChoosePen(bool& active) {
    if (active) {
        current_tool_->SaveLastState(hue_, saturation_, brightness_, alpha_);
        current_tool_ = pen_;
        DisableAll();
        pen_toggle_ = true;
        UpdateGui();
    } else if (!active && current_tool_ == pen_) {
        pen_toggle_ = true;
    }
}

void ToolGui::ChooseEraser(bool& active) {
    if (active) {
        current_tool_->SaveLastState(hue_, saturation_, brightness_, alpha_);
        current_tool_ = eraser_;
        DisableAll();
        eraser_toggle_ = true;
        UpdateGui();
    } else if (!active && current_tool_ == eraser_) {
        eraser_toggle_ = true;
    }
}

void ToolGui::ThickPressed(bool& active) {
    canvas->thicken_ = active;
}

void ToolGui::ClearPressed() {
    canvas->ClearCanvas();
}

void ToolGui::UndoPressed() {
    canvas->Undo();
}

void ToolGui::RedoPressed() {
    canvas->Redo();
}

void ToolGui::SavePressed() {
    canvas->SaveImage();
}