#pragma once
#include "BufferQueue.h"


class Consumer {

public:
    Consumer(int unique_id, BufferQueue* bQueue);
    void StartConsuming();
    void StopConsuming();

private:
    static void* consumeProduct(void* param);
    bool detectClosedEyes();

    bool sentinal;
    BufferQueue* m_bufferQueue;
    pthread_t thread;
    Mat my_consumed_frame;
    int m_uniqueid;
    int m_count;
    int m_countClosed;

    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;

    String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
    String face_cascade_name = "haarcascade_frontalface_alt.xml";


};


inline Consumer::Consumer(int unique_id, BufferQueue* bQueue)
{
    m_uniqueid = unique_id;
    m_bufferQueue = bQueue;
    m_count = 0;
    m_countClosed = 0;

    //-- 1. Load the cascades
    if (!face_cascade.load(face_cascade_name))
    {
        throw "--(!)Error loading face cascade\n";
    };
    if (!eyes_cascade.load(eyes_cascade_name))
    {
        throw "--(!)Error loading face cascade\n";
    };


}


inline void Consumer::StartConsuming()
{
    sentinal = true;
    pthread_create(&thread, NULL, consumeProduct, this);
}

inline void Consumer::StopConsuming()
{
    sentinal = false;
    void* ret_val;
    pthread_join(thread, &ret_val);
}

inline void* Consumer::consumeProduct(void* param)
{
    Consumer* _this = (Consumer*)param;
    while (_this->sentinal)
    {
        _this->my_consumed_frame = _this->m_bufferQueue->consumeFromQueue();
        if (!_this->detectClosedEyes())   //no closed eyes
        {
            _this->m_countClosed = 0;
        }
        if (_this->m_countClosed > 8)
        {
            cout << "sleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\nsleeping!!!!!\n";
            system("python3 speaker.py");
        }

        ++_this->m_count;
    }

 
    return NULL;
}


inline bool Consumer::detectClosedEyes()
{
    if (my_consumed_frame.empty())
    {
        return false;
    }
    
    Mat gray;
    cvtColor(my_consumed_frame, gray, COLOR_BGR2GRAY);

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
        cout << "found face\n";
        //cerr << "Detection " << faces[i] << " with weight " << weights[i] << endl;
        Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        ellipse(my_consumed_frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
        Mat faceROI = gray(faces[i]);
        //-- In each face, detect eyes
        std::vector<Rect> eyes;
        eyes_cascade.detectMultiScale(faceROI, eyes);
        if (eyes.size() <= 1)
        {
            ++m_countClosed;
            return true;
        }
        for (size_t j = 0; j < eyes.size(); j++)
        {
            Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
            int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
            circle(my_consumed_frame, eye_center, radius, Scalar(255, 0, 0), 4);
        }
    }

    //       imshow("Eyes", frame);

    char buff[30];
    sprintf(buff, "sleepOutput%02d.jpg", m_count);
    imwrite(buff, my_consumed_frame);
    return false;
}