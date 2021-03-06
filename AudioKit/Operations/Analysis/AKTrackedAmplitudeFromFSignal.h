//
//  AKTrackedAmplitudeFromFSignal.h
//  AudioKit
//
//  Created by Aurelius Prochazka on 8/3/14.
//  Copyright (c) 2014 Aurelius Prochazka. All rights reserved.
//

#import "AKParameter+Operation.h"
#import "AKControl.h"
#import "AKFSignal.h"

/** Track the amplitude of an F-Signal as control-rate variables.
 
 The pitch detection algorithm implemented is based upon J. F. Schouten's hypothesis of the neural processes of the brain used to determine the pitch of a sound after the frequency analysis of the basilar membrane. Except for some further considerations, pvspitch essentially seeks out the highest common factor of an incoming sound's spectral peaks to find the pitch that may be attributed to it.
 
 In general, input sounds that exhibit pitch will also exhibit peaks in their spectrum according to where their harmonics lie. There are some the exceptions, however. Some sounds whose spectral representation is continuous can impart a sensation of pitch. Such sounds are explained by the centroid or center of gravity of the spectrum and are beyond the scope of the method of pitch detection implemented.
 
 This operation is able (using a previous analysis F-signal generated by AKFSignalFrom MonoAudio) to locate the spectral peaks of a signal. The threshold parameter is of utmost importance, as adjusting it can introduce weak yet significant harmonics into the calculation of the fundamental. However, bringing amplitudeThreshold too low would allow harmonically unrelated partials into the analysis algorithm and this will compromise the method's accuracy. These initial steps emulate the response of the basilar membrane by identifying physical characteristics of the input sound. The choice of kthresh depends on the actual level of the input signal, since its range (from 0 to 1) spans the whole dynamic range of an analysis bin (from -inf to 0dBFS).
 
 It is important to remember that the input to the operation is assumed to be characterised by strong partials within its spectrum. If this is not the case, the results outputted by the opcode may not bear any relation to the pitch of the input signal. If a spectral frame with many unrelated partials was analysed, the greatest common factor of these frequency values that allows for adjacent “harmonics” would be chosen. Thus, noisy frames can be characterised by low frequency outputs. This fact allows for a primitive type of instrumental transient detection, as the attack portion of some instrumental tones contain inharmonic components. Should the lowest frequency of the analysed melody be known, then all frequencies detected below this threshold are inaccurate readings, due to the presence of unrelated partials.
 
 In order to facilitate efficient testing of the algorithm, an amplitude value proportional to the one in the observed in the signal frame is also outputted (kamp). The results can then be employed to drive an oscillator whose pitch can be audibly compared with that of the original signal (In the example below, an oscillator generates a signal which appears a fifth above the detected pitch).
 */
@interface AKTrackedAmplitudeFromFSignal : AKControl

/// Initialize the tracked amplitude.
/// @param fSignalSource      Input mono F-Signal.
/// @param amplitudeThreshold Amplitude threshold (0-1). Higher values will eliminate low-amplitude spectral components from being included in the analysis.
- (instancetype)initWithFSignalSource:(AKFSignal *)fSignalSource
                   amplitudeThreshold:(AKControl *)amplitudeThreshold;

@end
