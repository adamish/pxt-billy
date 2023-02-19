# SAM

The contents of this directory come from [C port of SAM](https://github.com/s-macke/SAM)

Modifications
 * Changed .c to .cpp
 * Wrapped in a namespace for isolation
 * changed output to call a method rather than writing into a larger buffer (limited memory on Micro:bit)
 * freq1data, freq2data and freq3data moved from header into .cpp as they were not consts and causing cloud build failure