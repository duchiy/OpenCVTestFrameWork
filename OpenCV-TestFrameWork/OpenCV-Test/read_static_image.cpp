#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#define MAX_BINARY_VALUE (255)
#define MID_BINARY_VALUE (127)

#define CANNY_KERNEL_SIZE (3)
#define CANNY_MAX_LOW_THRESHOLD (100)
#define CANNY_RATIO (3)

#define SOBEL_X_DERIVATIVE (1)
#define SOBEL_Y_DERIVATIVE (1)
#define SOBEL_MAX_KERNEL_SIZE (15)
#define SOBEL_DELTA (0)
#define SOBEL_SCALE (1)
#define SOBEL_DEPTH (CV_8U)
#define MAX_MORPHOLOGY_KERNEL_SIZE (21)

using namespace cv;
using namespace std;
void thresholdingOperation (int, void*);
void cannyOperation (int, void*);
void sobelOperation (int, void*);
void dilationOperation (int, void*);


Mat gray_image;
Mat thresold_image;
Mat canny_image;
Mat sobel_image;
Mat dilation_image;

int canny_low_threshold=40;
int threshold_value = MID_BINARY_VALUE;
int sobel_kernel_size=0;
int dilation_kernel =0;
    
int main( int argc, char** argv )
{
    if( argc != 2)
    {
    cout <<" Usage: read_static_image   seahawks.jpg" << endl;
      return -1;
    }

    Mat image;
    // Read the image file name
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   
	Mat gray_image1;
    cvtColor( image, gray_image1, CV_BGR2GRAY );
    vector<int> compression_params; //vector that stores the compression parameters of the image
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY); //specify the compression technique
    compression_params.push_back(98); //specify the compression quality
	
	imwrite("testImage.jpg",image,compression_params);
  // Check for invalid input
    if( image.data == NULL )                              
    {
        cout <<  "Couldn’t open the image" << endl ;
        return -1;
    }
    // Create a window for display.
    namedWindow( "Read Static Image", WINDOW_AUTOSIZE );
    //Display the image
    imshow( "Read Static Image", image );                   
    // Wait for a keystroke in the window
    waitKey(0);  
	Mat image_dst;
	GaussianBlur( image, image_dst, Size( 7,7), 0, 0, BORDER_DEFAULT );
	imshow( "Read Static Image", image_dst );   
// show gray image
	waitKey(0);                                          
	int thresh=10;
	cvtColor( image_dst, gray_image, CV_BGR2GRAY);
    imshow( "Read Static Image", gray_image );   
	waitKey(0);                                          

	// Canny Edge Detection
	namedWindow("Canny Operation", CV_WINDOW_AUTOSIZE );
    createTrackbar("Low Threshold:", "Canny Operation", &canny_low_threshold, CANNY_MAX_LOW_THRESHOLD, cannyOperation);
    cannyOperation (0, 0);
	waitKey(0);         

   // Canny Edge Detection

	namedWindow("Thresholding Operation", CV_WINDOW_AUTOSIZE );
    createTrackbar("Threshold Value", "Thresholding Operation", &threshold_value, MAX_BINARY_VALUE, thresholdingOperation);
	thresholdingOperation (0, 0);
	waitKey(0);                                          

   // Sobel Detection

	namedWindow("Sobel Operation", CV_WINDOW_AUTOSIZE );
    createTrackbar("Kernel Size", "Sobel Operation", &sobel_kernel_size, SOBEL_MAX_KERNEL_SIZE, sobelOperation);
	sobelOperation (0, 0);
	waitKey(0);                                          

   // Dilation Detection

	namedWindow("Dilation Operation", CV_WINDOW_AUTOSIZE );
    createTrackbar("Kernel Size", "Dilation Operation", &dilation_kernel, MAX_MORPHOLOGY_KERNEL_SIZE, dilationOperation);
	dilationOperation (0, 0);
	waitKey(0);                                          

 	return 0;
}

void thresholdingOperation (int, void*)
{
	threshold( gray_image, thresold_image, threshold_value, MAX_BINARY_VALUE, THRESH_BINARY);
	imshow("Thresholding Operation",  thresold_image);
}
void cannyOperation (int, void*)
{
	Canny( gray_image, canny_image, canny_low_threshold, canny_low_threshold*CANNY_RATIO, CANNY_KERNEL_SIZE, true );
	imshow("Canny Operation",  canny_image);
}
void sobelOperation (int, void*)
{
	Sobel( gray_image, sobel_image, SOBEL_DEPTH, SOBEL_X_DERIVATIVE, SOBEL_Y_DERIVATIVE,2*sobel_kernel_size+1, 
		SOBEL_SCALE, SOBEL_DELTA, BORDER_DEFAULT );
	imshow("Sobel Operation",  sobel_image);
}
void dilationOperation (int, void*)
{
	threshold( gray_image, thresold_image, MID_BINARY_VALUE, MAX_BINARY_VALUE, THRESH_BINARY);
	Mat element = getStructuringElement(MORPH_RECT, Size(2*dilation_kernel +1, 2*dilation_kernel+1), Point(dilation_kernel, dilation_kernel));
	dilate(thresold_image, dilation_image, element);

	imshow("Dilation Operation",  dilation_image);
}
