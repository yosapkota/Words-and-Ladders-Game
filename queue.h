#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdexcept>

const int QUEUE_SIZE = 10;

template <typename QueueType>
class Queue {
public:
    Queue(void) {
        count = tail = 0;
        head = QUEUE_SIZE - 1;
        data = new QueueType[QUEUE_SIZE];
        capacity = QUEUE_SIZE;
    }

    ~Queue(void) { delete[] data; }

    void clear(void) { count = tail = 0; head = QUEUE_SIZE - 1; }
    int size(void) { return count; }
    bool isEmpty(void) { return count == 0; }

    void enqueue(const QueueType &d) {

        if (count == capacity) {
            int tmpCap = 2 * capacity;
            QueueType
                    *tmpData = new QueueType[tmpCap];

            if(tmpData == nullptr) {
                throw std::overflow_error("Queue is full");
            }

            for (int i=0; i < capacity; i++) {
                tmpData[i] = data[(head+i+1)%capacity];
            }

            delete [] data;
            data= tmpData;


            head = tmpCap - 1;
            tail = capacity;
            capacity = tmpCap;

        }
        data[tail] = d;

        tail = ++tail % capacity;

        count++;
    }

    QueueType dequeue(void) {

        if (!count)
            throw std::underflow_error("Queue is empty");

        count--;

        head = ++head % capacity;

        return data[head];

    }

private:
    QueueType
    //data[QUEUE_SIZE];
    *data;
    int
            count,head,tail,capacity;
};

#endif
