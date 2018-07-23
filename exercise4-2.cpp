#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

void GetItegalImage(InputArray src, OutputArray dst)
{
	Mat destImg= dst.getMat() ,srcImg = src.getMat();
	if (destImg.cols != srcImg.cols || destImg.rows != srcImg.rows)
		return;
	Mat temp;
	copyMakeBorder(destImg, temp, 1, 0, 1, 0, CV_8U);

	for (int i =0;i<srcImg.rows; i++)
	{
		float rowsum = 0;
		for (int j = 0; j < srcImg.cols; j++)
		{	
			rowsum += srcImg.at<uchar>(i, j);			
			temp.at<float>(i+1, j+1) = rowsum + temp.at<float>(i, j+1);
			destImg.at<float>(i, j ) = temp.at<float>(i + 1, j + 1);
		}
	}
//	Rect r(1, 1, temp.cols - 1, temp.rows - 1);
//	destImg = temp(r);
	cout << destImg << endl;
}
float CalculateRactangleArea(InputArray src, Rect in)
{
	float result = 0;
	Mat srcImg = src.getMat(),temp;
	Point a, b, c, d;
	a.x = in.x;
	a.y = in.y;
	b.x = in.x+in.width+1;
	b.y = in.y;
	c.x = in.x;
	c.y = in.y+in.height+1;
	d.x = in.x + in.width +1;
	d.y = in.y + in.height+1;
	copyMakeBorder(src, temp, 1, 0, 1, 0, CV_8U);

	result = temp.at<float>(a) + temp.at<float>(d) - temp.at<float>(b) - temp.at<float>(c);
	return result;
}
int main()
{
	Mat srcImag(3,4,CV_8UC1), ItegalImage(3, 4, CV_32FC1);
	RNG rng;
	rng.fill(srcImag, cv::RNG::UNIFORM, 0, 255);
	ItegalImage.setTo(Scalar::all(0));

	GetItegalImage(srcImag, ItegalImage);

	cout << srcImag << endl;
	cout << ItegalImage << endl;
	Rect rec(1,1,1,1);
	float sumResult;
	sumResult = CalculateRactangleArea(ItegalImage, rec);

	cout << sumResult << endl;
	return 0;
}