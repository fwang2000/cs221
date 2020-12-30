#include <iostream>
#include "HSLAPixel.h"

using namespace cs221util;

HSLAPixel::HSLAPixel() {

    h = 0;
    s = 0;
    l = 1.0;
    a = 1.0;
}

HSLAPixel::HSLAPixel(double h, double s, double l) {

	this->h = h;
    this->s = s;
    this->l = l;
    this->a = 1.0;
}

HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha) {

    h = hue;
    s = saturation;
    l = luminance;
    a = alpha;
}