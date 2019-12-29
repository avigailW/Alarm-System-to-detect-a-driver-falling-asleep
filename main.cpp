#include <cstdio>


#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include <iostream>
#include<string>

using namespace std;
using namespace cv;

string eye_cascPath = "haarcascade_eye_tree_eyeglasses.xml";  //eye detect model
string face_cascPath = "haarcascade_frontalface_alt.xml";  //face detect model
//faceCascade = cv2.CascadeClassifier(face_cascPath)
//eyeCascade = cv2.CascadeClassifier(eye_cascPath)

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

void detectClosedEyes()
{
    String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
    String face_cascade_name = "haarcascade_frontalface_alt.xml";

    //-- 1. Load the cascades
    if (!face_cascade.load(face_cascade_name))
    {
        cout << "--(!)Error loading face cascade\n";
        return;
    };
    if (!eyes_cascade.load(eyes_cascade_name))
    {
        cout << "--(!)Error loading eyes cascade\n";
        return;
    };


    VideoCapture cap = VideoCapture(0);

    while (true)
    {
        if (!cap.isOpened())
        {
            cout << "Could not initialize capturing...\n";
            return;
        }
//        namedWindow("Eyes", 1);

        Mat frame;
        cap >> frame;
        if (frame.empty())
        {
            break;
        }

        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // ret, img = cap.read()

             // Detect faces in the image

        std::vector<Rect> faces;
        /*vector<double> weights;
        vector<int> levels;*/

        face_cascade.detectMultiScale(gray, faces, 1.1, 5, 0, Size(30, 30), Size());// , levels, weights, 1.1, 3, 0, Size(), Size(), true);

            //faces = faceCascade.detectMultiScale(
            //    frame,
            //    scaleFactor = 1.1,
            //    minNeighbors = 5,
            //    minSize = (30, 30),
            //    # flags = cv2.CV_HAAR_SCALE_IMAGE
            //)
            //# print("Found {0} faces!".format(len(faces)))

        for (size_t i = 0; i < faces.size(); i++)
        {
            //cerr << "Detection " << faces[i] << " with weight " << weights[i] << endl;

            Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
            ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
            Mat faceROI = gray(faces[i]);
            //-- In each face, detect eyes
            std::vector<Rect> eyes;
            eyes_cascade.detectMultiScale(faceROI, eyes);
            for (size_t j = 0; j < eyes.size(); j++)
            {
                Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
                int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
                circle(frame, eye_center, radius, Scalar(255, 0, 0), 4);
            }
        }

 //       imshow("Eyes", frame);

        int keyboard = waitKey(1);
        if (keyboard == 'q' || keyboard == 27)
            break;
    }
}

int main()
{

    detectClosedEyes();

    return 0;
}