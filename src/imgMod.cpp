/*
	Heidi He
	S19 CS365 project 1
	Reading, manipulating, displaying, and writing an image

	Compile command

	clang++ -o imod -I /opt/local/include imgMod.cpp -L /opt/local/lib -lopencv_core -lopencv_highgui 
	
	To compile: make imod
	To run: ../bin/imod ../data/starfuries.png or ../bin/imod ../data/mondrian.jpg
*/
#include <cstdio>
#include <cstring>
#include "opencv2/opencv.hpp"

//for extensions
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
 #include <stdio.h>
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

/* Extension1: save image into file*/
void save_image(cv::Mat src){
	cv::imwrite("../output/savedImage.bmp", src);
}


/* Extesnsion2: add & blend two images */
cv::Mat blend_image(cv::Mat src1, cv::Mat src2, double alpha = 0.5){
	cv::resize(src2,src2,src1.size());//resize src2 to share the same size with image
	cv::Mat dst = cv::Mat::zeros( src1.size(), src1.type() );
	double beta = ( 1.0 - alpha );
 	cv::addWeighted( src1, alpha, src2, beta, beta, dst);

 	return dst;
}

/* Extension3: face detection and draw square*/
void detect_face( cv::Mat src, cv::CascadeClassifier cascade, double scale){
	std::vector<cv::Rect> faces;
	cv::Mat gray;
	cv::cvtColor( src, gray, CV_BGR2GRAY );

	cascade.detectMultiScale( gray, faces, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );

	//draw tectangle:
	for ( size_t i = 0; i < faces.size(); i++ ){
		cv::Rect r = faces[i];
		cv::Scalar color = cvScalar(255, 0, 0);
		rectangle( src, cvPoint(cvRound(r.x*scale), 
						cvRound(r.y*scale)), 
						cvPoint(cvRound((r.x + r.width-1)*scale), 
						cvRound((r.y + r.height-1)*scale)), 
						color, 3, 8, 0);
	}

	imshow( "Face Detection", src );
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

	cv::Mat src2 = cv::imread("../data/manet.jpg");
	// test if the read was successful
	if(src2.data == NULL) {
		printf("Unable to read image ../data/manet.jpg\n");
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

	// //task 4
	// Gaussian_blur(src);

	// // wait for a key press (indefinitely)	
	while(true){
    	cv::imshow(filename, src);
    	char keyPressed = cv::waitKey(1);
    	// printf("keyPressed is %c\n", keyPressed);
    	// if b, blend images
    	if( 'b' == keyPressed){
    		//extension 2
    		src = blend_image(src, src2, 0.2);
			printf(" 'b' key pressed, blend images\n");
		// if d, detect face
    	}else if( 'd' == keyPressed){
    		// cascade.load( "../../haarcascade_frontalcatface.xml" );
    		cv::CascadeClassifier face_cascade;
    		if( !face_cascade.load( "../data/haarcascade_frontalface_alt2.xml" ) ){ 
    			printf("--(!)Error loading\n"); 
    			return -1; 
    		};
    		// face_cascade.load("../../haarcascade_frontalface_default.xml");
    		detect_face(src, face_cascade, 1);
			printf(" 'd' key pressed, detect face\n");
    	}
    	// if h, flip image
    	else if( 'f' == keyPressed){ 
			//task3
			src = flip_image(src);
			printf(" 'f' key pressed, flip image\n");
		// if g, Gaussian blur
		}else if( 'g' == keyPressed){
			//task4
			src = Gaussian_blur(src, 31);
			printf(" 'g' key pressed, flip image\n");
		}else if( 's' == keyPressed){
			//extension 1 - save image
			save_image(src);
			printf(" 's' key pressed, save image\n");
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
