#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main() {

	Mat C, result, canny;
	VideoCapture cap("D:\\srcpkg\\opencv2.4\\opencv\\sources\\samples\\cpp\\tutorial_code\\HighGUI\\video-input-psnr-ssim\\video\\Megamind.avi");

	if (!cap.isOpened())
		return -1;
	//	while (1)
	//	{
	//		cap >> C;
	//		if(C.empty())
	//			break;
	//		cvtColor(C, gray, CV_BGR2GRAY);
	//		Canny(gray, canny, 50, 150);
	//		imshow("src video", C);
	//		imshow("gray video", gray);
	//		imshow("canny video", canny);
	//
	//		if ('n' == waitKey(0))
	//			continue;
	//		if (27 == waitKey(0))
	//			break;
	//	}
	if (cap.grab())
		cap.retrieve(C);
	int width = C.cols, height = C.rows, type = C.type();
	Mat ThreeWindow(height, width * 3, type), temp1 = ThreeWindow(Rect(0, 0, width, height)), temp2 = ThreeWindow(Rect(width, 0, width, height)), temp3 = ThreeWindow(Rect(2 * width, 0, width, height));
	cout << temp1.cols << "  " << temp1.rows << " " << temp1.size() << "  " << temp1.type() << endl;
	int n = 0;
	bool flag = true;
	cout << static_cast<const void *>(ThreeWindow.data) << " " << static_cast<const void *>(temp1.data) << " " << static_cast<const void *>(temp2.data) << " " << static_cast<const void *>(temp3.data) << endl;
	while (1)
	{
		flag = cap.set(CV_CAP_PROP_POS_FRAMES, 0 + n);
		cap >> C;
		if (C.empty()||!flag )
			break;
		C.copyTo(temp1);
		putText(temp1, "first stages ", Point(5, 30), CV_FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(0, 255, 0), 2, 8);
		flag = cap.set(CV_CAP_PROP_POS_FRAMES, 33 + n);
		cap >> C;
		if (C.empty() || !flag)
			break;
		C.copyTo(temp2);
		putText(temp2, "second stages ", Point(5, 30), CV_FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(0, 255, 0), 2, 8);
		flag = cap.set(CV_CAP_PROP_POS_FRAMES, 66 + n);
		cap >> C;
		if (C.empty() || !flag)
			break;
		C.copyTo(temp3);
		putText(temp3, "third stages ", Point(5, 30), CV_FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(0, 255, 0), 2, 8);
 		resize(ThreeWindow, result, Size(900, 300));
		imshow("Split three Window", result);
		n++;
		if ('n' == waitKey(0))
			continue;
		if (27 == waitKey(0))
			break;
	}

	waitKey(0);
	return 0;
}