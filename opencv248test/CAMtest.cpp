#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>

using namespace cv;

int	threshold(IplImage *img, IplImage *t_img);

int CAM()
{
	const double WIDTH = 640;  // ��
	const double HEIGHT = 480; // ����
	const int CAMERANUM = 0; // �J�����ԍ�

	CvCapture *capture = NULL;
	IplImage *frame = 0,*t_frame=0;
	int ch;

	// �J�����ڑ��A���ƍ����̐ݒ�
	capture = cvCreateCameraCapture(CAMERANUM);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, WIDTH);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);

	namedWindow("Capture", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
	namedWindow("Gray_Capture", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);

	while (1) {
		frame = cvQueryFrame(capture);
		threshold(frame,t_frame);
		cvShowImage("Capture", frame);
		cvShowImage("Gray_Capture", t_frame);
		ch = cvWaitKey(1); // 0 �̓f�B���C���� (�~���b�P��)
		if (ch == 's'){
			cvSaveImage("outputimg.jpg", frame);
		}
		if (ch == '\x1b') {
			// ESC �L�[
			break;
		}
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("Capture");
	cvDestroyWindow("Gray_Capture");
	return 0;
}