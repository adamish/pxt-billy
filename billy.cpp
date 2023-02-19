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
     //uBit.audio.setSpeakerEnabled(false);
    // uBit.io.speaker.setHighDrive(true);
}

void Billy::flushRemainder() {
    if (outputBufferFill > 0) {
        sampleSource->play(outputBuffer, outputBufferFill);
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

    char input[256];
    for (unsigned int i = 0; i < sizeof(input); i++) {
        input[i] = 0;
    }
    unsigned int length = strlen(words);
    // Reciter truncates *output* at about 120 characters.
    // So to avoid that we must disallow any input that will exceed that.
    if (length > 80) {
        length = 80;
    }
    for (unsigned int i = 0; i < length; i++) {
        input[i] = words[i];
    }
    // convert
    if (billy::TextToPhonemes((unsigned char *)input) == 0) {
        uBit.display.print('X');
    }

    pronounce(input, false);
}

void Billy::pronounce(const char * phonemes, bool sing) {

    SetSingmode(0);
    SetSpeed(speed);
    SetPitch(pitch);
    SetMouth(mouth);
    SetThroat(throat);

    // prepare buffer
    inputPosOffset = 0;
    outputBufferFill = 0;
    outputBufferCount = 0;

    for (int i = 0; i < sizeof(outputBuffer); i++) {
        outputBuffer[i] = 0;
    }

    // playback
    billy::SetInput((char*)phonemes);
    if (billy::SAMMain() == 0) {
        uBit.display.print('X');
    }

    uBit.display.print('O');
    flushRemainder();
}

void Billy::outputByte(unsigned int pos, unsigned char value) {
    /*
     * pos doesn't necessary increase monotonically so fill our buffer by index.
     */
    int offset = pos - inputPosOffset;
    if (offset >= 0 && offset < outputBufferSize) {
        outputBuffer[offset] = value;
        if (offset > outputBufferFill) {
            // high water mark
            outputBufferFill = offset;
        }
    }

    int posFrame = pos / outputBufferSize;
    if (posFrame > outputBufferCount) {
        outputBufferCount = posFrame;
        sampleSource->play(outputBuffer, outputBufferSize);
        outputBufferFill = 0;
        // move offset onto next window
        inputPosOffset = outputBufferCount * outputBufferSize;
    }
}

}
