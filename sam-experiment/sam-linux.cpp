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

char input[256];

WavWriter *w;

char buffer[50000];

int main(void) {
//    billy::sam_memory sam;
//    billy::sam_memory *samPtr = &sam;

    SetSingmode(0);
//    SetSpeed(72);
//    SetPitch(64);
//    SetMouth(128);
//    SetThroat(128);

//    billy::reciter_memory mem;
    char *example = "Hello this is a test";
    for (int i = 0; i < sizeof(input); i++) {
        input[i] = 0;
    }
    for (int i = 0; i < strlen(example); i++) {
        input[i] = example[i];
    }

    int x = billy::TextToPhonemes((unsigned char *)input);
    std::cout << "TextToPhonemes " << x << std::endl;

    for (int i = 0; i < strlen(input); i++) {
        std::cout << input[i];
    }
    std::cout << std::endl;

    for (int i = 0; i < strlen(input); i++) {
        std::cout << i << ":" << (int) input[i] <<  std::endl;
    }
    std::cout << std::endl;

    const char *ph = input;

    /*
     * input gets padded with spaces,
     * find the first non-space character
     */
    unsigned int lastCharIndex = 0;
    for (int i = strlen(input) - 2; i > 0; i--) {
        if (input[i] != 32) {
            lastCharIndex = i;
            break;
        }
    }
//    input[lastCharIndex + 1] = 0;

    std::cout << "Length " << strlen(ph) << std::endl;
    billy::SetInput(input);

    w = new WavWriter();
    w->setSampleRate(22500);
    w->init("out.wav");

    std::cout << ph << std::endl;
    int ret = billy::SAMMain();
    std::cout << "main " << ret << std::endl;
//    std::cout << billy::sam_error << std::endl;

    for (int i = 0; i < sizeof(buffer); i++) {
       w->write(buffer[i]);
    }
    w->close();
    return 0;
}

namespace billy {
int debug = 1;

void SamOutputByte(unsigned int pos, unsigned char b) {
    std::cout << pos << std::endl;
//    w->write(b);
    buffer[pos] = b;
}

}
