#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace cv;
using namespace std;

Mat img(400,400,CV_8UC3);
Mat temp = img.clone();
vector<Point> pt;
vector<vector<Point>> point;
bool flag = false;

void onMouse(int event, int x, int y, int flag, void* param) {
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN://鼠标左键按下
		
		pt.clear();
		pt.push_back(Point(x, y));
		flag = true;
		break;
	case CV_EVENT_MOUSEMOVE://鼠标移动
		if (flag) {
			pt.push_back(Point(x, y));
			Point *buffer = pt.data();
			const Point *pts2[] = { buffer };
			int npt[] = { pt.size() };
			polylines(img, pts2, npt, 1, false, Scalar(0, 100, 200), 2, 8);
		}
		break;
	case CV_EVENT_LBUTTONUP://鼠标左键抬起		
		point.push_back(pt);
		flag = false;
		break;
	default:
		break;
	}
}
void deleteline()
{
	temp.copyTo(img);
	cout << point.size() << endl;
	if(point.size()>0)
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
void main() {
	namedWindow("mouse", CV_WINDOW_AUTOSIZE);
	setMouseCallback("mouse", onMouse, 0);

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