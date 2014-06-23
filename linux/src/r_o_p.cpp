#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <thread>
#include <chrono>

#include <curses.h>

#include "settings.h"
#include "control.cpp"

using namespace std;
using namespace cv;

/** Forward declarations */
void processFrame( Mat frame );
int mainVision();
int keyboardInput();
void controlTest();
void trackPoint(Point frameCentre, Point faceCentre);

// Classifiers (eyes, nose and mouth are out for a bit until a simple version is all happy on the Robot)
String face_cascade_name = "classifiers/haarcascade_frontalface_alt.xml";
//String eyes_cascade_name = "classifiers/haarcascade_eye_tree_eyeglasses.xml";
//String nose_cascade_name = "classifiers/haarcascade_mcs_nose.xml";
//String mouth_cascade_name = "classifiers/haarcascade_mcs_mouth.xml";

CascadeClassifier face_cascade;
//CascadeClassifier eyes_cascade;
//CascadeClassifier nose_cascade;
//CascadeClassifier mouth_cascade;
string windowName = "Face Tracking";

// Flags whether a human face is detected by the vision thread
bool faceDetected = false;

//To contain all detected faces
std::vector<Rect> faces;

//Arduino control
Control control;

// Test control
bool test = false;
bool tp_test = false;
bool drive_test = true;
// Mode
int manual = true;
int vision = true;

int main()
{
	// Physical check that we've got full control over the tilt/pan servos
	if (test) {
		controlTest();
	}

	if (vision) {
		std::thread vision (mainVision);
		vision.join();
	}

	if (manual) {
		std::thread vision (keyboardInput);
		vision.join();
	}

	return 0;
}

/**
 * Governs the main loop for the manual control thread
 */
int keyboardInput() {
	int ch;
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);

    while ( (ch = getch()) != KEY_QUIT ) {
    	switch(ch) {
    		case KEY_LEFTFORWARD:
    			control.driveLeftForward();
    			break;
    		case KEY_LEFTSTOP:
    			control.driveLeftStop();
    			break;
    		case KEY_LEFTREVERSE:
    			control.driveLeftReverse();
    			break;
    		case KEY_RIGHTFORWARD:
    			control.driveRightForward();
    			break;
    		case KEY_RIGHTSTOP:
    			control.driveRightStop();
    			break;
    		case KEY_RIGHTREVERSE:
    			control.driveRightReverse();
    			break;
    		default:
    			break;
    	}

    	std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    endwin();

	return 0;
}

/**
 * Governs the main loop for the vision thread
 */
int mainVision() {
	// Open the default camera
	VideoCapture cap(0);
	// Check if we succeeded
	if ( ! cap.isOpened()) {
		return -1;
	}

	Mat frame;

	// Load the cascades
	if( ! face_cascade.load(face_cascade_name)) {
		cout << "Error loading face cascade" << endl;
		return -1;
	}

	while(true)
	{
		// Grab a frame
		cap >> frame;

		if( ! frame.empty()) {
			// Scale the image down for performance
			resize(frame, frame, Size(), 0.5, 0.5);
			// Do the do's
			processFrame(frame);
		} else {
			cout << "No captured frame -- Break!" << endl;
			break;
		}

		// Slow up the rate we're processing the frame, because otherwise we get ahead of the poor little Arduino.
		// @todo This is an arbitrary sleep, some maths might be done around making the processing time for each frame
		// an equal length
		std::this_thread::sleep_for(std::chrono::milliseconds(40));
	}

	return 0;
}

/**
 *  Called to process each frame captured from the camera
 */
void processFrame( Mat frame ) {
	Mat frame_gray;

	// Bit of help to clarify faces
	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	// Detect faces
	face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

	cv::Size s = frame.size();

	Point frameCentre(s.width / 2, s.height / 2);
	Point targetCentre;

	circle( frame, frameCentre, 1, Scalar( 255, 255, 0 ), 4, 8, 0 );

	faceDetected = false;

	for(size_t i = 0; i < faces.size(); i++)
	{
		faceDetected = true;

		Point faceCentre( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
		targetCentre = faceCentre;

		circle(frame, faceCentre, 1, Scalar( 255, 255, 255 ), 2, 8, 0);

		Mat faceROI = frame_gray( faces[i] );
		std::vector<Rect> eyes;
	}

	if (faceDetected) {
		trackPoint(frameCentre, targetCentre);
	}

	// Display the frame
	imshow(windowName, frame);
}

/**
 * Moves the camera one increment on the x and/or y axis if the target point is out of the centre area
 */
void trackPoint(Point centre, Point target)
{
	if (centre.x < (target.x - 30)) {
		control.camRight();
	}

	if (centre.x > (target.x + 30)) {
		control.camLeft();
	}

	if (centre.y < (target.y - 30)) {
		control.camDown();
	}

	if (centre.y > (target.y + 30)) {
		control.camUp();
	}
}

/*
 * Operates all motors to prove we've control
 */
void controlTest() {
	if (tp_test) {
		// Tilt/Pan
		for(int n=10; n>0; n--) {
			control.camLeft();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		for(int n=10; n>0; n--) {
			control.camRight();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		for(int n=10; n>0; n--) {
			control.camUp();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		for(int n=10; n>0; n--) {
			control.camDown();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	if (drive_test) {
	// Drive
		control.driveLeftForward();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		control.driveLeftStop();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		control.driveLeftReverse();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		control.driveLeftStop();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		control.driveRightForward();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		control.driveRightStop();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		control.driveRightReverse();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		control.driveRightStop();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

/*  Eyes, nose and face - later on down the line
if( ! eyes_cascade.load(eyes_cascade_name)) {
	cout << "Error loading eye cascade" << endl;
	return -1;
};
if( ! mouth_cascade.load(mouth_cascade_name)) {
	cout << "Error loading face cascade" << endl;
	return -1;
}
if( ! nose_cascade.load(nose_cascade_name)) {
	cout << "Error loading eye cascade" << endl;
	return -1;
};
*/

/* Something like this will go in to detect eyes, nose and mouth when we're looking at recognition...way down the line...

eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

for( size_t j = 0; j < eyes.size(); j++ )
{
	Point centre( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
	circle( frame, centre, 1, Scalar( 255, 0, 0 ), 4, 8, 0 );
}

std::vector<Rect> nose;
nose_cascade.detectMultiScale(faceROI, nose, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

for( size_t j = 0; j < nose.size(); j++ )
{
	Point centre( faces[i].x + nose[j].x + nose[j].width*0.5, faces[i].y + nose[j].y + nose[j].height*0.5 );
	circle( frame, centre, 1, Scalar( 255, 0, 0 ), 4, 8, 0 );
}

std::vector<Rect> mouth;
mouth_cascade.detectMultiScale(faceROI, mouth, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

for( size_t j = 0; j < mouth.size(); j++ )
{
	Point centre( faces[i].x + mouth[j].x + mouth[j].width*0.5, faces[i].y + mouth[j].y + mouth[j].height*0.5 );
	circle( frame, centre, 1, Scalar( 255, 0, 0 ), 4, 8, 0 );
}
*/
