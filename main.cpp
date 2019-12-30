#include <unistd.h>
#include "BufferQueue.h"
#include "Producer.h"
#include "Consumer.h"



int main()
{

    BufferQueue bufferQueue;
    Producer producer(1, &bufferQueue);
    producer.StartProducing();

    Consumer consumer(1, &bufferQueue);
    consumer.StartConsuming();
    


    for (int i = 0; i < 10; ++i)
        sleep(1);

    while (true)
    {
        int keyboard = waitKey(1);
        if (keyboard == 'q' || keyboard == 27)
        {
            producer.StopProducing();
            consumer.StopConsuming();
            return 0;
        }
    }

    return 0;
}