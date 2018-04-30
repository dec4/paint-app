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

    gui_.setup();   

    gui_.add(pencil_.setup("pencil", false));
    gui_.add(pen_.setup("pen", true));
    gui_.add(eraser_.setup("eraser", false));
    // Listeners used to simulate radio buttons
    pencil_.addListener(this, &ToolGui::ChoosePencil);
    pen_.addListener(this, &ToolGui::ChoosePen);
    eraser_.addListener(this, &ToolGui::ChooseEraser);

    gui_.add(radius_.setup("radius", 2, .5, 5));
    gui_.add(thick_.setup("thicken stroke", false));
    thick_.addListener(this, &ToolGui::ThickPressed);

    // Color parameters
    gui_.add(hue_.setup("hue", 150, 0, 255));
    gui_.add(saturation_.setup("saturation", 255, 0, 255));
    gui_.add(brightness_.setup("brightness", 255, 0, 255));
    gui_.add(alpha_.setup("alpha", 255, 0, 255));

    gui_.add(clear_.setup("clear canvas (c)"));
    clear_.addListener(this, &ToolGui::ClearPressed);

    gui_.add(undo_.setup("undo (u)"));
    undo_.addListener(this, &ToolGui::UndoPressed);

    gui_.add(redo_.setup("redo (r)"));
    redo_.addListener(this, &ToolGui::RedoPressed);

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
    switch (current_tool_) {
        case PENCIL: 
            hue_ = 0;
            hue_.setMin(0);
            hue_.setMax(0);
            saturation_ = 0;
            saturation_.setMin(0);
            saturation_.setMax(0);
            brightness_ = 150;
            brightness_.setMin(0);
            brightness_.setMax(255);
            // alpha never changes, so it 
            // never has to be reset
            break;
        case PEN:
            hue_ = 150;
            hue_.setMin(0);
            hue_.setMax(255);
            saturation_ = 255;
            saturation_.setMin(0);
            saturation_.setMax(255);
            brightness_ = 255;
            brightness_.setMin(0);
            brightness_.setMax(255);
            // alpha never changes, so it 
            // never has to be reset
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
            // alpha never changes, so it 
            // never has to be reset
            break;
    }
}

void ToolGui::DisableAll() {
    pencil_ = false;
    pen_ = false;
    eraser_ = false;
}


//*** LISTENER FUNCTIONS ***//

// Note for toggle functions: bool& active = toggle state AFTER pressed

void ToolGui::ChoosePencil(bool& active) {
    if (active) {
        current_tool_ = PENCIL;
        DisableAll();
        pencil_ = true;
        UpdateGui();
    } else if (!active && current_tool_ == PENCIL) {
        pencil_ = true;
    }
}

void ToolGui::ChoosePen(bool& active) {
    if (active) {
        current_tool_ = PEN;
        DisableAll();
        pen_ = true;
        UpdateGui();
    } else if (!active && current_tool_ == PEN) {
        pen_ = true;
    }
}

void ToolGui::ChooseEraser(bool& active) {
    if (active) {
        current_tool_ = ERASER;
        DisableAll();
        eraser_ = true;
        UpdateGui();
    } else if (!active && current_tool_ == ERASER) {
        eraser_ = true;
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