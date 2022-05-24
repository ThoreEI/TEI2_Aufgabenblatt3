#ifndef AUFGABENBLATT3_AUFGABE1_RINGBUFFER_H
#define AUFGABENBLATT3_AUFGABE1_RINGBUFFER_H

template <typename T> class RingBuffer {
public:
    RingBuffer() = default;
    explicit RingBuffer(int size) {
        this->size = size;
    }
    ~RingBuffer() {
        delete[] elements;
    }

    int getSize () {
        return size;
    }

private:
    int size{};
    int*elements{};
};


#endif //AUFGABENBLATT3_AUFGABE1_RINGBUFFER_H
