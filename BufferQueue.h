#pragma once
#include <pthread.h>

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

#define BUFFER_SIZE 30

class BufferQueue {

public:
    void addProductToQueue(Mat product);
    Mat consumeFromQueue();
    BufferQueue();
    ~BufferQueue();

private:
    int in;
    int out;
    Mat m_buffer[BUFFER_SIZE];
    pthread_mutex_t m_lock;


};

inline BufferQueue::BufferQueue() {
    pthread_mutex_init(&m_lock, NULL);
    in = 0;
    out = 0;
}

inline BufferQueue::~BufferQueue() {
    pthread_mutex_destroy(&m_lock);
}

inline void BufferQueue::addProductToQueue(Mat product) {


    pthread_mutex_lock(&m_lock);
    if (((in + 1) % BUFFER_SIZE) != out)/* do nothing */
    {
        //printf("thread id: %d - product %d producing %d\n", pid, in, product);
        m_buffer[in] = product;
        in = (in + 1) % BUFFER_SIZE;
    }
    pthread_mutex_unlock(&m_lock);

}

inline Mat BufferQueue::consumeFromQueue() {
    Mat next_consumed;
    pthread_mutex_lock(&m_lock);
    if (in != out) /* do nothing */
    {
        next_consumed = m_buffer[out];
        //printf("thread id: %d - consumer %d consuming %d\n", pid, out, next_consumed.num);
        out = (out + 1) % BUFFER_SIZE;
        /* consume the item in next consumed */

    }
    pthread_mutex_unlock(&m_lock);
    return next_consumed;

}
