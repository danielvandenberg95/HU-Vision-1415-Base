#include "StudentPreProcessing.h"
#include "GrayscaleAlgorithm.h"
#include "ImageFactory.h"
#include "IntensityImageStudent.h"
#include <iostream>
#include "basetimer.h"
#include <fstream>
#include <algorithm>

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
#define NEWSIZE 200.0f
	double scale = std::max(image.getWidth() / NEWSIZE, image.getHeight() / NEWSIZE);
	IntensityImage* result = ImageFactory::newIntensityImage(image.getWidth() / scale, image.getHeight() / scale);
	for (int x = 0; x < (image.getWidth() / scale); x++){
		for (int y = 0; y < (image.getHeight() / scale); y++){
			double oldX = x * scale, oldY = y * scale;
			if (oldX < 0 || oldY < 0 || oldX >= image.getWidth() - 1 || oldY >= image.getHeight() - 1){
				result->setPixel(x,y, 0);
				continue;
			}
			float v00 = image.getPixel(oldX, oldY);
			float v01 = image.getPixel(oldX, oldY + 1);
			float v10 = image.getPixel(oldX + 1, oldY);
			float v11 = image.getPixel(oldX + 1, oldY + 1);
			#define t0 ((std::ceil(oldX) - oldX) * v00 + (oldX - std::floor(oldX)) * v10);
			#define t1 ((std::ceil(oldX) - oldX) * v01 + (oldX - std::floor(oldX)) * v11);
			float res = (std::ceil(oldY) - oldY) * t0 + (oldY - std::floor(oldY)) * t1;
			result->setPixel(x, y, v00);
		}
	}
	return result;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	const int size = 9;
	const int halfSize = floor(size / 2.0f);
	int mask[9][9] = { { 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 1, 1, 1, -4, -4, -4, 1, 1, 1 },
	{ 1, 1, 1, -4, -4, -4, 1, 1, 1 },
	{ 1, 1, 1, -4, -4, -4, 1, 1, 1 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 } };

	float z = -0.125;
	float a = -0.25;
	float b = -0.75;
	float c = -0.5;
	float d = -1.5;
	float e = -1.25;
	float f = -1;

	/*float mask[9][9] = { 
	{ 0, 0, z, c, b, c, z, 0, 0 },
	{ 0, z, a, b, e, b, a, z, 0 },
	{ z, a, c, d, f, d, c, a, z },
	{ c, b, d, 2.25, 3.75, 2.25, d, b, c },
	{ b, e, f, 3.75, 21.5, 3.75, f, e, b },
	{ c, b, d, 2.25, 3.75, 2.25, d, b, c },
	{ z, a, c, d, f, d, c, a, z },
	{ 0, z, a, b, e, b, a, z, 0 },
	{ 0, 0, z, c, b, c, z, 0, 0 } };*/

	//int mask[3][3] = { { 0, 1, 0 }, { 1, -4, 1 }, { 0, 1, 0 } };
	//float mask[3][3] = { { 0, 0.5, 0 }, { 0.5, -2, 0.5 }, { 0, 0.5, 0 } };
	//int mask[3][3] = { { 0, 4, 0 }, { 4,-16,4 }, { 0, 4, 0 } };

	IntensityImage * res = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	for (int x = halfSize; x < image.getWidth() - halfSize; x++){
		for (int y = halfSize; y < image.getHeight() - halfSize; y++){
			int value = 0;
			for (int _x = 0; _x < size; _x++){
				for (int _y = 0; _y < size; _y++){
					value += image.getPixel(x + _x - halfSize, y + _y - halfSize) *mask[_x][_y] ;
				}
			}
			value = value*2 + 127;
			if (value < 0){
				value = 0;
			}
			else if (value > 255){
				value = 255;
			}
			res->setPixel(x, y, value);
		}
	}

	for (int x = 0; x < image.getWidth(); x++){
		for (int y = 0; y < halfSize; y++){
			res->setPixel(x, y, 0);
			res->setPixel(x, image.getHeight() - y - 1, 0);
		}
	}

	for (int y = 0; y < image.getHeight(); y++){
	for (int x = 0; x < halfSize; x++){
			res->setPixel(x, y, 0);
			res->setPixel(image.getWidth() - x - 1,y, 0);
		}
	}
	return res;
}


IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
#define T
#ifdef T
	IntensityImage * res = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	for (int x = 0; x < image.getWidth(); x++){
		for (int y = 0; y < image.getHeight(); y++){

			int value = 255 * (image.getPixel(x, y) <255);

			res->setPixel(x, y, value);
		}
	}
	return res;
#else
	return ImageFactory::newIntensityImage(image);
#endif
}