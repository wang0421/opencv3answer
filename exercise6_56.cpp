#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace cv;
using namespace std;

int main() {
	Mat mat = imread("C:/Users/wangcl/source/repos/opencvday2/p001.png");
	Point pt[] = { Point(50,50),Point(50,90) ,Point(90,90) };
	const Point *ppt[] = { pt };
	int nnpt[] = { 3 };
	//fillPoly(mat, ppt, nnpt, 1, Scalar(20, 50, 90));
	//line(mat, Point(50, 50), Point(90, 90), Scalar(20, 50, 90));
	polylines(mat, ppt, nnpt,1, false, Scalar(20, 50, 90));
	imshow("exam6-5", mat);
	LineIterator lineItor(mat,Point(50,50),Point(90,90));
	Vec3b pixChg(200, 00, 00);
	cout << lineItor.count << endl;
	for (int i = 0; i < lineItor.count; i++, ++lineItor)
	{
		(*lineItor)[1] = 200;
	}
	imshow("exam6-6", mat);
	waitKey(0);
	return 0;
}