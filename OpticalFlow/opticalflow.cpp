#include <iostream>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

static void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step,
	const Scalar& colorStill, const Scalar& colorMobile) {
	for (int y=0; y < cflowmap.rows; y += step)
		for (int x = 0; x < cflowmap.cols; x += step) {
			const Point2f& fxy = flow.at<Point2f>(y, x);
			//�ƶ�������
			line(cflowmap, Point(x, y), Point(cvRound(x + fxy.x), cvRound(y + fxy.y)), colorStill);
			//��ɫ�̶���
			circle(cflowmap, Point(x, y), 1, colorMobile, -1);
		}
}

int main() {
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "����ͷ��ʧ�ܣ�" << endl;
		return -1;
	}
	Mat prevgray, gray, flow, cflow, frame;
	namedWindow("flow", 1);
	while (true) {
		cap >> frame;
		cvtColor(frame, gray, COLOR_RGB2GRAY);
		if (prevgray.data) {
			// ʹ�� Gunner Farneback �㷨������� (optical flow) �ܶ�
			calcOpticalFlowFarneback(prevgray, gray, flow, 
				0.5, 3, 15, 3, 5, 1.2, 0);
			cvtColor(prevgray, cflow, COLOR_GRAY2BGR);
			//�����̵�
			drawOptFlowMap(flow, cflow, 16, Scalar(0, 0, 255), Scalar(0, 255, 0));
			imshow("flow", cflow);
		}
		if (waitKey(30) >= 0)
			break;
		//ͼ�񻥻�
		swap(prevgray, gray);
	}
	return 0;
}