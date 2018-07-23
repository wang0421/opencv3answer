#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
void drawHistogram(Mat mat);
Point pt[2];
Mat recT;
bool f = false;
void OnMouse(int event, int x, int y, int flag, void* param) {
	Mat img = *(Mat *)(param);
	Mat m(img.rows, img.cols, img.type());
	m.setTo(Scalar::all(0));

	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN://鼠标左键按下
		pt[0] = Point(x, y);
		pt[1] = Point(x, y);
		f = true;
		break;
	case CV_EVENT_MOUSEMOVE://鼠标移动
		if (f)
		{
			pt[1] = Point(x, y);
			recT = img(Rect(pt[0], pt[1]));
			rectangle(m, pt[0], pt[1], Scalar(100, 300, 0));
			addWeighted(img, 1, m, 1, 0, m);
			imshow("src pic", m);
		}
		m.setTo(Scalar::all(0));
		break;
	case CV_EVENT_LBUTTONUP://鼠标左键抬起	
		f = false;
		imshow("RIO img", recT);
		drawHistogram(recT);
		break;
	default:
		break;
	}
}

void drawHistogram(Mat mat)
{
	Mat His(500, 500, CV_8UC3, Scalar(100, 100,100));
	unsigned b[8] = {}, g[8] = {}, r[8] = {};
	MatIterator_<Vec3b>  it = mat.begin<Vec3b>(), end = mat.end<Vec3b>();
	for (; it != end; ++it)
	{
		b[(*it)[0] / 32]++;
		g[(*it)[1] / 32]++;
		r[(*it)[2] / 32]++;
	}
	Mat B(1, 8, CV_32SC1,b), G(1, 8, CV_32SC1, g), R(1, 8, CV_32SC1, r);
	vector<Mat> temp = { B,G,R };
	Mat t;
	merge(temp, t);
	cout << t << endl;
	normalize(t, t, 0, 500, NORM_MINMAX, -1, Mat());
	cout << B << endl;
	cout << G << endl;
	cout << R << endl;
	cout << t << endl;
	cout << t.type() << " " << t.depth() << endl;

	Point Bp[2], Gp[2], Rp[2];
	for (int i = 0; i < 8; i++)
	{
		Bp[0] = Point(10+i*60, 500);
		Bp[1] = Point(30 + i * 60, 500-t.at<Vec3i>(0, i)[0]);
		Gp[0] = Point(30 + i * 60, 500);
		Gp[1] = Point(50 + i * 60, 500 - t.at<Vec3i>(0, i)[1]);
		Rp[0] = Point(50 + i * 60, 500);
		Rp[1] = Point(70 + i * 60, 500 - t.at<Vec3i>(0, i)[2]);
 		rectangle(His, Bp[0], Bp[1], Scalar(255, 0, 0),-1);
 		rectangle(His, Gp[0], Gp[1], Scalar(0, 255, 0),-1);
		rectangle(His, Rp[0], Rp[1], Scalar(0, 0, 255),-1);
		cout << i << "  ";
	}
	imshow("His img", His);
	return;
}

int main() {

	Mat C, result;
	C = imread("C:\\Users\\wangcl\\source\\repos\\opencvday2\\p001.png");
	namedWindow("src pic");
	setMouseCallback("src pic", OnMouse, &C);
	imshow("src pic", C);
	waitKey(0);
	return 0;
}