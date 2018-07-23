#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int value,Stop = 1 ;

void onChange(int, void* param) {
	VideoCapture cap = *(VideoCapture*)param;
	cap.set(CV_CAP_PROP_POS_FRAMES, value);//设置视频帧位置
}

void main() {
	Mat frame;
	char strFps[20];
	VideoCapture cap("D:/srcpkg/opencv2.4/opencv/sources/samples/cpp/tutorial_code/HighGUI/video-input-psnr-ssim/video/Megamind.avi");
	namedWindow("video", CV_WINDOW_AUTOSIZE);
	int frameCount = cap.get(CV_CAP_PROP_FRAME_COUNT);//获取视频总帧数
	createTrackbar("Frame", "video", &value, frameCount, onChange, &cap);
	createTrackbar("stop", "video", &Stop, 1, 0, 0);

	if (cap.isOpened()) {//如果视频成功打开
		while (1) {
			while(Stop == 0)
			{
				imshow("video", frame);
				setTrackbarPos("stop", "video", 0);
				waitKey(10);
			}
			{
				double Fps = cap.get(CV_CAP_PROP_FPS);//获得视频帧率
				sprintf(strFps, "Fps%0.1f/s", Fps);//格式化字符串
				int framePos = cap.get(CV_CAP_PROP_POS_FRAMES);//获取视频帧位置
				setTrackbarPos("Frame", "video", framePos);//设置滑动条位置
				cap >> frame;
				if (!frame.empty()) {//如果该帧不为空
					putText(frame, strFps, Point(5, 30), CV_FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(0, 255, 0), 2, 8);
					imshow("video", frame);
					if (27 == waitKey(1000 / Fps))//esc退出，1000/Fps毫秒刷新
						break;
				}
				else break;
			}
		}
	}
}