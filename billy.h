/*
 * MIT License

* Copyright (c) 2023 Adam Granger

* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.

* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE. */

#ifndef BILLY_H
#define BILLY_H

#include "MicroBit.h"
#include "MicroBitConfig.h"
#include "MemorySource.h"
#include "sam/render.h"
#include "sam/sam.h"
#include "sam/reciter.h"
#include <string>

namespace billy {
const unsigned int outputBufferSize = 4096;
const int sampleRate = 22050;

class Billy {
    MemorySource *sampleSource = NULL;
    uint8_t outputBuffer[outputBufferSize];
    /*
     * how much of outputBuffer is current filled
     */
    unsigned int outputBufferFill = 0;
    /*
     * how many output buffers have been flushed
     */
    unsigned int outputBufferCount = 0;
    unsigned int inputPosOffset = 0;
    void flushRemainder();
    int speed = 64;
    int pitch = 72;
    int mouth = 128;
    int throat = 128;
    void resetBuffer();
public:
    Billy();
    void init();
    void say(const char * words);
    void pronounce(const char * phonemes, bool sing);
    void configureVoice(int pitch, int speed, int mouth, int throat);
    void outputByte(unsigned int pos, unsigned char value);
};

}
#endif
