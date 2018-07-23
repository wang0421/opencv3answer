#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O
#include <iostream>
using namespace cv;

int value = 2;

void onChange(int pos, void *param) {
//	value = pos;
}

int main(int argc, char* argv[]) {
	namedWindow("Example2_11", WINDOW_AUTOSIZE);
	VideoCapture capture(0);
	Mat Store;

 	createTrackbar("TrackBar", "Example2_11", &value, 8, onChange, 0);
	Mat tempImg, tempImg2;
	while (1) {
		capture >> tempImg;
		for (int i = 2; i <= value; i++)
		{
			pyrDown(tempImg, tempImg2);
			tempImg = tempImg2;
		}
		imshow("Example2_11", tempImg2);

		if (waitKey(20) > 0) break;
	}
	imwrite(argv[1], tempImg2);
	capture.release();
}