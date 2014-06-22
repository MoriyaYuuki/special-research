#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>

using namespace cv;

int CAM()
{
	const double WIDTH = 640;  // 幅
	const double HEIGHT = 480; // 高さ
	const int CAMERANUM = 0; // カメラ番号

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
			cvSaveImage("outputimg.jpg", frame);
		}
		if (ch == '\x1b') {
			// ESC キー
			break;
		}
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("Capture");
	return 0;
}