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

/* task1: 
* make b channal in the src image more intense, and draw a new window*/
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

/* task2: 
* using threshold function in open cv to binirize the imae
* have one color turn white while the rest go black 
* openCV theshold: double threshold(InputArray src, OutputArray dst, double thresh, double maxval, int type)
**/
void binirize_color(cv::Mat src){
	cv::Mat newImage = cv::Mat::zeros( src.size(), src.type() );
	// Convert the src image into an HSV image
	cvtColor(src, src, CV_BGR2HSV);
	// Detect the object based on HSV Range Values
    inRange(src, cv::Scalar(110, 40, 0), cv::Scalar(120, 255, 255), newImage);

    imshow("Thresholded Image", newImage);

	// threshold(src, dst, thresh, maxval, THRESH_BINARY); // threshold function
	//Mondrian: World map
	//blue: 120 53 73 
	//yellow: 48 254 208  #222222
	//red: 35 208 9 
}



/* task3:
* flip image with keyboard control 
* return a cv::Mat*/
cv::Mat flip_image(cv::Mat src){
	cv::Mat flippedImage;               // dst must be a different Mat
	cv::flip(src, flippedImage, 1);     // because you can't flip in-place (leads to segfault)
    // imshow("Flipped Image", flippedImage);

    return flippedImage;
}


/* task4:
* Gaussian blur */
cv::Mat Gaussian_blur(cv::Mat src, int kernalSize = 51){
	// Gaussian smoothing
	cv::Mat dst = cv::Mat::zeros( src.size(), src.type() );
	for ( int i = 1; i < kernalSize; i = i + 2 ){
	    cv::GaussianBlur( src, dst, cv::Size(i, i), 0, 0 );
	}

    return dst;
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

	//resize image until it fit the screen
	while((int)src.size().height > 800 || (int)src.size().width > 800){
		cv::resize(src,src, cv::Size(), 0.75, 0.75);
	}

	// print out information about the image
	printf("filename:         %s\n", filename);
	printf("Image size:       %d rows x %d columns\n", (int)src.size().height, (int)src.size().width);
	printf("Image dimensions: %d\n", (int)src.channels());
	printf("Image depth:      %d bytes/channel\n", (int)src.elemSize()/src.channels());

	// create a window
	cv::namedWindow(filename, 1);

	// edit the source image here
	

	// // show the image in a window
	// cv::imshow(filename, src);

	// //task1
	// // turn_blue(src);
	// //task2
	// //  binirize_color(src);
	//task 4
	Gaussian_blur(src);
	


	// // wait for a key press (indefinitely)	
	while(true){
    	cv::imshow(filename, src);
    	char keyPressed = cv::waitKey(1);
    	// printf("keyPressed is %c\n", keyPressed);

    	// if h, flip image
    	if( 'h' == keyPressed){ 
			//task3
			src = flip_image(src);
			printf(" 'h' key pressed, flip image\n");
		// if g, Gaussian blur
		}else if( 'g' == keyPressed){
			//task4
			src = Gaussian_blur(src, 31);
			printf(" 'g' key pressed, flip image\n");
		//if q, quit program
		}else if( 'q' == keyPressed){ 
			printf(" 'q' key pressed, quit program\n");
			break;
		}
	}

	// get rid of the window
	cv::destroyWindow(filename);
	// terminate the program
	printf("Terminating\n");

	return(0);
	
}
