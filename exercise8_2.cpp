#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void OnMouse(int event, int x, int y, int flag, void* param) {
	Mat img = *(Mat *)(param);
	int cols = img.cols/3; //analytic pic's cols
	int X = x % cols;
	string s;
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN://鼠标左键按下
		s = '('+to_string(X) + ',' + to_string(y)+')';
		putText(img,s, Point(x, y), CV_FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(0, 255, 0), 2, 8);
		break;
	case CV_EVENT_LBUTTONUP://鼠标左键抬起		
		img.setTo(Scalar::all(0));
		break;
	default:
		break;
	}
}

int main() {

	Mat C ,result;
	VideoCapture cap("D:\\srcpkg\\opencv2.4\\opencv\\sources\\samples\\cpp\\tutorial_code\\HighGUI\\video-input-psnr-ssim\\video\\Megamind.avi");

	if (!cap.isOpened())
		return -1;
	namedWindow("Split three Window");
	if (cap.grab())
		cap.retrieve(C);
	int width = C.cols, height = C.rows, type = C.type(),fps =(int) cap.get(CV_CAP_PROP_FPS);
	Mat ThreeWindow(height, width * 3, type), temp1 = ThreeWindow(Rect(0, 0, width, height)), temp2 = ThreeWindow(Rect(width, 0, width, height)), temp3 = ThreeWindow(Rect(2 * width, 0, width, height));
	Mat img(height, width * 3, type,Scalar::all(0));
	Mat temp = img.clone();	
	int n = 0;
	bool flag;
	setMouseCallback("Split three Window", OnMouse, &img);
	while (1)
	{
		flag = cap.set(CV_CAP_PROP_POS_FRAMES, 0 + n);
		cap >> C;
		if (C.empty() || !flag)
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
		addWeighted(ThreeWindow, 1, img, 1, 0, result);
//		resize(result, result, Size(900, 300));
		imshow("Split three Window", result);
		n++;
		
		if (27 == waitKey(1000/fps))
			break;
	}

	waitKey(0);
	return 0;
}