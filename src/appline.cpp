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

bool AppLine::IsThick() {
    return thick_;
}

void AppLine::AddPoint(ofPoint& pt) {
    line_->addVertex(pt);
}