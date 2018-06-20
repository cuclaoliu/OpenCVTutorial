#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
using namespace cv;
using namespace std;

#define CAMERA

void FaceDetect(Mat& img, String path);
void OverlayFacemask(Mat& img, String path);
void OverlaySunGlasses(Mat& img, String path);

int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
		cout << i<<". "<<argv[i] << endl;
	if (2 != argc) {
		cout<<"Parameter error!"<<endl;
		system("pause");
		return -1;
	}

	//ѵ���õ��ļ�����
	String path = argv[1];
	Mat frame;
#ifndef CAMERA
	String imFile = path+"/g7.jpg";
	frame = imread(imFile);
	if (frame.empty()) {
		cout << "No photo: " << imFile << endl;
		system("pause");
		return -1;
	}
	FaceDetect(frame, path);
	waitKey();
#else
	VideoCapture cap(0);    //��Ĭ������ͷ
	if (!cap.isOpened())
	{
		return -1;
	}
	int status = 0;
	while(true)
	{
	    cap>>frame;
		flip(frame, frame, 1);
		int key = waitKey(10);
		switch (status)
		{
		case 0:
			if (key == -1)
				imshow("ԭʼͼ��", frame);
			else if (key == 27)
				return 0;
			else if (key == '1') {
				status = 1;
			}
			else if (key == '2')
				status = 2;
			else if (key == '3')
				status = 3;
			break;
		case 1:
			FaceDetect(frame, path);
			imshow("ʶ����", frame);
			if (key == 27) {
				destroyAllWindows();
				status = 0;
			}
			break;
		case 2:
			OverlayFacemask(frame, path);
			imshow("�����", frame);
			if (key == 27) {
				destroyAllWindows();
				status = 0;
			}
			break;
		case 3:
			OverlaySunGlasses(frame, path);
			imshow("̫����", frame);
			if (key == 27) {
				destroyAllWindows();
				status = 0;
			}
			break;
		default:
			break;
		}

	}
#endif
	return 0;
}