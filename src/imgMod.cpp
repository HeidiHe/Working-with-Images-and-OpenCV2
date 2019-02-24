/*
	Bruce A. Maxwell
	J16 
	Simple example of reading, manipulating, displaying, and writing an image

	Compile command

	clang++ -o imod -I /opt/local/include imgMod.cpp -L /opt/local/lib -lopencv_core -lopencv_highgui 

*/
#include <cstdio>
#include <cstring>
#include "opencv2/opencv.hpp"

/* task1: make b channal in the src image more intense, and draw a new window*/
void turn_blue(cv::Mat src){
	cv::Mat newImage = cv::Mat::zeros( src.size(), src.type() );
	for(int i=0; i < src.rows; i++){ //i is rows
		for(int j=0; j < src.cols; j++){
			//To access each pixel in the images we are using this syntax: 
			//image.at<Vec3b>(y,x)[c] where y is the row, x is the column and c is R, G or B (0, 1 or 2).
			int blue = src.at<cv::Vec3b>(j,i)[0];
			newImage.at<cv::Vec3b>(j,i) = src.at<cv::Vec3b>(j,i);
			if(blue<150){
				newImage.at<cv::Vec3b>(j,i)[0] = blue + 100;
			}
		}
	}

	cv::imshow("Edited Image", newImage);
}

void binirize_color(cv::Mat src){

}


int main(int argc, char *argv[]) {
	cv::Mat src;
	char filename[256];

	// usage
	if(argc < 2) {
		printf("Usage %s <image filename>\n", argv[0]);
		exit(-1);
	}
	strcpy(filename, argv[1]);

	// read the image
	src = cv::imread(filename);

	// test if the read was successful
	if(src.data == NULL) {
		printf("Unable to read image %s\n", filename);
		exit(-1);
	}

	// print out information about the image
	printf("filename:         %s\n", filename);
	printf("Image size:       %d rows x %d columns\n", (int)src.size().height, (int)src.size().width);
	printf("Image dimensions: %d\n", (int)src.channels());
	printf("Image depth:      %d bytes/channel\n", (int)src.elemSize()/src.channels());

	// create a window
	cv::namedWindow(filename, 1);
	cv::namedWindow("Edited Image", 1);

	// edit the source image here
	

	// show the image in a window
	cv::imshow(filename, src);

	//task1
	turn_blue(src);

	//task2
	binirize_color(src);

	// wait for a key press (indefinitely)
	cv::waitKey(0);

	// get rid of the window
	cv::destroyWindow(filename);

	// terminate the program
	printf("Terminating\n");

	return(0);
}
