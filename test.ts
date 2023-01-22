// tests go here; this will not be compiled when this package is used as a library

basic.forever(() => {
    basic.showNumber(banana.bananas(3))
    basic.pause(1000)
    basic.showNumber(banana.bananaMultiplier(3))
    basic.pause(1000)
    basic.showNumber(banana.bananaMultiply(3, 3))
    basic.pause(1000)
})
