enum VoicePreset {
    //% block="Elf"
    ELF = 1,
    //% block="Little Robot"
    LITTLE_ROBOT = 2,
    //% block="Stuffy Guy"
    STUFFY_GUY = 3,
    //% block="Little Old Lady"
    LITTLE_OLD_LADY = 4,
    //% block="Extra_Terrestrial"
    EXTRA_TERRESTRIAL = 5,
    //% block="Default"
    SAM = 6,
    //% block="Dalek"
    DALEK = 7
}

/**
 * Define blocks
 */
//% weight=100 color=#7f00ff icon="\uf028"
namespace billy {
    /**
     * Say the following text
     * @param text words to say
     */
    //% block
    //% weight=10
    export function say(text: string): void {
        sayShim(text);
    }
    /**
     * Pronounce the following phonemes
     * e.g. "I am a computer" is "AY4 AEM AH KUMPYUW3TER"
     * @param phonemes phonemes to pronounce
     */
    //% block
    //% weight=7
    export function pronounce(phonemes: string): void {
        pronounceShim(phonemes);
    }

    /**
     * Sing a song
     * e.g. "#115DOWWWWWW#103REYYYYYY#94MIYYYYYY#88FAOAOAOAOR#78SOHWWWWW#70LAOAOAOAOR#62TIYYYYYY#58DOWWWWWW"
     * @param phonemes phonemes including pitch
     */
    //% block
    //% weight=6
    export function sing(phonemes: string): void {
        singShim(phonemes);
    }

    /**
     * Change the voice preset
     * @param voicePreset Type of voice to use
     */
    //% block Change voice preset
    //% weight=9
    export function voicePreset(voicePreset: VoicePreset): void {
        switch (voicePreset) {
            case VoicePreset.ELF:
                configureVoice(183, 64, 110, 160);
                break;
            case VoicePreset.LITTLE_ROBOT:
                configureVoice(163, 60, 190, 190);
                break;
            case VoicePreset.STUFFY_GUY:
                configureVoice(173, 72, 110, 105);
                break;
            case VoicePreset.LITTLE_OLD_LADY:
                configureVoice(173, 32, 145, 145);
                break;
            case VoicePreset.EXTRA_TERRESTRIAL:
                configureVoice(155, 64, 150, 200);
                break;
            case VoicePreset.SAM:
                configureVoice(183, 64, 128, 128);
                break;
            case VoicePreset.DALEK:
                configureVoice(135, 100, 100, 200);
                break;
            default:
                break;
        }
    }

    /**
     * Configure voice parameters
     * @param speed how quickly the voice talks. 0 slow, 255 fast.
     * @param pitch how high or low the voice sounds
     * @param throat how relaxed or tense is the tone of voice
     * @param mouth how tight-lipped or overtly enunciating the voice sounds
     */
    //% block Configure Voice
    //% speed.min=1 speed.max=255 speed.defl=72
    //% pitch.min=1 pitch.max=255 pitch.defl=64
    //% throat.min=1 throat.max=255 throat.defl=128
    //% mouth.min=1 mouth.max=255 mouth.defl=128
    //% weight=8
    export function configureVoice(speed: number, pitch: number, throat: number, mouth: number): void {
        /*
         * Original SAM uses 0 as fast 255 as slow.
         * Flip it and reverse it.
         */
        configureVoiceShim(255 - speed, pitch, throat, mouth)
    }

    /**
     *
     */
    //% shim=billy::configureVoiceShim
    function configureVoiceShim(speed: number, pitch: number, throat: number, mouth: number): void {
        console.log("configureVoice")
    }
    /**
     */
    //% shim=billy::sayShim
    function sayShim(text: string): void {
        console.log(text)
    }
    /**
     */
    //% shim=billy::singShim
    function singShim(song: string): void {
        console.log(song)
    }
    /**
     */
    //% shim=billy::pronounceShim
    function pronounceShim(phonemes: string): void {
        console.log(phonemes)
    }
}

