#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	Point2f p2f = { -12.1f,22.6f };
	Point OutPoint = (Point)p2f;

	
	cout << p2f << "  " << OutPoint << endl;
	OutPoint.x = ceil(p2f.x);
	OutPoint.y = ceil(p2f.y);

	cout<<"ceil" << p2f << "  " << OutPoint << endl;
	OutPoint.x = floor(p2f.x);
	OutPoint.y = floor(p2f.y);

	cout << "floor" << p2f << "  " << OutPoint << endl;

	Matx33f m33f = { 2.2f,2.6f,-2.2f,-2.6f,3.3f,4.4f,4.5f,2.2f,2.6f };
	Vec3f vec3f = { -1.1f,1.2f,1.6f };

	// m33f.mul(vec3f); erro,  vec3f cant conver to matx33f
	//vec3f.mul(m33f); erro,  matx33f  cant conver to vec3f
	Vec3f result1 = m33f*vec3f;
	//vec3f*m33f;
	Vec3f result2 =  vec3f*vec3f;   // Undefined behavior
	Vec3f result3 = vec3f.mul(vec3f);
	cout << result1 <<"result 2 :" << result2<<"result 3 :" << result3 << endl;

	return 0;
}