#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>
#include <Tchar.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace cv;

int CAM();
int histogram(int argc, char **argv);
int histogram2(IplImage* img);
void get_imageData(char* out_filename, IplImage* img);
void Mouse(int event, int x, int y, int flags, void *param);
int	threshold(IplImage* &img,IplImage* &t_img);

int main(int argc, char **argv)
{
	IplImage *image=0,*gray_image=0,*threshold_image=0;
	//CvPoint *mouse=0;
	char name[100];

	while (1){
		/*画像読み込み*/
		CAM();
		image = cvLoadImage("outputimg.jpg", CV_LOAD_IMAGE_ANYCOLOR);
		gray_image = cvLoadImage("outputimg.jpg", CV_LOAD_IMAGE_GRAYSCALE);

		cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
		cvShowImage("Image", image);
		cvNamedWindow("Gray_Image", CV_WINDOW_AUTOSIZE);
		cvShowImage("Gray_Image", gray_image);
		cvWaitKey(0);
		cvDestroyWindow("Image");
		cvReleaseImage(&image);
		cvDestroyWindow("Gray_Image");
		cvReleaseImage(&gray_image);

		/*ヒストグラムの表示*/
		//histogram2(gray_image);

		/*二値化*/
		threshold(gray_image, threshold_image);

		cvNamedWindow("Threshold_Image", CV_WINDOW_AUTOSIZE);
		cvShowImage("Threshold_Image", threshold_image);
		cvWaitKey(0);
		cvDestroyWindow("Threshold_Image");
		cvReleaseImage(&threshold_image);

		//x = mouse->x;
		//y = mouse->y;
		//printf("%d,%d",x,y);
		
		//printf("%d\n", check);
		//printf("%d,%d\n",x,y);
		getchar();
	}
	return 0;
}

//std::cout << "outfile name(.txt) = ";
//std::cin >> name;
//get_imageData(name, gray_image);
