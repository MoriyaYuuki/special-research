#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>
#include <Tchar.h>

using namespace cv;

int CAM(int argc, char **argv);
int histogram(int argc, char **argv);

int main(int argc, char **argv)
{
	int check;
	CAM(argc,argv);
	check=histogram(argc,argv);
	printf("%d\n", check);
	getchar();
	return 0;
}