#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>

void Mouse(int event, int x, int y, int flags, void *param)
{
	//CvPoint* point=0;
	switch (event)
	{			
	case CV_EVENT_LBUTTONDOWN:
		{
			 std::cout << x << "," << y << "\n";
			 //point->x = x;
			 //point->y = y;
			 break;
		}
	default:
		{
			   break;
		}

	}
}

