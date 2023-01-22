/**
 * C++ functions as part of the extension.
 * 
 * A function defined here will run on the micro:bit, there is also a "shim"
 * in the main.ts file that will be run in the simulator.
 * Info about shims: https://makecode.com/simshim
 */
#include "pxt.h"

using namespace pxt;

namespace banana {
    #define V1_MULTIPLIER 2
    #define V2_MULTIPLIER 3

    /**
     * This simple C++ function to simply add your bananas!
     */
    //%
    int banana_add(int bananas, int multiplier) {
        return bananas + multiplier;
    }

    /**
     * This function uses the C preprocessor to compile different code
     * depending on the version of the micro:bit.
     */
    //%
    int banana_multiplier(int bananas) {
    #if MICROBIT_CODAL
        // On micro:bit V2 the multiplier is 2
        return bananas * V2_MULTIPLIER;
    #else
        // On micro:bit V1 the multiplier is 1
        return bananas * V1_MULTIPLIER;
    #endif
    }

    /**
     * This function uses the C preprocessor to throw an error if this function
     * is run on a micro:bit V1.
     */
    //%
    int bananas_v2_only(int bananas) {
    #if MICROBIT_CODAL
        return bananas;
    #else
        target_panic(PANIC_VARIANT_NOT_SUPPORTED);
    #endif
    }
}
