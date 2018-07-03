#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
#define IMFILE "../../lena.png"

void sharpen(const Mat&, Mat&);

int main(int argc, char** argv)
{
	String file;
#ifdef IMFILE
	file = IMFILE;
#else
	if (argc != 2)
	{
		cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}
	file = argv[1];
#endif
	Mat image;
	image = imread(file, IMREAD_COLOR); // Read the file
	if (image.empty()) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		waitKey(0); // Wait for a keystroke in the window
		return -1;
	}
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image); // Show our image inside it.

	double t = (double)getTickCount();
	
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}

void sharpen(const Mat& img, Mat& result)
{

}