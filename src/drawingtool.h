// TODO: TODO: TODO: TODO:  make .cpp file

#pragma once

#include "ofxGui.h"
//#include "ofMain.h"

class DrawingTool {

public:
    void HueMin();
    void HueMax();
    void SaturationMin();
    void SaturatinMax();
    void BrightnessMin();
    void BrightnessMax();
    void AlphaMin();
    void AlphaMax();

    void LastHue();
    void LastSaturation();
    void LastBrightness();
    void LastAlpha();

    void SaveLastState(int hue, int saturation, int brightness, int alpha) {
        last_hue_ = hue;
        last_saturation_ = saturation;
        last_brightness_ = brightness;
        last_alpha_ = alpha;
    };

private:
    hue_min_;
    hue_max_;
    saturation_min_;
    saturation_max_;
    brightness_min_;
    brightness_max_;
    alpha_min_;
    alpha_max_;

    last_hue_;
    last_saturation_;
    last_brightness_;
    last_alpha_;
};


class Pencil : public DrawingTool {
    // Default constructor
    Pencil() {
        hue_min_ 0;
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
    // Default constructor
    Pen() {
        hue_min_ 0;
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
    // Default constructor
    Eraser(ofColor& background) {
        hue_min_ background_.getHue();
        hue_max_ = background_.getHue();
        saturation_min_ = background_.getSaturation();
        saturation_max_ = background_.getSaturation();
        brightness_min_ = background_.getBrightness();
        brightness_max_ = background_.getBrightness();
        alpha_min_ = 0;
        alpha_max_ = 255;

        last_hue_ = background_.getHue();
        last_saturation_ = background_.getSaturation();
        last_brightness_ = background_.getBrightness();
        last_alpha_ = 255;
    };
};

// TODO: TODO: TODO: TODO:  make .cpp file

/*

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

*/