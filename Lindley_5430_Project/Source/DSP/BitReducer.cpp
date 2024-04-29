/*
  ==============================================================================

    BitReducer.cpp
    Created: 11 Apr 2024 2:59:47am
    Author:  Keller Lindley

  ==============================================================================
*/

#include "BitReducer.h"



void BitReducer::processBuffer(float * buffer, const int numSamples, const int channel)
{
    
    // Perform the processing
    for (int n = 0;  n < numSamples ; n++){
        
        float x = buffer[n];
        
        buffer[n] = processSample(x,channel);
        
        
    }
}

float BitReducer::processSample(float x, int channel)
{
    
    float totalQLevels = powf(2, bitDepth);
    
    float remainder =fmodf(x, 1/totalQLevels);
    
    y = x - remainder;
    

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
