#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>

using namespace cv;

int CAM()
{
	const double WIDTH = 640;  // ��
	const double HEIGHT = 480; // ����
	const int CAMERANUM = 0; // �J�����ԍ�

	CvCapture *capture = NULL;
	IplImage *frame = 0;
	int ch;

	// �J�����ڑ��A���ƍ����̐ݒ�
	capture = cvCreateCameraCapture(CAMERANUM);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, WIDTH);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);

	namedWindow("Capture", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);

	while (1) {
		frame = cvQueryFrame(capture);

		cvShowImage("Capture", frame);
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
	return 0;
}