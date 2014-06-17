#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>
#include <Tchar.h>

using namespace cv;

int CAM();
int histogram(int argc, char **argv);
void Mouse(int event, int x, int y, int flags, void *param);
int	threshold(IplImage *img,IplImage *t_img);

int main(int argc, char **argv)
{
	IplImage *image=0,gray_img, *threshold_img=0;
	//CvPoint *mouse=0;
	int check=0;
	int x=0, y=0;
	while (1){
		/*‰æ‘œ“Ç‚Ýž‚Ý*/
		CAM();
		image = cvLoadImage("outputimg.jpg", CV_LOAD_IMAGE_ANYCOLOR);

		/*“ñ’l‰»(‘å’Ã)*/
		threshold(image, threshold_img);

		/*‰æ‘œ•\Ž¦*/
		image = cvLoadImage("outputimg.jpg", CV_LOAD_IMAGE_ANYCOLOR);
		if (image == NULL) {
			fprintf(stderr, "“Çž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½.");
			return EXIT_FAILURE;
		}
		threshold_img = cvLoadImage("Threshold_outputimg.jpg", CV_LOAD_IMAGE_ANYCOLOR);
		
		cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
		cvNamedWindow("Threshold_Image", CV_WINDOW_AUTOSIZE);
		cvShowImage("Image", image);
		cvShowImage("Threshold_Image",threshold_img);
		cvWaitKey(0);
		cvDestroyWindow("Image");
		cvDestroyWindow("Threshold_Image");
		cvReleaseImage(&image);
		cvReleaseImage(&threshold_img);

		/*‰æ‘œ•\Ž¦*/
		image = cvLoadImage("Threshold_outputimg.jpg", CV_LOAD_IMAGE_ANYCOLOR);
		if (image == NULL) {
			fprintf(stderr, "“Çž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½.");
			return EXIT_FAILURE;
		}
		cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
		cvShowImage("Image", image);
		cvSetMouseCallback("Image", Mouse/*,mouse*/);
		cvWaitKey(0);
		histogram(argc,argv);
		//x = mouse->x;
		//y = mouse->y;
		//printf("%d,%d",x,y);
		
		//printf("%d\n", check);
		//printf("%d,%d\n",x,y);
		getchar();
	}
	return 0;
}