
#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>
#include <Tchar.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <direct.h>

using namespace cv;

void CAM(char* filename);
int histogram(int argc, char **argv);
int histogram2(IplImage* img);
void get_imageData(char* filename, IplImage* img);
void Mouse(int event, int x, int y, int flags, void *param);
void threshold(IplImage* img, IplImage* t_img, char* filename);
void cutImage(IplImage* img, IplImage* cut_img);
void makeDirectory(const char* dirName);
int search_TransAngle(IplImage* img);
Mat TransMat(double angle);

typedef struct _data{
	int event, x=0, y=0, flag;
}Data;

typedef struct _cutdata{
	int x = 0, y = 0, width=0, hight=0;
}cutData;


/*時間の取得*/
time_t now = time(NULL);
struct tm *pnow = localtime(&now);

int main(int argc, char **argv)
{
	IplImage *image,*gray_image,*threshold_image,*point_image;
	Data data;
	cutData cut;
	const char *directoryName;
	char fileName[100], gray_fileName[100], threshold_fileName[100], point_fileName[100];
	CvRect roi;
	unsigned int sum=0;
	double ave = 0.0;
	double last_ave = 0.0;
	int i=0;


	while (1){
		/*ディレクトリの作成*/
		directoryName = "Image";
		makeDirectory(directoryName);

		/*画像読み込み*/
		sprintf(fileName, "Outimage_%d%02d%02d%02d%02d.jpg",
			pnow->tm_year + 1900, pnow->tm_mon + 1, pnow->tm_mday, pnow->tm_hour, pnow->tm_min);
		printf("%s\n", fileName);
		CAM(fileName);

		/*画像表示*/
		image = cvLoadImage(fileName, CV_LOAD_IMAGE_ANYCOLOR);
		cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
		cvShowImage("Image", image);
		cvWaitKey(0);
		cvDestroyWindow("Image");

		/*グレースケールの画像作成，表示，保存*/
		gray_image = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
		gray_image = cvLoadImage(fileName, CV_LOAD_IMAGE_GRAYSCALE);
		cvNamedWindow("Gray_Image", CV_WINDOW_AUTOSIZE);
		cvShowImage("Gray_Image", gray_image);
		sprintf(gray_fileName, "Gray_%s", fileName);
		printf("%s\n", gray_fileName);
		cvSaveImage(gray_fileName, gray_image);

		/*輝度の取得（グレースケール）*/
		directoryName = "ImageData";
		makeDirectory(directoryName);
		get_imageData(fileName, gray_image);
		histogram2(gray_image);

		///*二値化*/
		directoryName = "Thresholde";
		makeDirectory(directoryName);
		sprintf(threshold_fileName, "Thresholde_%s", fileName);
		printf("%s\n", threshold_fileName);
		threshold_image = cvCreateImage(cvGetSize(gray_image), IPL_DEPTH_8U, 1);
		threshold(gray_image, threshold_image, fileName);
		/*cvNamedWindow("Threshold_Image", CV_WINDOW_AUTOSIZE);
		cvShowImage("Threshold_Image", threshold_image);*/

		/*マウス座標取得*/
		printf("マウスで座標入力\n");
		cvSetMouseCallback("Gray_Image", Mouse, (void*)&data);
		printf("%d:%d\n", data.x, data.y);
		cvWaitKey(0);

		///*切り出し処理*/
		directoryName = "PointImage";
		makeDirectory(directoryName);
		cvSetImageROI(gray_image, cvRect(data.x - 50, data.y - 25, 100, 50));
		point_image = cvCreateImage(cvGetSize(gray_image), IPL_DEPTH_8U, 1);
		printf("%d:%d\n", point_image->height, point_image->width);
		cvCopy(gray_image, point_image);
		cvResetImageROI(gray_image);
		cvNamedWindow("Point_Image", CV_WINDOW_AUTOSIZE);
		cvShowImage("Point_Image", point_image);
		cvWaitKey(0);
		sprintf(point_fileName, "Point_Outimage_%d%02d%02d%02d%02d.jpg",
			pnow->tm_year + 1900, pnow->tm_mon + 1, pnow->tm_mday, pnow->tm_hour, pnow->tm_min);
		cvSaveImage(point_fileName, point_image);

		/*輝度の取得（切り出し後）*/
		directoryName = "PointImageData";
		makeDirectory(directoryName);
		get_imageData(point_fileName, point_image);
		histogram2(point_image);

		search_TransAngle(point_image);

		/*切り出し二値化*/
		directoryName = "ThresholdPointImage";
		makeDirectory(directoryName);
		threshold_image = cvCreateImage(cvGetSize(point_image), IPL_DEPTH_8U, 1);
		threshold(point_image, threshold_image, point_fileName);

		/*単語周辺のヒストグラム*/
		for (int i = 0; i < 25; i++){
			for (int j = 0; j < point_image->width; j++){
				sum += (uchar)point_image->imageData[point_image->widthStep * (25-i) + j];
				//printf("%d\n", (uchar)point_image->imageData[point_image->widthStep * 25 + j]);
			}
			ave = sum / point_image->width;
			if (ave > 160){
				roi.y = 25 - i;
				break;
			}
			sum = 0;
			printf("%lf , %lf , %d\n", ave, last_ave,i);
		}

		for (int i = 0; i < 25; i++){
			for (int j = 0; j < point_image->width; j++){
				sum += (uchar)point_image->imageData[point_image->widthStep * (25 + i) + j];
				//printf("%d\n", (uchar)point_image->imageData[point_image->widthStep * 25 + j]);
			}
			ave = sum / point_image->width;
			if (ave > 160) {
				roi.height = (25 + i) - roi.y;
				break;
			}
			sum = 0;
			printf("%lf , %lf , %d\n", ave, last_ave, i);
		}
		//printf("%d , %d\n", roi.y, roi.height);
		//cvSetImageROI(point_image, cvRect(0, roi.y , 100, roi.height));
		//cvSaveImage("result.bmp", point_image);
		//cvWaitKey(0);
		//while (ave - last_ave < 50){
		//	last_ave = ave;
		//	sum = 0;
		//	for (int j = 0; j < point_image->width; j++){
		//		sum += (uchar)point_image->imageData[point_image->widthStep * (25 + i) + j];
		//		//printf("%d\n", (uchar)point_image->imageData[point_image->widthStep * 25 + j]);
		//	}
		//	ave = sum / point_image->width;
		//	i++;
		//}
		//roi.height = 25 + i - roi.y;
		//while (ave - last_ave < 50){
		//	last_ave = ave;
		//	sum = 0;
		//	for (int j = 0; j < point_image->width; j++){
		//		sum += (uchar)point_image->imageData[point_image->widthStep * (25 - i) + j];
		//		//printf("%d\n", (uchar)point_image->imageData[point_image->widthStep * 25 + j]);
		//	}
		//	ave = sum / point_image->width;
		//	i++;
		//}
		//roi.y = 25 - i;
		//while (ave - last_ave < 50){
		//	last_ave = ave;
		//	sum = 0;
		//	for (int j = 0; j < point_image->width; j++){
		//		sum += (uchar)point_image->imageData[point_image->widthStep * (25 + i) + j];
		//		//printf("%d\n", (uchar)point_image->imageData[point_image->widthStep * 25 + j]);
		//	}
		//	ave = sum / point_image->width;
		//	i++;
		//}
		//roi.height = 25 + i - roi.y;



		//for (int i = 0; i < 25; i++){
		//	sum = 0;
		//	for (int j = 0; j < point_image->width; j++){
		//		sum += (uchar)point_image->imageData[point_image->widthStep * (25-i) + j];
		//		//printf("%d\n", (uchar)point_image->imageData[point_image->widthStep * 25 + j]);
		//	}
		//	std::cout << "aaaaaaaaaaaaaaaa" << std::endl;
		//	std::cout << sum << std::endl;
		//}
			
		

		/*printf("マウスで座標入力\n");
		cvSetMouseCallback("Point_Image", Mouse, (void*)&data);
		printf("%d:%d\n", data.x, data.y);
		for (int j = 0; j < point_image->width; j++){
			sum += point_image->imageData[point_image->widthStep * (data.y)];
		}
		sum = sum / point_image->width;
		std::cout << sum << std::endl;
		cvWaitKey(0);
		printf("%d:%d\n", data.x, data.y);
		std::cout << "cuthis" << std::endl;
		for (int j = 0; j < point_image->width; j++){
			sum += point_image->imageData[point_image->widthStep * (data.y) + j];
	    }
		sum / point_image->width;
		last_sum = sum;
		sum = 0;
		for (int i = 0; i < data.y; i++){
			for (int j = 0; j < point_image->width; j++){
				sum += point_image->imageData[point_image->widthStep * (data.y - i) + j];
			}
			sum=sum / point_image->width;
			printf("%lf\n",sum);
			if (abs(last_sum) - abs(sum) > 5000){
				cut.y = data.y - i;
				break;
			}
			last_sum = sum;
			sum = 0;
		}

		for (int j = 0; j < point_image->width; j++){
			sum += point_image->imageData[point_image->widthStep * (data.y) + j];
		}
		sum=sum / point_image->width;
		last_sum = sum;
		sum = 0;
		for (int i = 0; i < point_image->height - data.y; i++){
			for (int j = 0; j < point_image->width; j++){
				sum += point_image->imageData[point_image->widthStep * (data.y + i) + j];
			}
			sum / point_image->width;
			printf("aaaaaaaaaaaaaaaaaaaaaaaaa\n");
			printf("%lf\n", sum);
			if (abs(last_sum) - abs(sum) > 5000){
				cut.hight = cut.y-(data.y - i);
				break;
			}
			last_sum = sum;
			sum = 0;
		}

		std::cout << cut.y << "::" << cut.hight << std::endl;*/

		//cvDestroyWindow("Image");
		//cvReleaseImage(&image);
		//cvDestroyWindow("Gray_Image");
		//cvReleaseImage(&gray_image);

		///*データ出力*/
		//sprintf(exfileName, "99%s", fileName);
		//get_imageData(exfileName,gray_image);

		//cvNamedWindow("Threshold_Image", CV_WINDOW_AUTOSIZE);
		//cvShowImage("Threshold_Image", threshold_image);
		//cvWaitKey(0);
		//cvDestroyWindow("Threshold_Image");
		//cvReleaseImage(&threshold_image);

		getchar();
	}
	return 0;
}

void makeDirectory(const char *dirName)
{
	/*日付からディレクトリ作成*/
	char directoryName[100];
	sprintf(directoryName, "%s_%d%02d%02d",
			dirName,pnow->tm_year + 1900, pnow->tm_mon + 1, pnow->tm_mday);
	_mkdir(directoryName);
	_chdir(directoryName);
}

void CAM(char* filename)
{
	const double WIDTH = 640;  // 幅
	const double HEIGHT = 480; // 高さ
	const int CAMERANUM = 1; // カメラ番号
	/*画像関係*/
	CvCapture *capture = NULL;
	IplImage *frame = 0;
	int ch;

	// カメラ接続、幅と高さの設定
	capture = cvCreateCameraCapture(CAMERANUM);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, WIDTH);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);
	namedWindow("Capture", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
	while (1) {
		frame = cvQueryFrame(capture);
		cvShowImage("Capture", frame);
		ch = cvWaitKey(1); // 0 はディレイ時間 (ミリ秒単位)
		if (ch == 's'){
			cvSaveImage(filename, frame);
		}
		if (ch == '\x1b') {
			// ESC キー
			break;
		}
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("Capture");
}

void get_imageData(char* filename, IplImage* img)
{
	int x, y, i = 0;
	char out_FileName[100];
	sprintf(out_FileName, "Data_%s.txt", filename);
	std::ofstream ofs(out_FileName);

	uchar p[3];

	uchar* bank = new uchar[img->height*img->width];
	for (y = 0; y < img->height; y++) {
		for (x = 0; x < img->width; x++) {
			/* 画素値を直接操作する一例 */
			//p[0] = img->imageData[img->widthStep * y + x * 3];        // B
			//p[1] = img->imageData[img->widthStep * y + x * 3 + 1];    // G
			//p[2] = img->imageData[img->widthStep * y + x * 3 + 2];    // R
			i++;
			//bank[i] = 0.144*p[0] + 0.587*p[1] + 0.299*p[2];
			bank[i] = img->imageData[img->widthStep * y + x];
			ofs << std::dec << static_cast<int>(bank[i]) << std::endl;
		}
	}
}

void Mouse(int event, int x, int y, int flags, void *param)
{
	Data* data = (Data*)param;
	switch (event)
	{
		case CV_EVENT_LBUTTONDOWN:
		{
			std::cout << x << "," << y << "\n";
			data->x = x;
			data->y = y;
			break;
		}
		default:
		{
			break;
		}
	}
}

void threshold(IplImage* img, IplImage* t_img, char* filename)
{
	IplImage *src_img = 0, *dst_img;
	int x;
	char exfilename[100];/*拡張子付きファイル名*/

	//cvSmooth (src_img, src_img, CV_GAUSSIAN, 5);//平均化

	cvThreshold(img, t_img, 100, 255, CV_THRESH_BINARY);
	sprintf(exfilename, "100_%s", filename);
	cvSaveImage(exfilename, t_img);

	cvThreshold(img, t_img, 50, 255, CV_THRESH_BINARY);
	sprintf(exfilename, "50%s", filename);
	cvSaveImage(exfilename, t_img);

	cvThreshold(img, t_img, 75, 255, CV_THRESH_BINARY);
	sprintf(exfilename, "75%s", filename);
	cvSaveImage(exfilename, t_img);

	// (1)輝度平均
	x = cvThreshold(img, t_img, 127, 255, CV_THRESH_BINARY);
	sprintf(exfilename, "ave%d%s", x, filename);
	cvSaveImage(exfilename, t_img);

	// (2)大津の手法
	x = cvThreshold(img, t_img, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	sprintf(exfilename, "Otsu%d%s", x, filename);
	cvSaveImage(exfilename, t_img);
}

int search_TransAngle(IplImage* img ){
	int i, j;

	int max=0, min=0,result;
	double angle=0.0;
	double sum=0.0,ave=0.0,con=0.0,max_con=0.0;
	CvPoint origin,point; 
	Mat trans;
	Mat x, ans;
	std::ofstream fs1("kkuninn.txt");
	origin.x = img->width / 2;
	origin.y = img->height / 2;

	for (angle= -10; angle < 11; angle++){
		trans = TransMat(angle);
		for (i = -10; i < 10; i++){
			sum = 0;
			ave = 0;
			for (j = 0; j < img->width; j++){
				x = (Mat_<double>(2, 1) << j-origin.x, origin.y-i);
				ans = trans*x;
				fs1 << ans << std::endl;
				point.x=ans.at<int>(1, 1)+origin.x;
				point.y = ans.at<int>(2, 1);
				sum+=img->imageData[img->widthStep * point.y + point.x];
			}
			ave = sum / img->width;
			if (ave>max){
				max = ave;
			}
			else if (ave < min){
				min = ave;
			}
			fs1 << "aaaaaaaaaaaaaaa" << std::endl;
		}
		con = abs(max - min);
		if (max_con < con){
			result = angle;
		}
		fs1 << result << std::endl;
	}
	return result;
}

Mat TransMat(double angle){
	double a, b;
	a = std::cos(angle*CV_PI / 180);
	b = b = std::sin(angle*CV_PI / 180);
	Mat trans = (Mat_<double>(2, 2) << a, -b, b, a);
	return trans;
}



//std::cout << "outfile name(.txt) = ";
//std::cin >> name;
//get_imageData(name, gray_image);
