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
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}