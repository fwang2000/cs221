#include "fadeColorPicker.h"

fadeColorPicker::fadeColorPicker(double fade)
{
    /* your code here */
    fadeFactor = fade;
}

HSLAPixel fadeColorPicker::operator()(point p)
{
    /* your code here */
    int distSq = (int) pow((int) p.x - (int) p.c.x, 2) + (int) pow((int) p.y - (int) p.c.y, 2);

 	HSLAPixel fadedColor;
 	fadedColor.h = p.c.color.h;
 	fadedColor.s = p.c.color.s;
 	fadedColor.l = p.c.color.l * pow(fadeFactor, sqrt(distSq));
 	return fadedColor;   
}
