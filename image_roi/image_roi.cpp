// ˵����ͼ������룬��ʾ����������
// VSC2015   OpenCV�汾��3.41

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;

int main(int argc, char** argv) {
	const char* filename1 = argc >= 2 ? argv[1] : "../../images/lena.png";
	const char* filename2 = argc >= 3 ? argv[2] : "../../images/opencv-logo-small.png";

	//ͼ������
	Mat image = imread(filename1);	//lena.png ��һ��ͼƬ
	Mat logo = imread(filename2);	//opencv-logo-small.pngΪ�ڶ���ͼƬ

	//���������ʾ
	char* winName1 = "1. ԭ��ͼ";
	namedWindow(winName1);			//��������
	imshow(winName1, image);		//��ʾ����
	char* winName2 = "2. logoͼ";
	namedWindow(winName2);
	imshow(winName2, logo);

	//����һ��Mat���ͣ����ڴ�ţ�ͼ���ROI
	Mat imageROI;
	//����һ
	imageROI = image(Rect(image.cols-logo.cols, image.rows-logo.rows, logo.cols, logo.rows));
	//������
	//imageROI=image(Range(350,350+logo.rows),Range(800,800+logo.cols));

	//��logo�ӵ�ԭͼ�ϣ��������
	//dst = src1*alpha + src2*beta + gamma;
	//			src1,   alpha, src2, beta, gamma, dst
	addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);

	//��ʾ���
	char* winName3 = "3. ԭ��+logoͼ";
	namedWindow(winName3);
	imshow(winName3, image);

	//���һ��jpgͼƬ����ĿĿ¼��
	imwrite("result.jpg", image);

	waitKey();
	return 0;
}