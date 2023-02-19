# Billy

This is a MakeCode extension based on a [port of SAM](https://github.com/s-macke/SAM) by Sebastian Macke. 

SAM "Software Automatic Mouth" itself is a legendary text to speech algorithm from 1982 for the Commodore C64

## Add to a MakeCode Project

This repository can be added as an **extension** in MakeCode.

- Open https://makecode.microbit.org
- Click on **New Project**
- Click on **Extensions** under the gearwheel menu
- Search for **https://github.com/adamish/pxt-billy** and import it

## Examples

Basic usage

```block
input.onButtonPressed(Button.A, function () {
    billy.say("Hello World")
})

input.onButtonPressed(Button.B, function () {
    billy.say("I am a DALEK - EXTERMINATE")
})
```

The voice can be configured from an existing preset

```
input.onButtonPressed(Button.A, function () {
    billy.configureVoice(VoicePreset.DALEK)
    billy.say("I am a DALEK - EXTERMINATE")
})
```

The voice can be configured with individual values for speed, pitch, throat and mouth 
Each value is in the range of 0 to 255

* speed - how quickly the voice talks - low value slow, high value fast
* pitch - how high or low the voice sounds
* throat - how relaxed or tense is the tone of voice
* mouth - how tight-lipped the voice sounds

```
input.onButtonPressed(Button.A, function () {
    billy.configureVoice(92, 60, 190, 190);
    billy.say("I am a robot")
})
```

Advanced pronounciation can be achieved with direct use of phonemes

See [original SAM manual](https://github.com/discordier/sam/blob/master/docs/manual.md) for full details of the syntax 

```block
input.onButtonPressed(Button.A, function () {
    billy.pronounce("/HEHLOW WERLD")
})
```

## Supported targets

* for PXT/microbit

(The metadata above is needed for package search, update it with the targets you support)

## Acknowledgements
* Icon from [Text to speech icons created by Freepik - Flaticon](https://www.flaticon.com/free-icons/text-to-speech)
* Sebastian Macke - author of the [C port of SAM](https://github.com/s-macke/SAM)
* Authors of [BBC micro:bit MicroPython speech module](https://github.com/bbcmicrobit/micropython/tree/master/source/lib/sam) for inspiration

## License 

MIT

## Links

 * [BBC micro:bit MicroPython - docs](https://microbit-micropython.readthedocs.io/en/latest/tutorials/speech.html)
 * [BBC micro:bit MicroPython - SAM port](https://github.com/bbcmicrobit/micropython/tree/master/source/lib/sam)
 * [BBC micro:bit MicroPython - wrapper](https://github.com/bbcmicrobit/micropython/blob/master/source/microbit/modspeech.c)
 * [Original C port](https://github.com/s-macke/SAM)
 * [SpeakerTest.cpp](https://github.com/lancaster-university/microbit-v2-samples/blob/master/source/samples/SpeakerTest.cpp)
 * [Original SAM manual](https://archive.org/details/user_manual_s.a.m.)
 