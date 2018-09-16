// 说明：图像的载入，显示，混合与输出
// VSC2015   OpenCV版本：3.41
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;

int main(int argc, char** argv) {
	const char* filename1 = argc >= 2 ? argv[1] : "../../images/lena.png";
	const char* filename2 = argc >= 3 ? argv[2] : "../../images/opencv-logo-small.png";

	//图像载入
	Mat image = imread(filename1);	//lena.png 第一张图片
	Mat logo = imread(filename2);	//opencv-logo-small.png为第二张图片

	//载入后先显示
	char* winName1 = "1. 原画图";
	namedWindow(winName1);			//命名窗口
	imshow(winName1, image);		//显示窗口
	char* winName2 = "2. logo图";
	namedWindow(winName2);
	imshow(winName2, logo);

	//定义一个Mat类型，用于存放，图像的ROI
	Mat imageROI;
	//方法一
	imageROI = image(Rect(image.cols-logo.cols, image.rows-logo.rows, logo.cols, logo.rows));
	//方法二
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
	//显示结果
	char* winName3 = "3. 原画+logo图";
	namedWindow(winName3);
	imshow(winName3, image);

	//输出一张jpg图片到项目目录下
	imwrite("result.jpg", image);

	waitKey();
	return 0;
}