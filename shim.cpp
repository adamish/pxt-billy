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

#include "pxt.h"
#include "billy.h"

namespace billy {

int debug = 0;

// global instance
Billy b;

// global function called by the legacy C
void SamOutputByte(unsigned int pos, unsigned char value) {
    b.outputByte(pos, value);
}

// shims from typescript...
/**
 *
 */
//%
void configureVoiceShim(int speed, int pitch, int mouth, int throat) {
   b.configureVoice(speed, pitch, mouth, throat);
}

/**
 *
 */
//%
void sayShim(String words) {
    const char * cstr = words->getUTF8Data();
    b.init();
    b.say(cstr);
}
/**
 *
 */
//%
void pronounceShim(String words) {
    const char * cstr = words->getUTF8Data();
    b.init();
    b.pronounce(cstr, false);
}
/**
 *
 */
//%
void singShim(String words) {
    const char * cstr = words->getUTF8Data();
    b.init();
    b.pronounce(cstr, true);
}
}
