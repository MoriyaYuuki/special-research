#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>



int threshold(IplImage* &img, IplImage* &t_img)
{
	IplImage *src_img = 0, *dst_img;
	//src_img = cvLoadImage("outputimg.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	////src_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	//dst_img = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);

	//cvCvtColor(img, src_img, CV_BGR2GRAY);
	//cvSmooth (src_img, src_img, CV_GAUSSIAN, 5);//•½‹Ï‰»
	cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Image", t_img);
	// (1)‘å’Ã‚ÌŽè–@
	//cvThreshold (src_img, dst_img, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	
	// (2)‹P“x•½‹Ï
	cvThreshold(img, t_img, 126, 255, CV_THRESH_BINARY);

	//cvSaveImage("Threshold_outputimg3.jpg", dst_img);

	return 0;
}
