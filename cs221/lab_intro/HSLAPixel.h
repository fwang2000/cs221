#ifndef CS221UTIL_HSLAPixel_H
#define CS221UTIL_HSLAPixel_H

using namespace cs221util;

namespace cs221util {

  class HSLAPixel{

    public:

      double h, s, l, a;

      HSLAPixel();

      HSLAPixel(double h, double s, double l);

      HSLAPixel(double h, double s, double l, double a);

  };
}

#endif 