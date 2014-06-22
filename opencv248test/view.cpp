#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>

void view(char *name,IplImage *img)
{
	cvNamedWindow(name, CV_WINDOW_AUTOSIZE);
	cvShowImage(name, img);
}