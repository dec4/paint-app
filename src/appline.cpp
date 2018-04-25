#include "appline.h"

ofPolyline AppLine::getLine() {
    return *line_;
}

ofColor AppLine::getColor() {
    return color_;
}

float AppLine::getWidth() {
    return radius_*2;
}

void AppLine::add_point(ofPoint& pt) {
    line_->addVertex(pt);
}