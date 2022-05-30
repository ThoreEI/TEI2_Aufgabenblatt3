#ifndef AUFGABENBLATT3_AUFGABE1_TEMPLATEARRAY_H
#define AUFGABENBLATT3_AUFGABE1_TEMPLATEARRAY_H
#endif
#include <cstdio>
#include <typeinfo>
#include <iomanip>
#include <iostream>
using namespace std;

template< typename T > class container {
private:
    int size{};
    T *templateArray;
public:
    container()= default;

    explicit container(int size) {
        this->size = size;
        templateArray = new T[size];
    }

//    ~container() { // free up memory
//        delete[] templateArray; // doesn't work, why?
//    }

    //Override
    T& operator[] (int index) {
        if (index >= size)
            createNewTemplateArray(index);
        return templateArray[index];
    }

    void createNewTemplateArray (int index) {
        T *newTemplateArray = new T[index];
        for (int i = 0; i < size; ++i) //transfer all entries
            newTemplateArray[i] = templateArray[i];
        delete[] templateArray; //free up memory //doesn't work, why?
        this->size = index + 1;
        templateArray = newTemplateArray; //set the new reference
    }

    int getSize() {
        return this->size;
    }

    void toString() {
        for (int i = 0; i < this->getSize(); i++)
            cout << this->templateArray[i] << " ";
    }
};

