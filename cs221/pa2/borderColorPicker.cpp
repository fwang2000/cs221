#include "borderColorPicker.h"
#include "math.h"

borderColorPicker::borderColorPicker(unsigned int borderSize, HSLAPixel fillColor, PNG &img, double tolerance)
{
    /* your code here */
    this->borderSize = borderSize;
    this->fillColor = fillColor;
    this->img = img;
    this->tolerance = tolerance;
}

HSLAPixel borderColorPicker::operator()(point p)
{
    /* your code here */
	if (p.x < borderSize || p.y < borderSize || (p.x + borderSize >= img.width()) || (p.y + borderSize >= img.height())) {

      return fillColor;

    } else {

      for (int i = p.x - borderSize; i <= p.x + borderSize; i++) {

        for (int j = p.y - borderSize; j <= p.y + borderSize; j++) {

          HSLAPixel a = *img.getPixel(i, j);
          HSLAPixel b = *img.getPixel(p.x, p.y);

          if ((i-p.x) == 0 && (j-p.y) == 0) {

                continue;
            }

          int xDist = ((int) p.x - (int) p.c.x) * ((int) p.x - (int) p.c.x);
          int yDist = ((int) p.y - (int) p.c.y) * ((int) p.y - (int) p.c.y);

          if (xDist + yDist > borderSize* borderSize) {
                  continue;
              }

          double cDistance = a.dist(b);

          if (cDistance >= tolerance) {

            return fillColor;
          }

          if (i < 0 || i > ((int)img.width()-1)) {

                return fillColor;
            }

          if (j < 0 || j > ((int)img.height()-1)) {
            
                return fillColor;
            }

          return *img.getPixel(i, j);
        }
      }

      return *img.getPixel(p.x, p.y);
    }
}
