#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{

	string imgPath = "C:/Users/wangcl/source/repos/opencvday2/p001.png";
	Mat img = imread(imgPath);
	line(img, Point(10, 10), Point(100, 250), Scalar(0, 255, 255), 20, 8);//在img图中画一条黄线，线宽为20，线型为8联通（一般都设置为8）
	circle(img, Point(200, 100), 50, Scalar(0, 255, 255), 15, 8);   //以（200,100）为圆心，半径为50，线宽为15画空心圆
	circle(img, Point(200, 250), 50, Scalar(0, 255, 255), -1, 8);   //设置为-1时，画实心圆
	rectangle(img, Point(10, 100), Point(200, 200), Scalar(0, 0, 255), 1, 8);   //传入坐上、右下角坐标，画空心矩形
	rectangle(img, Rect(200, 300, 100, 50), Scalar(0, 255, 0), -1, 8); //传矩形数据（左上角坐标（200,300）和宽100，高50），画实心绿色矩形
	ellipse(img, Point(200, 200), Size(180, 80), 15, 0, 360, Scalar(0, 255, 255), 10, 8);   //画椭圆，（200,200）为中点，15旋转角度，0~360度，长轴180，短轴80
	ellipse(img, RotatedRect(Point(350, 350), Size(150, 100), 40), Scalar(0, 255, 0), -1, 8);   //画椭圆，40旋转角度
	
	Point ppt[] = { Point(120,50),Point(180,50),Point(210,100),Point(180,150),Point(120,150),Point(90,100) };
	Point ppt2[] = { Point(80,400),Point(80,550),Point(250,500),Point(300,550) };//定义点集
	const Point* pts[] = { ppt };
	const Point* pts2[] = { ppt2 };
	int npt[] = { 6 };
	int npt2[] = { 4 };
	fillPoly(img, pts, npt, 1, Scalar(255, 255, 0), 8);   //画填充多边形
	polylines(img, pts2, npt2, 1, false, Scalar(0, 100, 200), 2, 8);   //画多边形，false为不闭合，true为闭合
	
	putText(img, "China", Point(400, 400), CV_FONT_BLACK, 2, Scalar(100, 100, 100), 5, 8);//写入文字
	imshow("exam6_1", img);

	//R*0.299 + G * 0.587 + B * 0.114
	int i = 0;
	Mat gray;
	Size size = img.size();
	gray.create(size, img.type());
	MatIterator_<Vec3b> it = img.begin<Vec3b>(), end =img.end<Vec3b>(),grayIt = gray.begin<Vec3b>();
	for (; it!= end; ++it,++grayIt) {
		(*grayIt)[0] = (*it)[0] * 0.299 + (*it)[1] * 0.587 + (*it)[2] * 0.114;
		(*grayIt)[1] = (*it)[0] * 0.299 + (*it)[1] * 0.587 + (*it)[2] * 0.114;
		(*grayIt)[2] =(*it)[0] * 0.299 + (*it)[1] * 0.587 + (*it)[2] * 0.114;	
	}
	putText(gray, "exam6_2", Point(400, 400), CV_FONT_BLACK, 1, Scalar(100, 150, 100), 1, 8);//写入文字
	imshow("exam6_2", gray);

	VideoCapture cap("D:/srcpkg/opencv2.4/opencv/sources/samples/cpp/tutorial_code/HighGUI/video-input-psnr-ssim/video/Megamind.avi");
	string strFps;
	Mat frame;
	while (1)
	{
		double Fps = cap.get(CV_CAP_PROP_FPS);//获得视频帧率
		strFps = "Fps :" + to_string(Fps);
		cap >> frame;
		if (!frame.empty()) {
			putText(frame, strFps, Point(5, 30), CV_FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(0, 255, 0), 2, 8);
			imshow("exam6_3", frame);
			if (27 == waitKey(1000 / Fps))//esc退出，1000/Fps毫秒刷新
				break;
		}
		else
			break;

	}

	waitKey(0);
	return 0;
}