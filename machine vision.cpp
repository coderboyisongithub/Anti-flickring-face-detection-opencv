#include "stdafx.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

CascadeClassifier face_cascade, eyes_cascade;
String window_name = "Face Detection";
Point buffer;
int w,h;

/**
 * Detects faces and draws an ellipse around them
 */
void detectFaces(Mat frame) {

  std::vector<Rect> faces;
  Mat frame_gray;

  // Convert to gray scale
  cvtColor(frame, frame_gray, COLOR_BGR2GRAY);

  // Equalize histogram
  equalizeHist(frame_gray, frame_gray);

  // Detect faces
  face_cascade.detectMultiScale(frame_gray, faces, 1.2, 3,
	  0|CASCADE_SCALE_IMAGE|CASCADE_FIND_BIGGEST_OBJECT, Size(100,100));

  // Iterate over all of the faces
  int i=0;

	  
    // Find center of faces
  if(faces.size()>0)
  {

    Point center(faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2);
    Mat face = frame_gray(faces[i]);
    std::vector<Rect> eyes;
	
    // Try to detect eyes, inside each face
    
				  


    printf("%d %d\n",buffer.x,buffer.y);
      // Draw ellipse around face
		 if(abs(center.x-buffer.x)>5 && abs(center.y-buffer.y)>5){
			 buffer.x=center.x;
			 buffer.y=center.y;
			 if(abs(faces[i].width-w)>5 && abs(faces[i].height-h)>5)
			 {
				 w=faces[i].width;h=faces[i].height;
   circle(frame,buffer,abs(w/2),Scalar(255,255,0),3);
	 
		  }
			 else
			 {
				 circle(frame,buffer,abs(w/2),Scalar(255,255,0),3);
			 }

		  }
		 else
			 circle(frame,buffer,abs(w/2),Scalar(255,255,0),3);
  }
 

  // Display frame
  imshow( window_name, frame );
}


int main() {

  VideoCapture cap(0); // Open default camera
  Mat frame;
  buffer=Point();
  buffer.x=buffer.y=0;
  w=h=0;
  face_cascade.load("haarcascade_frontalface_alt.xml"); // load faces
  eyes_cascade.load("haarcascade_eye_tree_eyeglasses.xml"); // load eyes

  while(cap.read(frame)) {
    detectFaces(frame); // Call function to detect faces
    if( waitKey(30) >= 0)    // pause
      break;
  }
  return 0;
}