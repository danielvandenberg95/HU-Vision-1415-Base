#include "RGBImageStudent.h"

RGBImageStudent::RGBImageStudent() : RGBImage() {
}

RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) : RGBImage() {
	set(other);
}


RGBImageStudent::RGBImageStudent(const int width, const int height) : RGBImage() {
	set(width, height);
}

RGBImageStudent::~RGBImageStudent() {
	for (int x = 0; x < getWidth(); x++){
		delete pixMap[x];
	}
	delete pixMap;
}

void RGBImageStudent::set(const int width, const int height) {
	for (int x = 0; x < getWidth(); x++){
		delete pixMap[x];
	}
	delete pixMap;
	RGBImage::set(width, height);
	pixMap = new RGB*[width];
	for (int x = 0; x < width; x++){
		pixMap[x] = new RGB[height];
	}
}

void RGBImageStudent::set(const RGBImageStudent &other) {
	for (int x = 0; x < getWidth(); x++){
		delete pixMap[x];
	}
	delete pixMap;
	RGBImage::set(other.getWidth(), other.getHeight());

	for (int x = 0; x < getWidth(); x++){
		for (int y = 0; y < getHeight(); y++){
			pixMap[x][y] = other.getPixel(x, y);
		}
	}
}

void RGBImageStudent::setPixel(int x, int y, RGB pixel) {
	pixMap[x][y] = pixel;
}

void RGBImageStudent::setPixel(int i, RGB pixel) {
	//int throwError = 0, e = 1 / throwError;
	pixMap[i%getWidth()][i / getWidth()] = pixel;
}

RGB RGBImageStudent::getPixel(int x, int y) const {
	return pixMap[x][y];
}

RGB RGBImageStudent::getPixel(int i) const {
	return pixMap[i%getWidth()][i / getWidth()];
}