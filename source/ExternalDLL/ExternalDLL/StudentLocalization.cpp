#include "StudentLocalization.h"

bool StudentLocalization::stepFindHead(const IntensityImage &image, FeatureMap &features) const {
	/*Feature topOfHead = Feature(Feature::FEATURE_HEAD_TOP);
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
		/*int top = topOfHead.getY();
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
		int * black = new int[image.getHeight()];
		int * white = new int[image.getHeight()];
		for (int y = 0; y < image.getHeight(); y++){
			for (int x = 0; x < image.getWidth(); x++){
				(image.getPixel(x, y) == 0 ? black : white)[y]++;
			}
			rightOfHead.addPoint(Point2D<double>(black[y], y));
		}

	}

	features.putFeature(topOfHead);
	features.putFeature(leftOfHead);
	features.putFeature(rightOfHead);
	return true;*/
	return false;
}

bool StudentLocalization::stepFindNoseMouthAndChin(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindChinContours(const IntensityImage &image, FeatureMap &features) const {
	
	# define PI         3.141592653589793238462643383279502884L
	#define VerticalOffset 10
	Point2D<double> MouthCenter = features.getFeature(Feature::FEATURE_MOUTH_CENTER).getPoints()[0];
	Feature chinCountor = Feature(Feature::FEATURE_CHIN_CONTOUR);
	
	for(int i = 0; i < 19; i++)
	{
		bool pointFound = false;
		int x = MouthCenter.x;
		int y = MouthCenter.y;
		int j = 0;
		while (x > features.getFeature(Feature::FEATURE_HEAD_LEFT_SIDE).getX() && x < features.getFeature(Feature::FEATURE_HEAD_RIGHT_SIDE).getX() && y > 0 && y < features.getFeature(Feature::FEATURE_CHIN).getY() && !pointFound){
			x = (int) std::round(MouthCenter.x + (j * std::sin((270 + (10*i)) * (PI/180))));
			y = (int)std::round(MouthCenter.y + VerticalOffset + (j * std::cos((270 + (10 * i)) * (PI / 180))));
			if(image.getPixel(x,y) == 0){
				pointFound = true;
				chinCountor.addPoint(Point2D<double>(x, y));
			}
			j++;
		}
	}
	features.putFeature(chinCountor);
	return true;
}

bool StudentLocalization::stepFindNoseEndsAndEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindExactEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}