#include "IntensityImageStudent.h"

IntensityImageStudent::IntensityImageStudent() : IntensityImage() {
}

IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &other) : IntensityImage() {
	set(other);
}

IntensityImageStudent::IntensityImageStudent(const int width, const int height) : IntensityImage() {
	set(width, height);
}

IntensityImageStudent::~IntensityImageStudent() {
	for (int x = 0; x < getWidth(); x++){
		delete pixMap[x];
	}
	delete pixMap;
}

void IntensityImageStudent::set(const int width, const int height) {
	for (int x = 0; x < getWidth(); x++){
		delete pixMap[x];
	}
	delete pixMap;
	IntensityImage::set(width, height);
	pixMap = new Intensity*[width];
	for (int x = 0; x < width; x++){
		pixMap[x] = new Intensity[height];
	}
}

void IntensityImageStudent::set(const IntensityImageStudent &other) {
	for (int x = 0; x < getWidth(); x++){
		delete pixMap[x];
	}
	delete pixMap;
	IntensityImage::set(other.getWidth(), other.getHeight());

	for (int x = 0; x < getWidth(); x++){
		for (int y = 0; y < getHeight(); y++){
			pixMap[x][y] = other.getPixel(x, y);
		}
	}
}

void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
	pixMap[x][y] = pixel;
}

void IntensityImageStudent::setPixel(int i, Intensity pixel) {
	pixMap[i%getWidth()][i / getWidth()] = pixel;
}

Intensity IntensityImageStudent::getPixel(int x, int y) const {
	return pixMap[x][y];
}

Intensity IntensityImageStudent::getPixel(int i) const {
	return pixMap[i%getWidth()][i / getWidth()];
}