// ˵����ͼ������룬��ʾ����������
// VSC2015   OpenCV�汾��3.41
#include <opencv2/imgproc/imgproc.hpp>
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

	Mat grayLogo, grayLogoThresh, grayLogoThreshInv;
	Mat maskedLogo, maskedFrame;
	// Extract region of interest (ROI) covering your face

	// Resize the face mask image based on the dimensions of the above ROI
	//resize(faceMask, faceMaskSmall, Size(w, h));

	// Convert the above image to grayscale
	cvtColor(logo, grayLogo, CV_BGR2GRAY);

	// Threshold the above image to isolate the pixels associated only with the face mask
	threshold(grayLogo, grayLogoThresh, 0, 30, CV_THRESH_BINARY_INV);

	// Create mask by inverting the above image (because we don't want the background to affect the overlay)
	bitwise_not(grayLogoThresh, grayLogoThreshInv);

	// Use bitwise "AND" operator to extract precise boundary of face mask
	bitwise_and(logo, logo, maskedLogo, grayLogoThreshInv);

	// Use bitwise "AND" operator to overlay face mask
	bitwise_and(imageROI, imageROI, maskedFrame, grayLogoThresh);

	imshow("MaskedLogo", maskedLogo);
	imshow("MaskedFrame", maskedFrame);

	// Add the above masked images and place it in the original frame ROI to create the final image
	add(maskedLogo, maskedFrame, image(Rect(image.cols - logo.cols, image.rows - logo.rows, logo.cols, logo.rows)));
	//��ʾ���
	char* winName3 = "3. ԭ��+logoͼ";
	namedWindow(winName3);
	imshow(winName3, image);

	//���һ��jpgͼƬ����ĿĿ¼��
	imwrite("result.jpg", image);

	waitKey();
	return 0;
}