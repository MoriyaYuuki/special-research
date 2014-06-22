#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>

void DestroyView(char *name ,IplImage *img)
{
	cvDestroyWindow(name);
	cvReleaseImage(&img);
}