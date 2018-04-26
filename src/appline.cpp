#include "appline.h"

ofPolyline AppLine::GetLine() {
    return *line_;
}

ofColor AppLine::GetColor() {
    return color_;
}

float AppLine::GetWidth() {
    return radius_*2;
}

void AppLine::AddPoint(ofPoint& pt) {
    line_->addVertex(pt);
}