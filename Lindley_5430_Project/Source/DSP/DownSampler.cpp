/*
  ==============================================================================

    DownSampler.cpp
    Created: 11 Apr 2024 2:20:19am
    Author:  Keller Lindley

  ==============================================================================
*/

#include "DownSampler.h"
void DownSampler::processBuffer(float * samples, const int numSamples, const int channel)
{
    
    // Perform the processing
    for (int n = 0; n < numSamples ; n++){
        float x = samples[n];
        
        samples[n] = processSample(x,channel);
    }
}

float DownSampler::processSample(float x, int channel)
{
    //decimationRatio = Fs/newFs;
    
    return 0;
    
};

void DownSampler::setFs(float sampleRate)
{
    this->Fs = sampleRate;
};

float DownSampler::getFs()
{
    return Fs;
};

void DownSampler::setNewFs(float newFs)
{
    this->newFs = newFs;
};

float DownSampler::getNewFs()
{
    return Fs;
};
