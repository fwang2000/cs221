#include <typeinfo>
#include "stats.h"
#include <iostream>
#include <math.h>
#include <string.h>

stats::stats(PNG & im){

	for (unsigned int i = 0; i < im.width(); i++) {

		vector<long> redcolumn(im.height());
		vector<long> greencolumn(im.height());
		vector<long> bluecolumn(im.height());

		vector<long> sqredcolumn(im.height());
		vector<long> sqgreencolumn(im.height());
		vector<long> sqbluecolumn(im.height());
		
		for (unsigned int j = 0; j < im.height(); j++) {
			
			RGBAPixel * pixel = im.getPixel(i, j);
			
			long prevRed = 0;
			long prevGreen = 0;
			long prevBlue = 0;
			
			long prevRedSq = 0;
			long prevGreenSq = 0;
			long prevBlueSq = 0;
			
			
			if (j > 0) {	

				prevRed = redcolumn[j - 1];
				prevGreen = greencolumn[j - 1];
				prevBlue = bluecolumn[j - 1];
				
				prevRedSq = sqredcolumn[j - 1];
				prevGreenSq = sqgreencolumn[j - 1];
				prevBlueSq = sqbluecolumn[j - 1];
			}
			
			long red = pixel->r;
			long green = pixel->g;
			long blue = pixel->b;

			long sqred = red * red;
			long sqgreen = green * green; 
			long sqblue = blue * blue;
			
			if (i == 0 && j == 0) {

				redcolumn[j] = red;
				greencolumn[j] = green;
				bluecolumn[j] = blue;
				
				sqredcolumn[j] = sqred;
				sqgreencolumn[j] = sqgreen;
				sqbluecolumn[j] = sqblue;
			}

			if (i == 0 && j > 0) {

				redcolumn[j] = red + prevRed;
				greencolumn[j] = green + prevGreen;
				bluecolumn[j] = blue + prevBlue;
				
				sqredcolumn[j] = sqred + prevRedSq;
				sqgreencolumn[j] = sqgreen + prevGreenSq;
				sqbluecolumn[j] = sqblue + prevBlueSq;
			}

			if (i > 0 && j == 0){

				redcolumn[j] = sumRed[i - 1][j] + red;
				greencolumn[j] = sumGreen[i - 1][j] + green;
				bluecolumn[j] = sumBlue[i - 1][j] + blue;
				
				sqredcolumn[j] = sumsqRed[i - 1][j] + sqred;
				sqgreencolumn[j] = sumsqGreen[i - 1][j] + sqgreen;
				sqbluecolumn[j] = sumsqBlue[i - 1][j] + sqblue;
			}

			if (i > 0 && j > 0){

				redcolumn[j] = sumRed[i - 1][j] + red + prevRed - sumRed[i - 1][j - 1];
				greencolumn[j] = sumGreen[i-1][j] + green + prevGreen - sumGreen[i-1][j-1];
				bluecolumn[j] = sumBlue[i - 1][j] + blue + prevBlue - sumBlue[i - 1][j - 1];
				
				sqredcolumn[j] = sumsqRed[i - 1][j] + sqred + prevRedSq - sumsqRed[i - 1][j - 1];
				sqgreencolumn[j] = sumsqGreen[i - 1][j] + sqgreen + prevGreenSq - sumsqGreen[i - 1][j - 1];
				sqbluecolumn[j] = sumsqBlue[i - 1][j] + sqblue + prevBlueSq - sumsqBlue[i - 1][j - 1];
			}			

		}
			
			sumRed.push_back(redcolumn);
			sumGreen.push_back(greencolumn);
			sumBlue.push_back(bluecolumn);

			sumsqRed.push_back(sqredcolumn);
			sumsqGreen.push_back(sqgreencolumn);
			sumsqBlue.push_back(sqbluecolumn);

	}

}

long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){

	long result = 0;	

	if (channel == 'r') {

		if (ul.first == 0 && ul.second == 0) {

			return sumRed[lr.first][lr.second];

		} else if (ul.first == 0) {

			result = sumRed[lr.first][lr.second] - sumRed[lr.first][ul.second - 1];

		} else if (ul.second == 0) {

			result = sumRed[lr.first][lr.second] - sumRed[ul.first - 1][lr.second];

		} else {

			result = sumRed[lr.first][lr.second] - (sumRed[lr.first][ul.second - 1] + sumRed[ul.first - 1][lr.second] - sumRed[ul.first - 1][ul.second - 1]);
		}

	} else if (channel == 'b') {

		if (ul.first == 0 && ul.second == 0) {

			return sumBlue[lr.first][lr.second];

		} else if (ul.first == 0) {

			result = sumBlue[lr.first][lr.second] - sumBlue[lr.first][ul.second - 1];

		} else if (ul.second == 0) {

			result = sumBlue[lr.first][lr.second] - sumBlue[ul.first - 1][lr.second];

		} else {

			result = sumBlue[lr.first][lr.second] - (sumBlue[lr.first][ul.second - 1] + sumBlue[ul.first - 1][lr.second] - sumBlue[ul.first - 1][ul.second - 1]);
		}

	} else if (channel == 'g') {

		if (ul.first == 0 && ul.second == 0) {

			return sumGreen[lr.first][lr.second];

		} else if (ul.first == 0) {

			result = sumGreen[lr.first][lr.second] - sumGreen[lr.first][ul.second - 1];

		} else if (ul.second == 0) {

			result = sumGreen[lr.first][lr.second] - sumGreen[ul.first - 1][lr.second];

		} else {

			result = sumGreen[lr.first][lr.second] - (sumGreen[lr.first][ul.second - 1] + sumGreen[ul.first - 1][lr.second] - sumGreen[ul.first - 1][ul.second - 1]);
		}
	}

	return result;

}

long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){

	long result = 0;	

	if (channel == 'r') {

		if (ul.first == 0 && ul.second == 0) {

			return sumsqRed[lr.first][lr.second];

		} else if (ul.first == 0) {

			result = sumsqRed[lr.first][lr.second] - sumsqRed[lr.first][ul.second - 1];

		} else if (ul.second == 0) {

			result = sumsqRed[lr.first][lr.second] - sumsqRed[ul.first - 1][lr.second];

		} else {

			result = sumsqRed[lr.first][lr.second] - (sumsqRed[lr.first][ul.second - 1] + sumsqRed[ul.first - 1][lr.second] - sumsqRed[ul.first - 1][ul.second - 1]);
		}

	} else if (channel == 'b') {

		if (ul.first == 0 && ul.second == 0) {

			return sumsqBlue[lr.first][lr.second];

		} else if (ul.first == 0) {

			result = sumsqBlue[lr.first][lr.second] - sumsqBlue[lr.first][ul.second - 1];

		} else if (ul.second == 0) {

			result = sumsqBlue[lr.first][lr.second] - sumsqBlue[ul.first - 1][lr.second];

		} else {

			result = sumsqBlue[lr.first][lr.second] - (sumsqBlue[lr.first][ul.second - 1] + sumsqBlue[ul.first - 1][lr.second] - sumsqBlue[ul.first - 1][ul.second - 1]);
		}

	} else if (channel == 'g') {

		if (ul.first == 0 && ul.second == 0) {

			return sumsqGreen[lr.first][lr.second];

		} else if (ul.first == 0) {

			result = sumsqGreen[lr.first][lr.second] - sumsqGreen[lr.first][ul.second - 1];

		} else if (ul.second == 0) {

			result = sumsqGreen[lr.first][lr.second] - sumsqGreen[ul.first - 1][lr.second];

		} else {

			result = sumsqGreen[lr.first][lr.second] - (sumsqGreen[lr.first][ul.second - 1] + sumsqGreen[ul.first - 1][lr.second] - sumsqGreen[ul.first - 1][ul.second - 1]);
		}
	}

	return result;

}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

	return (lr.first - ul.first + 1) * (lr.second - ul.second + 1);

}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
long stats::getScore(pair<int,int> ul, pair<int,int> lr){

	long red = getSum('r', ul, lr) * getSum('r', ul, lr);
	long green = getSum('g', ul, lr) * getSum('g', ul, lr);
	long blue = getSum('b', ul, lr) * getSum('b', ul, lr);

	long area = rectArea(ul, lr);

	long redvar = getSumSq('r', ul, lr) - red/area;
	long greenvar = getSumSq('g', ul, lr) - green/area;
	long bluevar = getSumSq('b', ul, lr) - blue/area;

	return redvar + greenvar + bluevar;
}
		
RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

	long red = getSum('r', ul, lr);
	long green = getSum('g', ul, lr);
	long blue = getSum('b', ul, lr);

	long area = rectArea(ul, lr);

	RGBAPixel pixel = RGBAPixel(red/area, green/area, blue/area);
	return pixel;
}
