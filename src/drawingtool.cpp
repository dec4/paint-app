#include "drawingtool.h"


int DrawingTool::HueMin() {
    return hue_min_;
}

int DrawingTool::HueMax() {
    return hue_max_;
}

int DrawingTool::SaturationMin() {
    return saturation_min_;
}

int DrawingTool::SaturatinMax() {
    return saturation_max_;
}

int DrawingTool::BrightnessMin() {
    return brightness_min_;   
}

int DrawingTool::BrightnessMax() {
    return brightness_max_;
}

int DrawingTool::AlphaMin() {
    return alpha_min_;
}

int DrawingTool::AlphaMax() {
    return alpha_max_;
}


int DrawingTool::LastHue() {
    return last_hue_;   
}

int DrawingTool::LastSaturation() {
    return last_saturation_;
}

int DrawingTool::LastBrightness() {
    return last_brightness_;
}

int DrawingTool::LastAlpha() {
    return last_alpha_;
}


void DrawingTool::SaveLastState(int hue, int saturation, int brightness, int alpha) {
    last_hue_ = hue;
    last_saturation_ = saturation;
    last_brightness_ = brightness;
    last_alpha_ = alpha;
}