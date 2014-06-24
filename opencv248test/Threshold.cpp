#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>


void threshold(IplImage* img, IplImage* t_img)
{
	IplImage *src_img = 0, *dst_img;
	int x;
	//src_img = cvLoadImage("outputimg.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//src_img = cvCreateImage(cvGetSize(*img), IPL_DEPTH_8U, 1);
	//dst_img = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);

	//cvSmooth (src_img, src_img, CV_GAUSSIAN, 5);//•½‹Ï‰»
	cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Image", img);
	
	// (1)‘å’Ã‚ÌŽè–@
	cvThreshold (img, t_img, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	cvSaveImage("Otsu117_outputimg.jpg", t_img);
	// (2)‹P“x•½‹Ï
	cvThreshold(img, t_img, 127, 255, CV_THRESH_BINARY);
	cvSaveImage("ave127_outputimg.jpg", t_img);

	cvThreshold(img, t_img, 100, 255, CV_THRESH_BINARY);
	cvSaveImage("100_outputimg.jpg", t_img);

	cvThreshold(img, t_img, 50, 255, CV_THRESH_BINARY);
	cvSaveImage("50_outputimg.jpg", t_img);

	cvThreshold(img, t_img, 75, 255, CV_THRESH_BINARY);
	cvSaveImage("75_outputimg.jpg", t_img);
	//cvSaveImage("Threshold_outputimg3.jpg", dst_img);
}
