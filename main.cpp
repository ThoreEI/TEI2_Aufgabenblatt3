#include "TemplateArray.h"
#include "RingBuffer.h"
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;
using namespace std;

typedef struct  WavHead {
    char chunkID[4];
    long chunkSize;
    char format[4];
    char subChunkOneID[4];
    long subChunkOneSize;
    short audioFormat;
    short numberOfChannels;
    long sampleRate;
    long byteRate;
    short blockAlign;
    short bitsPerSample;
    char subChunkTwoID[4];
    long subChunkTwoSize;
} header;

container<int> readHeader(header head, FILE *filePath);
void printHeader(container<int> templateArray);
container<char> readData(const char *filePath);
void writeNewWavFile(container<int> container1, container<char> container2);
int getFileSize(FILE *wavFile);

int main() {
    /* Aufgabe 1
     * Klasse Container erstellen (siehe TemplateArray.h)
     */

    /* Aufgabe 2
     * WAV-File einlesen mit Template-Array
     */
    header head;
    FILE *wavFile;
    const char *filePath;
    filePath = "C://Users//UnknownUser//CLionProjects//Aufgabenblatt3//Aufgabenblatt3_Aufgabe1//test.wav";
    wavFile = fopen(filePath, "r"); // "r" for reading

    /* Aufgabe 3
     * RingBuffer implementieren (siehe RingBuffer.h)
     * und zu Sound Samples der WAV-Datei 8000 addieren -->  Verzögerung
     */
    container <int> wavHead = readHeader(head, wavFile);
    printHeader(wavHead);


    container <char> wavData = readData(filePath);
    cout << " Head: " << wavHead.getSize() << "Data: " << wavData.getSize() << endl;
    writeNewWavFile(wavHead, wavData);
    wavData.toString();
}

container <int> readHeader(header head, FILE *wavFile) {
    if (!wavFile) {
        cout << " File not found.";
        return container<int>(0);
    }
    // printing the size (in bytes) of the wav file
    int fileSize = getFileSize(wavFile);
    cout << " Size of the wav file: " << fileSize << " bytes" << endl;
    // computing the read header bytes for later calculations/prints
    size_t bytesReadFromHeader = fread(&head, 1, sizeof(struct WavHead), wavFile);
    //filling 'Template-Array' with head information
    container<int> templateArray((int) bytesReadFromHeader);
    for (int i = 0; i < 4; i++)
        templateArray[i] = (unsigned char) head.chunkID[i];
    templateArray[4] = head.chunkSize;
    for (int i = 5; i < 9; i++)
        templateArray[i] = (unsigned char) head.format[-5 + i];
    for (int i = 9; i < 13; i++)
        templateArray[i] = (unsigned char) head.subChunkOneID[-9 + i];
    templateArray[13] = head.subChunkOneSize;
    templateArray[14] = head.audioFormat;
    templateArray[15] = head.numberOfChannels;
    templateArray[16] = head.sampleRate;
    templateArray[17] = head.byteRate;
    templateArray[18] = head.blockAlign;
    templateArray[19] = head.bitsPerSample;
    for (int i = 20; i < 24; i++)
        templateArray[i] = (unsigned char) head.subChunkTwoID[-20 + i];
    templateArray[24] = head.subChunkTwoSize;
    templateArray[25] = (int) bytesReadFromHeader;
    fclose(wavFile);
    return templateArray;
}

void printHeader (container <int> templateArray) {
    //printing the header
    int bytesReadFromHeader = templateArray[25];
    cout << "\n Scanned the " << bytesReadFromHeader << " bytes large header:" << endl;
    cout << " ---------------------------------" << endl;
    cout << " Chunk ID:        : " << (char) templateArray[0] << (char) templateArray[1] << (char) templateArray[2]
         << (char) templateArray[3] << endl; // marks the file as a "riff" file
    cout << " File size        : " << templateArray[4] << " bytes" << endl;
    cout << " Format           : " << (char) templateArray[5] << (char) templateArray[6] << (char) templateArray[7]
         << (char) templateArray[8] << endl; // file type header
    cout << " Subchunk1 ID     : " << (char) templateArray[9] << (char) templateArray[10]
         << (char) templateArray[11]
         << (char) templateArray[12] << endl; //format chunk marker
    cout << " Subchunk1 size   : " << templateArray[13] << endl; //length of format data listed above
    cout << " Audio format     : " << templateArray[14] << endl; // type of audio format (example: 1 --> PCM)
    cout << " Channels         : " << templateArray[15] << endl; // number of channels
    cout << " Sample rate      : " << templateArray[16] << " samples/sec"
         << endl; // number of samples per second, or hertz
    cout << " Byte rate        : " << templateArray[17] << " bytes/sec"
         << endl;// (Sample Rate * BitsPerSample * Channels) / 8
    cout << " Block align      : " << templateArray[18]
         << endl; // (BitsPerSample * Channels) / 8.1 - 8 bit mono2 - 8 bit stereo/16 bit mono4 - 16 bit stereo
    cout << " Bits per sample  : " << templateArray[19] << endl; // number of bits per sample
    cout << " Subchunk2 ID     : " << (char) templateArray[20] << (char) templateArray[21]
         << (char) templateArray[22]
         << (char) templateArray[23] << endl; // data description header: "data"
    cout << " Subchunk2 size   : " << templateArray[24] << " bytes"
         << endl; //number of bytes in the audio data == samples * channels * bits per sample / 8
    cout << " ---------------------------------" << endl;
}

container <char> readData (const char *filePath) {
    container <char> templateArray(100);
    fstream wavFile = nullptr;
    wavFile.open(filePath, ios::in);
    if (wavFile.is_open()) {
        char charOfWavFileData;
        int index = 0;
        while (wavFile.get(charOfWavFileData)) { //skipping first 44 reads (header data)
            if (index > sizeof(header))
                templateArray[index] = charOfWavFileData;
        index++;
        }
        wavFile.close();
    }
    return templateArray;
}

void writeNewWavFile(container<int> head, container<char> data) {
    FILE *outputFile = nullptr;
    outputFile = fopen("C://Users//UnknownUser//CLionProjects//Aufgabenblatt3//Aufgabenblatt3_Aufgabe1//new.wav", "wb"); //write binaries
    for (int i = 0; i < head.getSize(); i++)
        fwrite((char*) &head[i], sizeof(int), 1, outputFile);
    for (int i = 0; i < data.getSize(); i++)
        fwrite((char*) &data[i], sizeof(char), 1, outputFile);
}

int getFileSize(FILE *wavFile) {
    int fileSize;
    fseek(wavFile, 0, SEEK_END);
    fileSize = ftell(wavFile);
    fseek(wavFile, 0, SEEK_SET);
    return fileSize;
}



