#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace cv;
using namespace std;

int main() {
	RNG rng(123);
	//生成和打印三个浮点数，每个浮点数从0到1的均匀分布。
	float a, b, c;
	a = rng.uniform(0.0f, 0.1f);
	b = rng.uniform(0.0f, 0.1f);
	c = rng.uniform(0.0f, 0.1f);
//	cout << a << " " << b << " " << c << endl;
	//生成并打印三个双精度数，每一个都来自于以0为中心的高斯分布，标准偏差为1。0。
	double d1,d2,d3;
	d1= rng.gaussian(1.0f);
	d2 = rng.gaussian(1.0f);
	d3 = rng.gaussian(1.0f);
//	cout << d1 << " " << d2 << " " << d3 << endl;
	//生成并打印三个无符号字节，每个字节从0到255的均匀分布。
	unsigned int u1, u2, u3;
	u1 = rng.uniform(0, 255);
	u2 = rng.uniform(0, 255);
	u3 = rng.uniform(0, 255);
//	cout << u1 << " " << u2 << " " << u3 << endl;

	Mat pf(1,20, CV_32FC1),pf2(1,20, CV_32FC1),pi(1,20,CV_8UC1),clr(1,20,CV_8UC3);
	rng.fill(pf, RNG::UNIFORM, 0.0f, 1.0f);
	rng.fill(pf2, RNG::NORMAL, 0.0L, 1.0L);
	rng.fill(pi, RNG::UNIFORM, 0, 255);
	rng.fill(clr, RNG::UNIFORM, 0, 255);
//	cout << pf << endl << pf2 << endl << pi << endl << clr << endl;

	Mat mat(100, 1, CV_16UC3),mat2(100,3,CV_16UC1);
	Mat tm1(1, 3, CV_16UC1), tm2(3, 1, CV_16UC1);
//	fill(InputOutputArray mat,int distType,InputArray a, InputArray b) 
//	distType = RNG::UNIFORM 均匀概率or  RNG::NORMAL 高斯概率
//	a和b对应mat的通道数，不必和 mat 方向相同；
	rng.fill(mat, RNG::NORMAL, Vec3d(64, 192, 128), Vec3d(10, 10, 2));//第一通道 均值64 ，10标准差范围的高斯随机
//	rng.fill(mat2.row(0), RNG::NORMAL, 64, 10);
//	rng.fill(mat2.row(1), RNG::NORMAL, 192, 10);
//	rng.fill(mat2.row(2), RNG::NORMAL, 128, 2);
//	cout << mat << endl;
//	cout << " channels " << mat.channels() << "   " << mat2.channels() << endl;

//	cout << mat2.row(0) << endl << mat2.row(1) << endl << mat2.row(2) << endl;
	
	mat2.data =  mat.data;
	cout << mat2<< endl;

 	PCA pca(mat2, Mat(), CV_PCA_DATA_AS_COL,2);
	Mat proj= pca.project(mat2.col(0));
	Mat reconstruction = pca.backProject(proj);
	cout << proj << endl << reconstruction << endl;
	Mat proj2 = pca.project(mat2.col(1));
	Mat reconstruction2 = pca.backProject(proj);
	Mat proj3 = pca.project(mat2.col(2));
	Mat reconstruction3 = pca.backProject(proj);
	Scalar a111= mean(reconstruction),a222 = mean(reconstruction2), a333= mean(reconstruction3);
	cout << reconstruction2 << endl << reconstruction3 << endl;
	cout << proj2 << endl << proj3 << endl;
	cout << a111 << " "<< a222<< " " << a333 <<endl;
	

	waitKey(0);
	return 0;
}