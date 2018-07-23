#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat mat(500, 500, CV_8UC3);
	mat = Scalar::all(0);

	imshow("ascii writer", mat);
	int i = 0;
	Point p[25];
	p[1]= { 0,30 };
	string ch[25];
	Scalar color(255, 0, 0);
	RNG rng;
	while (1)
	{
		char temp = 0;
		temp = waitKey(0);

		if(temp == '\b')
		{ 
			i--;
			ch[i/20].pop_back();
			
		}else if(isalpha(temp)){
			ch[i/20].push_back(temp);
			p[i/20].y = i / 20 * 50 +30;
			i++;
		}
		else {
			color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		}
		for (int t = 0; t <= i / 20; t++) {
			putText(mat, ch[t], p[t], FONT_HERSHEY_SIMPLEX, 1.0f, color);
		}
		
		imshow("ascii writer", mat);
		mat = Scalar::all(0);
		cout << i-1 << " "<<ch[i/20]<< " " << p<< " "<<endl;
		if (i == 200) break;
	}
	waitKey(0);
	return 0;
}