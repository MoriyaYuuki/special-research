//#include <opencv2/opencv.hpp>
//#include <opencv2/opencv_lib.hpp>
//
//
//void threshold(IplImage* img, IplImage* t_img, char* filename)
//{
//	IplImage *src_img = 0, *dst_img;
//	int x;
//	char exfilename[32];/*拡張子付きファイル名*/
//
//	//src_img = cvLoadImage("outputimg.jpg", CV_LOAD_IMAGE_GRAYSCALE);
//	//src_img = cvCreateImage(cvGetSize(*img), IPL_DEPTH_8U, 1);
//	//dst_img = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
//
//	//cvSmooth (src_img, src_img, CV_GAUSSIAN, 5);//平均化
//	cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
//	cvShowImage("Image", img);
//
//	cvThreshold(img, t_img, 100, 255, CV_THRESH_BINARY);
//	sprintf(exfilename, "100_%s.jpg", filename);
//	cvSaveImage(exfilename, t_img);
//
//	cvThreshold(img, t_img, 50, 255, CV_THRESH_BINARY);
//	sprintf(exfilename, "50%s.jpg", filename);
//	cvSaveImage(exfilename, t_img);
//
//	cvThreshold(img, t_img, 75, 255, CV_THRESH_BINARY);
//	sprintf(exfilename, "75%s.jpg", filename);
//	cvSaveImage(exfilename, t_img);
//
//	// (1)輝度平均
//	x=cvThreshold(img, t_img, 127, 255, CV_THRESH_BINARY);
//	sprintf(exfilename, "ave%d%s.jpg", x, filename);
//	cvSaveImage(exfilename, t_img);
//
//	// (2)大津の手法
//	x = cvThreshold(img, t_img, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
//	sprintf(exfilename, "Otsu%d%s.jpg", x, filename);
//	cvSaveImage(exfilename, t_img);
//}
