#ifndef CS221UTIL_HSLAPixel_H
#define CS221UTIL_HSLAPixel_H

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