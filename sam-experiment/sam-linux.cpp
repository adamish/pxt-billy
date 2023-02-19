/*
 * Build under Linux for experimentation
 */
#include "render.h"
#include "sam.h"
#include "reciter.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include "WavWriter.h"

using namespace billy;

WavWriter *w;

int main(void) {

    char input[256];

    SetSingmode(1);
    SetSpeed(72);
    SetPitch(64);
    SetMouth(128);
    SetThroat(128);

    const char *example = "I am a computer";
    for (unsigned int i = 0; i < sizeof(input); i++) {
        input[i] = 0;
    }
    for (unsigned int i = 0; i < strlen(example); i++) {
        input[i] = example[i];
    }

    int x = billy::TextToPhonemes((unsigned char *)input);
    std::cout << "TextToPhonemes " << x << std::endl;

    for (unsigned int i = 0; i < 256; i++) {
        std::cout << input[i];
    }
    std::cout << std::endl;

    for (unsigned int i = 0; i < 256; i++) {
        std::cout << (int) input[i] << ",";
    }
    std::cout << std::endl;

    SetSingmode(1);
    EnableSingmode();

    const char *ph = "#115AY4";

    for (unsigned int i = 0; i < sizeof(input); i++) {
        input[i] = 32;
    }
    unsigned int length = strlen(ph);
    if (length > 255) {
        length = 255;
    }
    for (unsigned int i = 0; i < length; i++) {
        input[i] = ph[i];
    }
    input[length] = -101;
    std::cout << "Length " << strlen(input) << std::endl;
    for (unsigned int i = 0; i < strlen(input); i++) {
        std::cout << (int) input[i] << ",";
    }
    std::cout << std::endl;

    std::cout << "Length " << strlen(ph) << std::endl;
    billy::SetInput(input);

    w = new WavWriter();
    w->setSampleRate(22500);
    w->init("out.wav");

    std::cout << ph << std::endl;
    int ret = billy::SAMMain();
    std::cout << "main " << ret << std::endl;

    w->close();
    return 0;
}

namespace billy {
int debug = 1;

unsigned int outputPos = 0;
unsigned int bufferSize = 4096;
char bufferSound[4096];
unsigned int inputPosOffset = 0;

void SamOutputByte(unsigned int pos, unsigned char b) {

    unsigned int offset = pos - inputPosOffset;
    if (offset >= 0 && offset < bufferSize) {
        bufferSound[offset] = b;
    }
    if (offset >= bufferSize - 1) {
//        std::cout << "Output flush " << pos << std::endl;
        outputPos = 0;
        inputPosOffset += bufferSize;
        for (unsigned int i = 0; i < bufferSize; i++) {
            w->write(bufferSound[i]);
        }
    }
}

}
