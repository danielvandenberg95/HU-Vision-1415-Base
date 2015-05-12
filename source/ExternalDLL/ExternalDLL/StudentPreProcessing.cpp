#include "StudentPreProcessing.h"
#include "GrayscaleAlgorithm.h"
#include "ImageFactory.h"
#include "IntensityImageStudent.h"
#include <iostream>
#include "basetimer.h"
#include <fstream>

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	BaseTimer baseTimer;
	baseTimer.start();
	IntensityImage* res = new IntensityImageStudent(image);
	baseTimer.stop();
	std::ofstream myfile;
	myfile.open("speedTest.txt", std::ofstream::ate);
	myfile << "Student:\n[" << baseTimer.elapsedSeconds() << ";" << baseTimer.elapsedMilliSeconds() << ";" << baseTimer.elapsedMicroSeconds() << "]\n";
	myfile.close();
	return res;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	const int size = 9;
	const int halfSize = floor(size / 2.0f);
	int mask[9][9] = { { 0, 0, 0, -1, -1, -1, 0, 0, 0 },
						{ 0, 0, 0, -1, -1, -1, 0, 0, 0 },
						{ 0, 0, 0, -1, -1, -1, 0, 0, 0 },
						{ -1, -1, -1, 4, 4, 4, -1, -1, -1 },
						{- 1,- 1,- 1, 4, 4, 4, -1, -1, -1 },
						{- 1,- 1,- 1, 4, 4, 4, -1, -1, -1 },
						{ 0, 0, 0,- 1,- 1, -1, 0, 0, 0 },
						{ 0, 0, 0,- 1, -1, -1, 0, 0, 0 },
						{ 0, 0, 0, -1, -1, -1, 0, 0, 0 } };

	IntensityImage * res = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	for (int x = halfSize; x < image.getWidth() - halfSize; x++){
		for (int y = halfSize; y < image.getHeight() - halfSize; y++){
			int value = 127;
			for (int _x = 0; _x < size; _x++){
				for (int _y = 0; _y < size; _y++){
					value += image.getPixel(x + _x - halfSize, y + _y - halfSize) *mask[_x][_y];
				}
			}
			if (value < 0){
				value = 0;
			}
			else if (value > 255){
				value = 255;
			}
			res->setPixel(x, y, value);
		}
	}
	return res;
}


IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	IntensityImage * res = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	for (int x = 0; x < image.getWidth(); x++){
		for (int y = 0; y < image.getHeight(); y++){

			int value = 255 * (image.getPixel(x, y) != 0);

			res->setPixel(x, y, value);
		}
	}
	return res;
}