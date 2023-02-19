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

extern char *sam_error;

WavWriter *w;

int main(void) {
    billy::sam_memory sam;
    billy::sam_memory *samPtr = &sam;

    sam.common.singmode = true;
    sam.common.pitch = DEFAULT_PITCH;
    sam.common.speed = DEFAULT_SPEED;
    sam.common.mouth = DEFAULT_MOUTH;
    sam.common.throat = DEFAULT_THROAT;

    billy::reciter_memory mem;
    char *example = "Hello this a test 1 2 3 adam";
    for (int i = 0; i < sizeof(mem.input); i++) {
        mem.input[i] = 0;
    }
    for (int i = 0; i < strlen(example); i++) {
        mem.input[i] = example[i];
    }

    int x = billy::TextToPhonemes(&mem);
    std::cout << "TextToPhonemes " << x << std::endl;

    for (int i = 0; i < strlen(mem.input); i++) {
        std::cout << mem.input[i];
    }
    std::cout << std::endl;

    for (int i = 0; i < strlen(mem.input); i++) {
        std::cout << i << ":" << (int) mem.input[i] <<  std::endl;
    }
    std::cout << std::endl;

    const char *ph = mem.input;

    /*
     * mem.input gets padded with spaces,
     * find the first non-space character
     */
    unsigned int lastCharIndex = 0;
    for (int i = strlen(mem.input) - 2; i > 0; i--) {
        if (mem.input[i] != 32) {
            lastCharIndex = i;
            break;
        }
    }
    mem.input[lastCharIndex + 1] = 0;

    std::cout << "Length " << strlen(ph) << std::endl;
    billy::SetInput(&sam, ph, strlen(ph));

    w = new WavWriter();
    w->setSampleRate(7812);
    w->init("out.wav");

    std::cout << ph << std::endl;
    int ret = billy::SAMMain(samPtr);
    std::cout << "main " << ret << std::endl;
    std::cout << billy::sam_error << std::endl;

    w->close();
    return 0;
}

namespace billy {
int debug = 1;


int outputPos = 0;
int bufferSize = 256;
char buffer[256];
int inputPosOffset = 0;

void SamOutputByte(unsigned int pos, unsigned char b) {
    unsigned int actual_pos = SCALE_RATE(pos);

    int offset = actual_pos - inputPosOffset;
    if (offset >= 0 && offset < bufferSize) {
        buffer[offset] = b;
        std::cout << "actual " << actual_pos << " offset " << offset << std::endl;
    }
    if (offset >= bufferSize - 1) {
        /*
         * start next buffer, flush
         */
        outputPos = 0;
        inputPosOffset += bufferSize;
        std::cout << "Flush" << std::endl;
        for (int i = 0; i < bufferSize; i++) {
            w->write(buffer[i]);
        }
    }

}
}
