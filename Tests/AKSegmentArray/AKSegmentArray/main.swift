//
//  main.swift
//  AudioKit
//
//  Created by Aurelius Prochazka on 1/4/15.
//  Copyright (c) 2015 Aurelius Prochazka. All rights reserved.
//

import Foundation

let testDuration: Float = 10

class Instrument : AKInstrument {
    
    override init() {
        super.init()
        
        let segments = AKSegmentArray(
            initialValue: 440.ak,
            targetValue: 660.ak,
            afterDuration: 2.ak,
            concavity: 3.ak
        )
        segments.addValue(550.ak, afterDuration: 0.ak, concavity:0.ak)
        segments.addValue(550.ak, afterDuration: 1.ak, concavity:0.ak)
        segments.addValue(880.ak, afterDuration: 0.ak, concavity:0.ak)
        segments.addValue(220.ak, afterDuration: 6.ak, concavity:(-5).ak)
        segments.addValue(220.ak, afterDuration: 1.ak, concavity:0.ak)
        connect(segments)
        
        enableParameterLog("segment value = ", parameter: segments, timeInterval: 0.1)
        
        let oscillator = AKOscillator()
        oscillator.frequency = segments
        connect(oscillator)
        
        let output = AKAudioOutput(audioSource: oscillator)
        connect(output)
    }
}

let instrument = Instrument()
AKOrchestra.addInstrument(instrument)
AKManager.sharedManager().isLogging = true
AKOrchestra.testForDuration(testDuration)

instrument.play()

while(AKManager.sharedManager().isRunning) {} //do nothing
println("Test complete!")