#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main() {

	Mat C = (Mat_<float>(3, 2) << 1, 1, 0, 1, -1, 1);
	cout << C << endl;

	Mat u, vt, w;
	SVD svd;
	svd.compute(C,w,u,vt, SVD::FULL_UV);

	cout << u << endl << w << endl << vt << endl;
	Mat trans(3,2,CV_32FC1);
	trans.at<float>(0, 0) =  w.at<float>(0,0);
	trans.at<float>(1, 1) = w.at<float>(1, 0);
	trans.at<float>(0, 1) = 0.0f;
	trans.at<float>(1, 0) = 0.0f;
	trans.at<float>(2, 0) = 0.0f;
	trans.at<float>(2, 1) = 0.0f;
	Mat result = (u*trans*vt );

	cout << result << endl;
	waitKey(0);
	return 0;
}