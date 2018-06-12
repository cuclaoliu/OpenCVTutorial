#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

//#define FILEPATH

// test function that creates an image
cv::Mat function() {
	// create image
	cv::Mat img(500, 500, CV_8U, 50);
	return img;
}

int main(int argc, char* argv[]) {

	// Matrix
	cv::Mat m1 = cv::Mat::eye(2, 3, CV_32F);
	cv::Mat m2 = cv::Mat::ones(3, 2, CV_32F);
	// scalar by matrix
	std::cout << m1 * 2 << std::endl;
	// matrix per element multiplication
	std::cout << (m1 + 1).mul(m1 + 3) << std::endl;
	// Matrix multiplication
	std::cout << m1*m2 << std::endl;
	// matrix transpotion
	std::cout << m1.t() << std::endl;
	// matrix inversion
	std::cout << (m2*m1).inv() << std::endl;
	// count the non-zero elements
	std::cout << "number of non-zero elements: " << cv::countNonZero(m1) << std::endl;

	// create a new image made of 240 rows and 320 columns
	cv::Mat image1(240, 320, CV_8U, 100);
	cv::imshow("240x320 value=100", image1); // show the image
	cv::waitKey(0); // wait for a key pressed

					// re-allocate a new image
	image1.create(200, 200, CV_8U);
	image1 = 200;

	cv::imshow("200x200 value=100", image1); // show the image
	cv::waitKey(0); // wait for a key pressed

					// create a red color image
					// channel order is BGR
	cv::Mat image2(240, 320, CV_8UC3, cv::Scalar(0, 0, 255));
	// or:
	// cv::Mat image2(cv::Size(320,240),CV_8UC3);
	// image2= cv::Scalar(0,0,255);

	cv::imshow("rgb(0, 0, 255)", image2); // show the image
	cv::waitKey(0); // wait for a key pressed

#ifdef FILEPATH
	cv::String imgFile = "../../lena.png";
#else
	cv::String imgFile = argv[1];
#endif
	// read an image
	cv::Mat image3 = cv::imread(imgFile);
	// all these images point to the same data block
	cv::Mat image4(image3);
	image1 = image3;

	// these images are new copies of the source image
	image3.copyTo(image2);
	cv::Mat image5 = image3.clone();

	// transform the image for testing
	cv::flip(image3, image3, 1);
	// check which images have been affected by the processing
	cv::imshow("fliped lena", image3);
	cv::imshow("assigned lena", image1);
	cv::imshow("copyto", image2);
	cv::imshow("copy construct", image4);
	cv::imshow("clone", image5);
	cv::waitKey(0); // wait for a key pressed

					// get a gray-level image from a function
	cv::Mat gray = function();
	cv::imshow("gray", gray); // show the image
	cv::waitKey(0); // wait for a key pressed

					// read the image in gray scale
	image1 = cv::imread(imgFile, CV_LOAD_IMAGE_GRAYSCALE);
	image1.convertTo(image2, CV_32F, 1 / 255.0, 0.0);

	cv::imshow("convert", image2); // show the image
	cv::waitKey(0); // wait for a key pressed

	return 0;
}