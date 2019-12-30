#pragma once

#include "BufferQueue.h"
#include <ctime>
#include <chrono>


class Producer {
public:

    Producer(int unique_id, BufferQueue* bQueue)
    {
        m_uniqueid = unique_id;
        m_bufferQueue = bQueue;
     
        m_count = 0;
    }

    ~Producer()
    {

    }

    void StartProducing()
    {
        sentinal = true;
        m_count = 0;
        pthread_create(&m_thread, NULL, addProduct, this);
    }

    void StopProducing()
    {
        sentinal = false;
        void* ret_val;
        pthread_join(m_thread, &ret_val);
    }

private:
    static void* addProduct(void* param)
    {

        VideoCapture cap = VideoCapture(0);
        time_t tt;
        Producer* _this = (Producer*)param;
        while (_this->sentinal )    // add condition vidio still working
        {
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            cap >> _this->my_created_product;
            char buff[30];
            sprintf(buff, "output%02d.jpg", _this->m_count);
            imwrite(buff, _this->my_created_product);
            _this->m_bufferQueue->addProductToQueue(_this->my_created_product);
            ++(_this->m_count);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;


        }

        return NULL;
}
    bool sentinal;
    BufferQueue* m_bufferQueue;
    pthread_t m_thread;
    Mat my_created_product;
    VideoCapture *m_cap;
    int m_uniqueid;
    int m_count;
};

