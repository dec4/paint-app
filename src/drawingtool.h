#pragma once

#include "ofxGui.h"
//#include "ofMain.h"

class DrawingTool {

public:
    // min and max getters
    int HueMin();
    int HueMax();
    int SaturationMin();
    int SaturatinMax();
    int BrightnessMin();
    int BrightnessMax();
    int AlphaMin();
    int AlphaMax();
    // last state getters
    int LastHue();
    int LastSaturation();
    int LastBrightness();
    int LastAlpha();

    // Saves the last state of tool
    // Used so that when switched back, it can switch to last state 
    // rather than some default value. Also note that only last values
    // are saved because the min and max are fixed at initialization.
    void SaveState(int hue, int saturation, int brightness, int alpha);

protected:
    // min and max values
    int hue_min_;
    int hue_max_;
    int saturation_min_;
    int saturation_max_;
    int brightness_min_;
    int brightness_max_;
    int alpha_min_;
    int alpha_max_;
    // last state  values
    int last_hue_;
    int last_saturation_;
    int last_brightness_;
    int last_alpha_;
};


//----- SPECIFIC DRAWING TOOLS -----//
// Each drawing tool has a specific default constructor that
// initializes all the varables above, depending on the tool

class Pencil : public DrawingTool {
public:
    Pencil() {
        hue_min_ = 0;
        hue_max_ = 0;
        saturation_min_ = 0;
        saturation_max_ = 0;
        brightness_min_ = 0;
        brightness_max_ = 255;
        alpha_min_ = 0;
        alpha_max_ = 255;

        last_hue_ = 0;
        last_saturation_ = 0;
        last_brightness_ = 150;
        last_alpha_ = 255;
    };
};

class Pen : public DrawingTool {
public:
    Pen() {
        hue_min_ = 0;
        hue_max_ = 255;
        saturation_min_ = 0;
        saturation_max_ = 255;
        brightness_min_ = 0;
        brightness_max_ = 255;
        alpha_min_ = 0;
        alpha_max_ = 255;

        last_hue_ = 150;
        last_saturation_ = 255;
        last_brightness_ = 255;
        last_alpha_ = 255;
    };
};

class Eraser : public DrawingTool {
public:
    Eraser(ofColor* background) {
        hue_min_ = background->getHue();
        hue_max_ = background->getHue();
        saturation_min_ = background->getSaturation();
        saturation_max_ = background->getSaturation();
        brightness_min_ = background->getBrightness();
        brightness_max_ = background->getBrightness();
        alpha_min_ = 0;
        alpha_max_ = 255;

        last_hue_ = background->getHue();
        last_saturation_ = background->getSaturation();
        last_brightness_ = background->getBrightness();
        last_alpha_ = 255;
    };
};