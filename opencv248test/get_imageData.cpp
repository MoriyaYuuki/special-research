//#include <opencv2/opencv.hpp>
//#include <opencv2/opencv_lib.hpp>
//#include <iostream>
//#include <fstream>
//#include <string>
//
//
////void get_imageData(char* filename,IplImage* img)
////{
////	int x, y,i=0;
////	char out_FileName[32];
////	sprintf(out_FileName, "Data_%s.txt",filename);
////	std::ofstream ofs(out_FileName);
////
////	uchar p[3];
////	
////	//img = cvLoadImage("outputimg.jpg", CV_LOAD_IMAGE_GRAYSCALE);
////	uchar* bank = new uchar[img->height*img->width];
////	for (y = 0; y < img->height; y++) {
////		for (x = 0; x < img->width; x++) {
////			/* ‰æ‘f’l‚ð’¼Ú‘€ì‚·‚éˆê—á */
////			//p[0] = img->imageData[img->widthStep * y + x * 3];        // B
////			//p[1] = img->imageData[img->widthStep * y + x * 3 + 1];    // G
////			//p[2] = img->imageData[img->widthStep * y + x * 3 + 2];    // R
////			i++;
////			//bank[i] = 0.144*p[0] + 0.587*p[1] + 0.299*p[2];
////			bank[i] = img->imageData[img->widthStep * y + x];
////			ofs << std::dec << static_cast<int>(bank[i]) << std::endl;
////		}
////	}
////}
//
//
