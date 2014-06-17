#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>



int threshold(IplImage *img, IplImage *t_img)
{
	IplImage *src_img = 0, *dst_img;
	src_img = cvLoadImage("outputimg.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//src_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	dst_img = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);

	//cvCvtColor(img, src_img, CV_BGR2GRAY);
	//cvSmooth (src_img, src_img, CV_GAUSSIAN, 5);//平均化

	// (1)二値化（大津の手法を利用）
	cvThreshold (src_img, dst_img, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	t_img = dst_img;
	cvSaveImage("Threshold_outputimg2.jpg", dst_img);

	return 0;x
}
