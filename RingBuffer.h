#ifndef AUFGABENBLATT3_AUFGABE1_RINGBUFFER_H
#define AUFGABENBLATT3_AUFGABE1_RINGBUFFER_H

#include <fstream>

using namespace std;

template <typename T> class RingBuffer {

private:
    const int size = 8000;
    int index;
    T *ringBuffer;

public:

    RingBuffer() {
        this->index = 0; // starts at first entry
        ringBuffer = new T[size];
    }

    ~RingBuffer() {
        delete[] ringBuffer;
    }

    T& operator[] (int position) { //for setting and getting entries
        this->index += 1; // increase for next element
        if (this->index == this-> size)
            this->index = 0; //no place left -> overwriting first index next time
        return ringBuffer[position];
    }

    int getSize() {
        return this->size;
    }

    void toString() {
        for (int i = 0; i < this->getSize(); i++)
            cout << (char) this->ringBuffer[i] << " ";
    }
};



#endif //AUFGABENBLATT3_AUFGABE1_RINGBUFFER_H
