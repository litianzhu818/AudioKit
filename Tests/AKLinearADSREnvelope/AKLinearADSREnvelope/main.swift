//
//  main.swift
//  AudioKit
//
//  Created by Aurelius Prochazka and Nick Arner on 12/29/14.
//  Copyright (c) 2014 Aurelius Prochazka. All rights reserved.
//

import Foundation

let testDuration: Float = 10.0

class Instrument : AKInstrument {
    
    override init() {
        super.init()
        
        let adsr = AKLinearADSREnvelope()
        connect(adsr)
        enableParameterLog("ADSR value = ", parameter: adsr, timeInterval:0.02)

        let oscillator = AKOscillator()
        oscillator.amplitude = adsr
        connect(oscillator)
        
        connect(AKAudioOutput(audioSource:oscillator))
    }
}

let instrument = Instrument()
AKOrchestra.addInstrument(instrument)

AKOrchestra.testForDuration(testDuration)

let note1 = AKNote()
let note2 = AKNote()

let phrase = AKPhrase()
phrase.addNote(note1, atTime:0.5)
phrase.stopNote(note1, atTime: 2.5)

note2.duration.setValue(5.0)
phrase.addNote(note2, atTime:3.5)
instrument.playPhrase(phrase)


while(AKManager.sharedManager().isRunning) {} //do nothing
println("Test complete!")

