#ifndef AUFGABENBLATT3_AUFGABE1_RINGBUFFER_H
#define AUFGABENBLATT3_AUFGABE1_RINGBUFFER_H
using namespace std;


template <typename T> class RingBuffer {

private:
    int size;
    int index;
    T *elements;

public:
    RingBuffer() = default;

    explicit RingBuffer(int size) {
        this->size = size;
        this->index = 0; // starts at first entry
        elements = new T[size];
    }

    ~RingBuffer() {
        delete[] elements;
    }

    void addElement(T element) {
        this->elements[this->index] = element;
        this->index += 1; // increase for next element
        if (this->index == this-> size)
            this->index = 0; //no place left -> overwriting first index next time
    }

    T &getElement(int index) {
        if (0 <= index && index < this->size)
            return elements[index];
        }

    int getSize() {
        return this->size;
    }
};



#endif //AUFGABENBLATT3_AUFGABE1_RINGBUFFER_H
