/*
  ==============================================================================

    BitReducer.cpp
    Created: 11 Apr 2024 2:59:47am
    Author:  Keller Lindley

  ==============================================================================
*/

#include "BitReducer.h"

void BitReducer::processBuffer(float * samples, const int numSamples, const int channel)
{
    
    // Perform the processing
    for (int n = 0; n < numSamples ; n++){
        float x = samples[n];
        
        samples[n] = processSample(x,channel);
    }
}

float BitReducer::processSample(float x, int channel)
{
    ampValues = std::pow(2, bitDepth);
    shrinkInput = (0.5f * x) + 5;
    scaleInput = ampValues * shrinkInput;
    roundInput = round(scaleInput);
    prepOut = roundInput / ampValues;
    
    y = 2 * prepOut - 1;
    return y;
};

void BitReducer::setFs(float sampleRate)
{
    this->Fs = sampleRate;
};

float BitReducer::getFs()
{
    return Fs;
};

void BitReducer::setBitDepth(float bitDepth)
{
    this->bitDepth = bitDepth;
};

float BitReducer::getBitDepth()
{
    return Fs;
};
