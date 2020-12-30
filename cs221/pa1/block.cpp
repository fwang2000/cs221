#include "block.h"


  // set values in data attribute, based on a dimension x dimension square region
  //   with upper-left corner at (left, upper) in the input PNG image
  // The orientation of the pixels in the data vector must match the orientation
  //   of the pixels in the PNG.
  // PRE: upper and left (and upper + dimension, left + dimension) are valid
  //        vector indices
  void Block::Build(PNG& im, int upper, int left, int dimension) {

  	for (int i = left; i < left + dimension; i++) {

	    vector<HSLAPixel> pixelColumn;

	    for (int j = upper; j < upper + dimension; j++) {

	      pixelColumn.push_back(*im.getPixel(i, j));

	    }

   		data.push_back(pixelColumn);
  	}
  }

  // write the pixel colour data fom data attribute into im,
  //   with upper-left corner at (left, upper)
  // PRE: upper and left (and upper + dimension, left + dimension) are valid
  //        vector indices
  void Block::Render(PNG& im, int upper, int left) const {


	for(int i = 0; i < Dimension(); i++) {

	    for(int j = 0; j < Dimension(); j++) {

	      *im.getPixel(i + left, j + upper) = data.at(i).at(j);

	    }
	}
  }

  // "Reverse" the Hue and Luminance channels for each pixel in the data attribute
  //   to simulate a photo-negative effect.
  // Refer to the HSLAPixel documentation to determine an appropriate transformation
  //   for "reversing" hue and luminance.
  void Block::Negative() {

   	for(int i = 0; i < Dimension(); i++) {

   		for (int j = 0; j < Dimension(); j++) {

        data.at(i).at(j).h = data.at(i).at(j).h + 180;

        if (data.at(i).at(j).h >= 360) {

          data.at(i).at(j).h = data.at(i).at(j).h - 360;
        }

  			data.at(i).at(j).l = 1 - data.at(i).at(j).l;
   		}
   	}
  }

  // Return the horizontal (or vertical) size of the data block's image region
  int  Block::Dimension() const {

  	return data.size();
  }

