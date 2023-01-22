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

#include "billy.h"
#include "pxt.h"

namespace billy {

Billy::Billy() {
    sam = new sam_memory();
}


void Billy::init() {
    uBit.audio.requestActivation();
    if (sampleSource == NULL) {
        sampleSource = new MemorySource();
        sampleSource->setFormat(DATASTREAM_FORMAT_8BIT_UNSIGNED);
        sampleSource->setBufferSize(outputBufferSize);
    }
    uBit.audio.mixer.addChannel(*sampleSource, sampleRate, 255);

    // not required?
    // uBit.audio.setVolume(255);
    // uBit.audio.setSpeakerEnabled(true);
    // uBit.io.speaker.setHighDrive(true);
}

void Billy::flushRemainder() {
    if (outputBufferPos > 0) {
        sampleSource->play(outputBuffer, outputBufferPos);
    }
}

void Billy::configureVoice(int pitch, int speed, int mouth, int throat) {
    this->pitch = pitch;
    this->speed = speed;
    this->mouth = mouth;
    this->throat = throat;
}

/**
 * Speak and route output to micro:bit mixer
 */
void Billy::say(const char * words) {

    // load
    billy::reciter_memory mem;
    for (unsigned int i = 0; i < sizeof(mem.input); i++) {
        mem.input[i] = 0;
    }
    unsigned int length = strlen(words);
    // Reciter truncates *output* at about 120 characters.
    // So to avoid that we must disallow any input that will exceed that.
    if (length > 80) {
        length = 80;
    }
    for (unsigned int i = 0; i < length; i++) {
        mem.input[i] = words[i];
    }
    // convert
    if (billy::TextToPhonemes(&mem) == 0) {
        uBit.display.print('X');
    }

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
    // null terminate so behaves nicely with strlen()
    mem.input[lastCharIndex + 1] = 0;

    pronounce(mem.input, false);
}

void Billy::pronounce(const char * phonemes, bool sing) {

    sam->common.singmode = sing;
    sam->common.pitch = pitch;
    sam->common.speed = speed;
    sam->common.mouth = mouth;
    sam->common.throat = throat;

    // prepare buffer
    outputBufferPos = 0;

    // playback
    billy::SetInput(sam, phonemes, strlen(phonemes));
    if (billy::SAMMain(sam) == 0) {
        uBit.display.print('X');
    }
    flushRemainder();
}

void Billy::outputByte(unsigned int pos, unsigned char value) {
    outputBuffer[outputBufferPos] = value;
    outputBufferPos++;

    if (outputBufferPos >= outputBufferSize) {
        outputBufferPos = 0;
        /*
         *  play() is blocking so can just wait for completion
         */
        sampleSource->play(outputBuffer, outputBufferSize);
    }
}

}
