/*
 * This is a manual test
 * Press the A button and listen to the output
 */
let testNumber = 0
input.onButtonPressed(Button.A, function () {
    basic.showNumber(testNumber)
    switch (testNumber) {
        case 0:
            test0()
        break
        case 1:
            test1()
        break
        case 2:
            test2()
        break
        case 3:
            test3()
        break
        case 4:
            test4()
        break
        case 5:
            test5()
        break
        case 6:
            test6()
        break
        default:
        break
    }
    testNumber = (testNumber + 1) % 7
})

/*
 * Say a basic sentence using defaults
 */
function test0() {
    billy.say("Testing testing 1 2 3")
}

/*
 * Use a different voice
 */
function test1() { 
    billy.voicePreset(BillyVoicePreset.Elf)
    billy.say("Testing testing 1 2 3")
}

/*
 * Speak faster
 */
 function test2() { 
    billy.configureVoice(220, 64, 128, 128)
    billy.say("Testing testing 1 2 3")
}

/*
 * Speak slower
 */
function test3() { 
    billy.configureVoice(30, 64, 128, 128)
    billy.say("Testing testing 1 2 3")
}

/*
 * speak lower
 */
function test4() { 
    billy.configureVoice(183, 32, 128, 128)
    billy.say("Testing testing 1 2 3")
}

/*
 * speak higher
 */
function test5() { 
    billy.configureVoice(183, 200, 128, 128)
    billy.say("Testing testing 1 2 3")
} 
 
/*
 * speak using phonemes
 */
function test6() { 
    billy.voicePreset(BillyVoicePreset.Sam)
    billy.pronounce("AY4 AEM AH KUMPYUW3TER")
}