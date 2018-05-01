#include "toolgui.h"
#include <string>


//----- GETTERS -----//

ofColor ToolGui::GetColor() {
    return color_;
}

float ToolGui::GetRadius() {
    return radius_;
}


//----- MAIN OPENFRAMEWORKS LOOP -----//

void ToolGui::setup() {
    // Initialize width and height variables
    tool_gui_width_ = ofGetWindowWidth();
    tool_gui_height_ = ofGetWindowHeight();

    // Initialize wave line (used for tool preview)
    InitializeWave();

    // Initialize drawing tools
    pen_ = new Pen();
    pencil_ = new Pencil();
    eraser_ = new Eraser(&(canvas->background_));
    current_tool_ = pen_;

    settings_gui_.setup();  // Everything below is for setting up gui:

    // Drawing Tools
    settings_gui_.add(pencil_toggle_.setup("pencil", false));
    settings_gui_.add(pen_toggle_.setup("pen", true));
    settings_gui_.add(eraser_toggle_.setup("eraser", false));
    // Listeners used to simulate radio buttons
    pencil_toggle_.addListener(this, &ToolGui::ChoosePencil);
    pen_toggle_.addListener(this, &ToolGui::ChoosePen);
    eraser_toggle_.addListener(this, &ToolGui::ChooseEraser);

    // Size parameters
    settings_gui_.add(radius_.setup("radius", 2, .5, 4));

    // Color parameters
    settings_gui_.add(hue_.setup("hue", 150, 0, 255));
    settings_gui_.add(saturation_.setup("saturation", 255, 0, 255));
    settings_gui_.add(brightness_.setup("brightness", 255, 0, 255));
    settings_gui_.add(alpha_.setup("alpha", 255, 0, 255));

    // Unbounded
    // Determines whether or not the line should end when the 
    // mouse is drawing and exits the window
    settings_gui_.add(bounded_.setup("bounded", true));
    bounded_.addListener(this, &ToolGui::BoundedPressed);

    // Background
    settings_gui_.add(background_.setup("set background color"));
    background_.addListener(this, &ToolGui::BackgroundPressed);

    // Clear
    settings_gui_.add(clear_.setup("c: clear canvas"));
    clear_.addListener(this, &ToolGui::ClearPressed);

    // Undo
    settings_gui_.add(undo_.setup("u: undo"));
    undo_.addListener(this, &ToolGui::UndoPressed);

    // Redo
    settings_gui_.add(redo_.setup("r: redo"));
    redo_.addListener(this, &ToolGui::RedoPressed);

    // Save
    settings_gui_.add(save_.setup("s: save image"));
    save_.addListener(this,  &ToolGui::SavePressed);
}

void ToolGui::update() { 
    // Update color based off of sliders
    color_.setHsb(hue_, saturation_, brightness_, alpha_);
        // Note: using update instead of listeners because then it's 
        // one line vs setting color in four different listeners
}

void ToolGui::draw() {
    // Draw settings
    settings_gui_.draw();

    // Draw wave (preview) 
    ofSetColor(color_);
    ofSetLineWidth(radius_*2);
    wave_.draw();
    // Draw circle (preview)
    ofDrawCircle(0.5*tool_gui_width_, 0.87*tool_gui_height_, radius_);

    // Draw "Image Saved!" if necessary
    if (canvas->print_save_message_) {
        ofSetColor(0, 0, 0);
	    ofDrawBitmapString("Image Saved!", 0.3*tool_gui_width_, 0.95*tool_gui_height_);
        // Only display for two seconds
        if (ofGetElapsedTimeMillis() > 2000) {  // elapsed time is reset in Save()
            canvas->print_save_message_ = false;
        }
    }
}


//----- OTHER OPENFRAMEWORKS METHODS -----//

/**
 * Used for keyboard shortcuts.
 * Contains shortcuts for ACTIONS only (not settings)
 */
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


//----- LISTENER FUNCTIONS (also private) -----//
// Note: Listener functions are called when the toggle/button is pressed

/**
 * General process for all tool toggle listener functions:
 * Note bool& active = toggle state AFTER pressed
 * 
 * if toggle is pressed and changed to true,
 *      save last state of current_tool_ (before change)
 *      change current_tool_ to this toggle's tool
 *      disable all tool toggles
 *      set this tool toggle to true
 *      update gui parameters to fit this tool
 * // In order to make sure one tool is always active: 
 * else if toggle is pressed and changed to false
 *      set this tool toggle to true
 *      // nothing else has to be done, because nothing changed
 */

/**
 * Listener function for pencil toggle.
 */
void ToolGui::ChoosePencil(bool& active) {
    if (active) {
        current_tool_->SaveState(hue_, saturation_, brightness_, alpha_);
        current_tool_ = pencil_;
        DisableAll();
        pencil_toggle_ = true;
        UpdateGui();
    } else if (!active && current_tool_ == pencil_) {
        pencil_toggle_ = true;
    }
}

/**
 * Listener function for pen toggle.
 */
void ToolGui::ChoosePen(bool& active) {
    if (active) {
        current_tool_->SaveState(hue_, saturation_, brightness_, alpha_);
        current_tool_ = pen_;
        DisableAll();
        pen_toggle_ = true;
        UpdateGui();
    } else if (!active && current_tool_ == pen_) {
        pen_toggle_ = true;
    }
}

/**
 * Listener function for eraser toggle.
 */
void ToolGui::ChooseEraser(bool& active) {
    if (active) {
        current_tool_->SaveState(hue_, saturation_, brightness_, alpha_);
        current_tool_ = eraser_;
        DisableAll();
        eraser_toggle_ = true;
        UpdateGui();
    } else if (!active && current_tool_ == eraser_) {
        eraser_toggle_ = true;
    }
}

/**
 * Listener function for bounded toggle.
 */
void ToolGui::BoundedPressed(bool& active) {
    canvas->bounded_ = active;
}

/**
 * Change background color to the current color in toolgui.
 */
void ToolGui::BackgroundPressed() {
    canvas->background_ = color_;
    eraser_->SaveState(hue_, saturation_, brightness_, alpha_);
}

/**
 * Listener function for clear button.
 */
void ToolGui::ClearPressed() {
    canvas->ClearCanvas();
}

/**
 * Listener function for undo button.
 */
void ToolGui::UndoPressed() {
    canvas->Undo();
}

/**
 * Listener function for redo button.
 */
void ToolGui::RedoPressed() {
    canvas->Redo();
}

/**
 * Listener function for save button.
 */
void ToolGui::SavePressed() {
    canvas->SaveImage();
}


//----- PRIVATE METHODS -----//

/**
 * Helper function to create line for preview. 
 * Use a wave to better display what the brush 
 * stroke will look like
 */
void ToolGui::InitializeWave() {
    // Start of wave
    int startx = 0;
    int starty = 0.85*tool_gui_height_;
    wave_.addVertex(startx, starty, 0);
    // Wave goes across width of tool gui
    for (float i = 0; i < tool_gui_width_; i+=5) {
        // Parametric Equations to create sin wave
        float x = startx + i;
        float y = starty + 10*sin(0.1*i);
        wave_.addVertex(x, y, 0);
    }
}

/**
 * Helper function to change tool gui parameters based on 
 * what the current tool is. Each tool type has it's own 
 * parameters that are fixed/changeable
 */
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

/**
 * Helper function called whenever a different tool toggle is pressed.
 * Simulates radio buttons (only one is allowed to be active at a time)
 */
void ToolGui::DisableAll() {
    pencil_toggle_ = false;
    pen_toggle_ = false;
    eraser_toggle_ = false;
}