#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace cv;
using namespace std;

Mat img(400, 400, CV_8UC3,Scalar::all(0));
Mat temp = img.clone();
vector<Point> pt;
vector<vector<Point>> point;
bool flagL = false;
bool flagR = false;
int value = 0;
enum logic
{
	OR = 0,
	AND = 1,
	XOR = 2
};
void onMouse(int event, int x, int y, int flag, void* param) {
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN://鼠标左键按下

		pt.clear();
		if (value == OR)
		{
			if(img.at<Vec3b>(Point(x, y))[0] == 0&&
			img.at<Vec3b>(Point(x, y))[1] == 0&&
			img.at<Vec3b>(Point(x, y))[2] == 0)
				flagL = true;
		}
		if (value == AND)
		{
			if (img.at<Vec3b>(Point(x, y))[0] > 0 ||
				img.at<Vec3b>(Point(x, y))[1] > 0 ||
				img.at<Vec3b>(Point(x, y))[2] > 0)
				flagL = true;
		}
		if (value == XOR)
		{
			flagL = true;
		}
		break;
	case CV_EVENT_MOUSEMOVE://鼠标移动
		if (flagL) {
			pt.push_back(Point(x, y));
			Point *buffer = pt.data();
			const Point *pts2[] = { buffer };
			int npt[] = { pt.size() };
			polylines(img, pts2, npt, 1, false, Scalar(0, 100, 200), 2, 8);
		}
		break;
	case CV_EVENT_LBUTTONUP://鼠标左键抬起	
		if(pt.size() > 0)
		point.push_back(pt);
		flagL = false;
		break;
	case CV_EVENT_RBUTTONDOWN:
		flagR = true;
		break;
	case CV_EVENT_RBUTTONUP:
		if (flagR)
		{
			img.at<Vec3b>(Point(x, y))[0] = 0;
			img.at<Vec3b>(Point(x, y))[1] = 0;
			img.at<Vec3b>(Point(x, y))[2] = 0;
		}
		flagR = false;
		break;
	default:
		break;
	}
}
void deleteline()
{
	temp.copyTo(img);
	cout << point.size() << endl;
	if (point.size()>0)
		point.pop_back();

	for (int i = 0; i < point.size(); i++)
	{
		//cout << "重新绘制" << endl;
		Point *buffer = point[i].data();
		const Point *pts2[] = { buffer };
		int npt[] = { point[i].size() };
		polylines(img, pts2, npt, 1, false, Scalar(0, 100, 200), 2, 8);
	}

}
void OnChange(int, void *)
{

}
void main() {
	namedWindow("mouse", CV_WINDOW_AUTOSIZE);
	setMouseCallback("mouse", onMouse, 0);
	createTrackbar("logical drawing","mouse",&value,2,OnChange);
	while (1) {
		imshow("mouse", img);
		char key = waitKey(10);
		if (27 == key)//esc跳出循环
		{
			break;
		}
		else if ('\b' == key)
		{
			//cout << "删除线条" << endl;			
			deleteline();
		}
	}
}