enum VoicePreset {
    //% block="elf"
    Elf = 1,
    //% block="little robot"
    LittleRobot = 2,
    //% block="stuffy guy"
    StuffyGuy = 3,
    //% block="little old lady"
    LittleOldLady = 4,
    //% block="extra_terrestrial"
    ExtraTerrestrial = 5,
    //% block="default"
    Sam = 6,
    //% block="dalek"
    Dalek = 7
}

/**
 * Text to speech extension
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
        sayShim(text)
    }
    /**
     * Pronounce the following phonemes
     * e.g. "I am a computer" is "AY4 AEM AH KUMPYUW3TER"
     * @param phonemes phonemes to pronounce
     */
    //% block
    //% weight=7
    export function pronounce(phonemes: string): void {
        pronounceShim(phonemes)
    }

    /**
     * Change the voice preset
     * @param voicePreset Type of voice to use
     */
    //% block Change voice preset
    //% weight=9
    export function voicePreset(voicePreset: VoicePreset): void {
        switch (voicePreset) {
            case VoicePreset.Elf:
                configureVoice(183, 64, 110, 160)
                break
            case VoicePreset.LittleRobot:
                configureVoice(163, 60, 190, 190)
                break
            case VoicePreset.StuffyGuy:
                configureVoice(173, 72, 110, 105)
                break
            case VoicePreset.LittleOldLady:
                configureVoice(173, 32, 145, 145)
                break
            case VoicePreset.ExtraTerrestrial:
                configureVoice(155, 64, 150, 200)
                break
            case VoicePreset.Sam:
                configureVoice(183, 64, 128, 128)
                break
            case VoicePreset.Dalek:
                configureVoice(135, 100, 100, 200)
                break
            default:
                break
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
    //% shim=billy::pronounceShim
    function pronounceShim(phonemes: string): void {
        console.log(phonemes)
    }
}
