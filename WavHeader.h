#include <iostream>
#include <string>
#include <fstream>
#include "TemplateArray.h"
#include "RingBuffer.h"
#ifndef AUFGABENBLATT3_AUFGABE1_WAVHEADER_H
#define AUFGABENBLATT3_AUFGABE1_WAVHEADER_H

class WAV_HEADER {
private:

    char buffer[8000];

public:



    void BuffertoFile (container<char> templateArray) {
        ofstream file;
        file.open("C://Users//UnknownUser//CLionProjects//Aufgabenblatt3//Aufgabenblatt3_Aufgabe1//test.wav", ios::out);
        for (char &i: this->buffer) {
            i = 0; // temporary char
        }
        int index = 0;
        int len = templateArray.getSize() + 8000;
        for (int i = 0; i < 44; ++i) {// header
            cout << templateArray[i] << " ";
            templateArray[i] = templateArray[i];
        }
        for (int i = templateArray; i < len; ++i) { // after header
            cout << buffer[index] << " ";
            templateArray[i] = buffer[index];
            buffer[index] = templateArray[i];
            index = (index + 1) % 8000;
        }
        for (int i = 0; i < templateArray.getSize(); ++i) {
            file << templateArray[i];
        }
        file.close();
    }

    void print(container <char> templateArray) {
        for (int i = 0; i < 10000; ++i) {
            cout << templateArray[i];
        }
    }
};

#endif //AUFGABENBLATT3_AUFGABE1_WAVHEADER_H
