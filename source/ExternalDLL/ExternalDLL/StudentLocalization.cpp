#include "StudentLocalization.h"

bool StudentLocalization::stepFindHead(const IntensityImage &image, FeatureMap &features) const {
	Feature topOfHead = Feature(Feature::FEATURE_HEAD_TOP);
	Feature leftOfHead = Feature(Feature::FEATURE_HEAD_LEFT_SIDE);
	Feature rightOfHead = Feature(Feature::FEATURE_HEAD_RIGHT_SIDE);

	float threshhold = 1.25f;

	int imageWidth = image.getWidth();
	int imageHeight = image.getHeight();
	{//Top of head
		int leftTop = imageWidth / 4;
		int rightTop = leftTop + imageWidth / 2;
		int testPoints = 32;
		int testDivision = imageWidth / 2 / (testPoints - 1);
		int yDevision = 4;
		bool topOfHeadFound = false;

		int y = yDevision;
		while (y < imageHeight && !topOfHeadFound){
			for (int div = 0; div < testPoints; div++){
				if (image.getPixel(leftTop + testDivision * div, y) * threshhold < image.getPixel(leftTop + testDivision * div, y - yDevision)){
					topOfHeadFound = true;
					topOfHead.addPoint(Point2D<double>(leftTop + testDivision * div, y));
					break;
				}
			}
			y+= yDevision;
		}
		if (!topOfHeadFound){
			return false;
		}
	}

	{//Left and right
		int top = topOfHead.getY();
		int bottom = top + imageHeight / 2;
		int testPoints = 32;
		int testDivision = imageHeight / 2 / (testPoints - 1);
		int xDevision = 4;

		bool leftFound = false, rightFound = false;

		int i = xDevision;
		while (i < imageWidth / 2 && (!leftFound || !rightFound)){
			for (int div = 0; div < testPoints; div++){
				int y = top + testDivision * div;
				if (!leftFound){
					int x = i;
					if (image.getPixel(x, y) * threshhold < image.getPixel(x, y - testDivision)){
						leftFound = true;
						leftOfHead.addPoint(Point2D<double>(x, y));
					}
				}
				if (!rightFound){
					int x = imageWidth - i;
					if (image.getPixel(x, y) * threshhold < image.getPixel(x, y - testDivision)){
						rightFound = true;
						rightOfHead.addPoint(Point2D<double>(x, y));
					}
				}
			}
			i += xDevision;
		}
		if (!leftFound || !rightFound){
			return false;
		}
	}

	features.putFeature(topOfHead);
	features.putFeature(leftOfHead);
	features.putFeature(rightOfHead);
	return true;
}

bool StudentLocalization::stepFindNoseMouthAndChin(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindChinContours(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindNoseEndsAndEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindExactEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}