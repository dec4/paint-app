#include "appline.h"


//----- CONSTRUCTORS -----//

AppLine::AppLine() {
    line_ = new ofPolyline();
}

AppLine::AppLine(ofPoint& start_point, ofColor& color, float& radius) {
    color_ = color;
    radius_ = radius;
    line_ = new ofPolyline();
    line_->addVertex(start_point);
}


//----- GETTERS -----//

ofPolyline AppLine::GetLine() {
    return *line_;
}

ofColor AppLine::GetColor() {
    return color_;
}

float AppLine::GetWidth() {
    return radius_*2;
}


//----- MODIFIERS -----//

/**
 * Add point to object's ofPolyline
 */
void AppLine::AddPoint(ofPoint& pt) {
    line_->addVertex(pt);
}