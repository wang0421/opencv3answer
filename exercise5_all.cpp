#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

void fillpoint(Point rook_points[ ][20],int w)
{
	rook_points[0][0] = Point(w / 5.0, w / 20.0);
	rook_points[0][1] = Point(w / 5.0 + 4, w / 20.0);
	rook_points[0][2] = Point(w / 5.0 + 6, w / 20.0);
	rook_points[0][3] = Point(w / 5.0 + 8, w / 20.0);
	rook_points[0][4] = Point(w / 5.0 + 10, w / 20.0);
	rook_points[0][5] = Point(w / 5.0 + 12, w / 20.0);
	rook_points[0][6] = Point(w / 5.0 + 14, w / 20.0);
	rook_points[0][7] = Point(w / 5.0 + 16, w / 20.0);
	rook_points[0][8] = Point(w / 5.0 + 18.0, w / 20.0);
	rook_points[0][9] = Point(w / 5.0 + 20, w / 20.0);
	rook_points[0][19] = Point(w / 5.0, w / 5.0);
	rook_points[0][18] = Point(w / 5.0 + 2, w / 5.0);
	rook_points[0][17] = Point(w / 5.0 + 4, w / 5.0);
	rook_points[0][16] = Point(w / 5.0 + 6, w / 5.0);
	rook_points[0][15] = Point(w / 5.0 + 8, w / 5.0);
	rook_points[0][14] = Point(w / 5.0 + 10, w / 5.0);
	rook_points[0][13] = Point(w / 5.0 + 12, w / 5.0);
	rook_points[0][12] = Point(w / 5.0 + 14, w / 5.0);
	rook_points[0][11] = Point(w / 5.0 + 16, w / 5.0);
	rook_points[0][10] = Point(w / 5.0 + 20, w / 5.0);

}
int main()
{
	Mat img1(100, 100, CV_8UC3, Scalar::all(0));
	Point center(10, 10);
	circle(img1, center, 3, Scalar(100, 200, 0));
	Rect rec(20, 5, 40, 20);
	rectangle(img1, rec, Scalar(100, 200, 0));


	imshow("exam5.1-5.2 windows", img1);
	img1.setTo(0);
	Point rook_points[1][20];
	int w = img1.rows;

	fillpoint(rook_points, w);
	const Point* ppt[1] = { rook_points[0] };
	int npt[] = { 20 };
	fillPoly(img1,ppt,npt,1, Scalar(255, 255, 255),8);
	imshow("exam5.3 windows", img1);

	Mat mat2(210, 210, CV_8UC1, Scalar::all(0));
	Mat Roi;
	Point a, b;
	int i = 1;
	while (1)
	{
		a.x = 10 * i;
		a.y = 10 * i;
		b.x = 210 - 10 * i;
		b.y = 210 - 10 * i;
		Roi = mat2(Rect(a,b));
		Roi.setTo(20 * i);
		i++;
		if (i == 10)break;
	}
	imshow("exam5.4 windows", mat2);

	string imgPath = "C:/Users/wangcl/source/repos/opencvday2/p001.png";
	Mat mat3 = imread(imgPath);
	Mat Roi1 = mat3(Rect(5, 10, 20, 30)), Roi2 = mat3(Rect(50, 60, 20, 30));

	bitwise_not(Roi1, Roi1);
	bitwise_not(Roi2, Roi2);
	imshow("exam5.5 windows", mat3);

	Mat spl[3];
	split(mat3, spl);// b ,g, r
	imshow("exam5.6 windows 1", spl[1]);
	Mat greenClone1 = spl[1].clone(), greenClone2 = spl[1].clone();
	int minimum =0, maximum =0;
	 min(greenClone1, minimum);
	 max(greenClone1, maximum);
	threshold(greenClone1, greenClone1, (unsigned char)((maximum - minimum) / 2.0),255, THRESH_BINARY);
	greenClone2.setTo(Scalar::all(0));
	compare(spl[1], greenClone1, greenClone2, CMP_EQ);
	subtract(spl[1], greenClone1, spl[1], greenClone2);
	imshow("exam5.6 windows 2", spl[1]);
	waitKey(0);
	return 0;
}